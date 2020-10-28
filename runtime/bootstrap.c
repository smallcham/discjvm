//
// Created by wangzhanzhi on 2020/7/9.
//

#include <pwd.h>
#include "bootstrap.h"

void init_lib_by_names(Thread *thread, SerialHeap *heap, char *names[], int count)
{
    for (int i = 0; i < count; i++) {
        ClassFile *class = load_class(thread, heap, names[i]);
        clinit_class_and_exec(thread, heap, class);
    }
}

void init_primitives(Thread *thread, SerialHeap *heap)
{
    load_primitive_class(thread, heap, "void");
    load_primitive_class(thread, heap, "boolean");
    load_primitive_class(thread, heap, "byte");
    load_primitive_class(thread, heap, "char");
    load_primitive_class(thread, heap, "short");
    load_primitive_class(thread, heap, "int");
    load_primitive_class(thread, heap, "long");
    load_primitive_class(thread, heap, "float");
    load_primitive_class(thread, heap, "double");
}

HashMap **init_vm_opts()
{
    VM_OPTS = create_map_by_size((int)(23 * 1.3) + 1);
    char *lib_path = malloc(strlen(JAVA_HOME) + 4);
    sprintf(lib_path, "%s/lib", JAVA_HOME);
    put_map(&VM_OPTS, "java.version", "1.11.0");
    put_map(&VM_OPTS, "java.version.data", "2019");
    put_map(&VM_OPTS, "java.vendor", "discjvm");
    put_map(&VM_OPTS, "java.vendor.url", "https://github.com/smallcham/discjvm");
    put_map(&VM_OPTS, "java.vendor.version", "1.0");
    put_map(&VM_OPTS, "java.home", JAVA_HOME);
    put_map(&VM_OPTS, "java.class.version", "55.0");
    put_map(&VM_OPTS, "java.class.path", CLASS_PATH);
    put_map(&VM_OPTS, "java.library.path", CLASS_PATH);
    put_map(&VM_OPTS, "sun.boot.library.path", lib_path);
    put_map(&VM_OPTS, "os.name", "linux");
    put_map(&VM_OPTS, "os.arch", "amd64");
    put_map(&VM_OPTS, "os.version",  "");
    put_map(&VM_OPTS, "file.separator", "/");
    put_map(&VM_OPTS, "file.encoding", "UTF-8");
    put_map(&VM_OPTS, "sun.jnu.encoding", "UTF-8");
    put_map(&VM_OPTS, "sun.stdout.encoding", "UTF-8");
    put_map(&VM_OPTS, "sun.stderr.encoding", "UTF-8");
    put_map(&VM_OPTS, "path.separator", ":");
    put_map(&VM_OPTS, "line.separator", "\n");
    put_map(&VM_OPTS, "user.name", USER_NAME);
    put_map(&VM_OPTS, "user.home", USER_HOME);
    put_map(&VM_OPTS, "user.dir", USER_DIR);
    put_map(&VM_OPTS, "user.country", "CN");
    return &VM_OPTS;
}

void start_vm(char *class_path)
{
    LOG_LEVEL = LOG_INFO;
//    LOG_LEVEL = LOG_DEBUG;
    JAVA_HOME = getenv("JAVA_HOME");
    CLASS_PATH = getenv("CLASSPATH");
    VM_STACK_SIZE = 100;
    C_STACK_SIZE = 100;
    NULL_SLOT = create_slot_by_size(1);
    struct passwd *pwd = getpwuid(getuid());
    USER_NAME = pwd->pw_name;
    USER_HOME = pwd->pw_dir;
    USER_DIR = malloc(1000);
    getcwd(USER_DIR, 1000);
    VM_OPTS = *init_vm_opts();
    _reference_pending_list = NULL;

    char *base_lib[] = {
            "java/lang/Object",
            "java/lang/Class",
            "java/lang/Module",
            "java/lang/String",
            "java/util/Vector",
            "java/lang/System",
            "java/lang/ClassLoader",
            "java/lang/ThreadGroup",
            "java/lang/Thread",
            "sun/nio/fs/UnixFileAttributes",
            "sun/nio/fs/UnixFileStoreAttributes",
            "sun/nio/fs/UnixMountEntry"
    };
    SerialHeap *heap = init_gc();
    init_instructions();
    init_native_factory();
    init_instructions_desc();
    Thread *thread = create_thread(VM_STACK_SIZE, C_STACK_SIZE);
    thread->pthread = (pthread_t *) pthread_self();
    init_lib_by_names(thread, heap, base_lib, 12);
    init_primitives(thread, heap);

    //创建 main方法栈帧
    ClassFile *class = load_class(thread, heap, class_path);
    clinit_class_and_exec(thread, heap, class);

    MethodInfo *main = find_method(thread, heap, class, "main");

    if (NULL == main) {
        printf_err("main method not found");
        exit(-1);
    }
    create_vm_frame_by_method_with_push(thread, class, main);

    Stack *params = create_unlimit_stack();
    //new ThreadGroup
    ClassFile *jthread_group = load_class(thread, heap, "java/lang/ThreadGroup");
    Slot *jthread_group_object = create_object_slot(thread, heap, jthread_group);
    MethodInfo *jthread_group_init = find_method_with_desc(thread, heap, jthread_group, "<init>", "()V");

    //new Thread
    ClassFile *jthread = load_class(thread, heap, "java/lang/Thread");
    Slot *jthread_object = create_object_slot(thread, heap, jthread);
    //此处必须初始化设置priority， 否则会抛出IllegalArgumentException异常， 详情请查看Java代码Thread.setPriority 中校验的最大值和最小值
    put_value_field_by_name_and_desc(jthread_object->object_value, "priority", "I", 1);
    MethodInfo *jthread_init = find_method_with_desc(thread, heap, jthread, "<init>", "(Ljava/lang/ThreadGroup;Ljava/lang/String;)V");

    //new System
    ClassFile *system = load_class(thread, heap, "java/lang/System");
    Slot *system_object = create_object_slot(thread, heap, system);

//    //初始化3阶段
//    MethodInfo *init_phase3 = find_method_with_desc(thread, heap, system, "initPhase3", "()V");
//    push_slot(params, system_object);
//    create_vm_frame_by_method_add_params(thread, system, params, init_phase3);
//
//    //初始化2阶段
//    MethodInfo *init_phase2 = find_method_with_desc(thread, heap, system, "initPhase2", "(ZZ)I");
//    push_slot(params, create_slot_set_value(1));
//    push_slot(params, create_slot_set_value(1));
//    create_vm_frame_by_method_add_params(thread, system, params, init_phase2);

    //初始化1阶段
    MethodInfo *init_phase1 = find_method_with_desc(thread, heap, system, "initPhase1", "()V");
    create_vm_frame_by_method_add_params(thread, system, NULL, init_phase1);

    //创建main Thread
    push_slot(params, jthread_object);
    push_slot(params, jthread_group_object);
    push_slot(params, create_str_slot_set_str(thread, heap, "main"));
    create_vm_frame_by_method_add_params_plus1(thread, jthread, params, jthread_init);

    thread->jthread = jthread_object->object_value;

    //创建ThreadGroup
    push_slot(params, jthread_group_object);
    create_vm_frame_by_method_add_params_plus1(thread, jthread_group, params, jthread_group_init);

    run(thread, heap);
}