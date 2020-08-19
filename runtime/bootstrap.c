//
// Created by wangzhanzhi on 2020/7/9.
//

#include "bootstrap.h"

//void init_lib(Thread *thread, SerialHeap *heap)
//{
//    zip_error_t err;
//    char *jmod_name = "java.base.jmod";
//    char *file_path = malloc(strlen(JAVA_HOME) + strlen(jmod_name) + 8);
//    sprintf(file_path, "%s/jmods/%s", JAVA_HOME, jmod_name);
//    FILE *fp = fopen(file_path, "rb");
//    if (NULL == fp) exit(-1);
//    fseek(fp, 0, SEEK_END);
//    long f_size = ftell(fp);
//    fclose(fp);
//    int offset = 4;
//    zip_error_t error;
//    zip_source_t *source = zip_source_file_create(file_path, offset, f_size - offset, &error);
//    zip_t *z = zip_open_from_source(source, 0, &err);
//    //Search for the file of given name
//    struct zip_stat st;
//    zip_stat_init(&st);
//    int file_count = zip_get_num_files(z);
//    for (int i = 0; i < file_count; i++) {
//        zip_stat_index(z, i, 0, &st);
//        if (!str_start_with(st.name, "classes/java/")) {
//            continue;
//        }
//        //Alloc memory for its uncompressed contents
//        u1 *contents = malloc(st.size);
//        //Read the compressed file
//        zip_file_t *f = zip_fopen(z, st.name, 0);
//        zip_fread(f, contents, st.size);
//        zip_fclose(f);
//
//        ClassFile *class = load_class_by_bytes(thread, heap, contents);
//        clinit_class_and_exec(thread, heap, class);
//    }
//    zip_close(z);
//    free(file_path);
//}

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
    VM_OPTS = create_map_by_size((int)(20 * 1.3) + 1);
    put_map(&VM_OPTS, "java.version", "1.11.0");
    put_map(&VM_OPTS, "java.version.data", "2019");
    put_map(&VM_OPTS, "java.vendor", "discjvm");
    put_map(&VM_OPTS, "java.vendor.url", "https://github.com/smallcham/discjvm");
    put_map(&VM_OPTS, "java.vendor.version", "1.0");
    put_map(&VM_OPTS, "java.home", JAVA_HOME);
    put_map(&VM_OPTS, "java.class.version", "55.0");
    put_map(&VM_OPTS, "java.class.path", JAVA_HOME);
    put_map(&VM_OPTS, "os.name", "linux");
    put_map(&VM_OPTS, "os.arch", "amd64");
    put_map(&VM_OPTS, "os.version",  "");
    put_map(&VM_OPTS, "file.separator", "/");
    put_map(&VM_OPTS, "path.separator", ":");
    put_map(&VM_OPTS, "line.separator", "\n");
    put_map(&VM_OPTS, "user.name", "");
    put_map(&VM_OPTS, "user.home", "");
    put_map(&VM_OPTS, "user.dir", ".");
//    put_map(&VM_OPTS, "user.country", "CN");
//    put_map(&VM_OPTS, "file.encoding", "UTF-8");
//    put_map(&VM_OPTS, "sun.stdout.encoding", "UTF-8");
//    put_map(&VM_OPTS, "sun.stderr.encoding", "UTF-8");
    return &VM_OPTS;
}

void start_vm(char *class_path)
{
    JAVA_HOME = getenv("JAVA_HOME");
    NULL_SLOT = create_slot_by_size(2);
    VM_OPTS = *init_vm_opts();

    char *base_lib[] = {
//            "java/lang/Object",
            "java/lang/String",
            "java/lang/System",
            "java/lang/Class",
//            "java/lang/Integer",
//            "java/lang/Float",
//            "java/lang/Double",
//            "java/lang/ClassLoader",
            "java/lang/ThreadGroup",
            "java/lang/Thread",
//            "java/io/PrintStream"
    };
    SerialHeap *heap = init_gc();
    init_instructions();
    init_native_factory();
    init_instructions_desc();
    Thread thread = create_thread(100, 100);
//    init_lib(&thread, heap);
    init_primitives(&thread, heap);
    init_lib_by_names(&thread, heap, base_lib, 5);

    //创建 main方法栈帧
    ClassFile *class = load_class(&thread, heap, class_path);
    clinit_class_and_exec(&thread, heap, class);

    MethodInfo *main = find_method(&thread, heap, class, "main");
    CodeAttribute *main_code = get_method_code(class->constant_pool, *main);

    if (NULL == main) exit(-1);
    create_vm_frame_by_method(&thread, class, main, main_code);

    //new ThreadGroup
    ClassFile *jthread_group = load_class(&thread, heap, "java/lang/ThreadGroup");
    Slot *jthread_group_object = create_object_slot(heap, jthread_group);
    MethodInfo *jthread_group_init = find_method_with_desc(&thread, heap, jthread_group, "<init>", "()V");

    //call
//    Frame *jthread_group_frame = create_vm_frame_by_method(&thread, jthread_group, jthread_group_init, get_method_code(jthread_group->constant_pool, *jthread_group_init));
//    push_slot(jthread_group_frame->operand_stack, jthread_group_object);
//    add_params_and_plus1(jthread_group_frame, jthread_group_frame, jthread_group_init);
//    run(&thread, heap);

    //new Thread
    ClassFile *jthread = load_class(&thread, heap, "java/lang/Thread");
    Slot *jthread_object = create_object_slot(heap, jthread);
    //此处必须初始化设置priority， 否则会抛出IllegalArgumentException异常， 详情请查看Java代码Thread.setPriority 中校验的最大值和最小值
    put_value_field_by_name_and_desc(jthread_object->object_value, "priority", "I", 1);
//    put_field_to_map(&((Object*)jthread_object->object_value)->fields, "priority", "I", create_slot_set_value(1));
    MethodInfo *jthread_init = find_method_with_desc(&thread, heap, jthread, "<init>", "(Ljava/lang/ThreadGroup;Ljava/lang/String;)V");

    //call
//    Frame *jthread_frame = create_vm_frame_by_method(&thread, jthread, jthread_init, get_method_code(jthread->constant_pool, *jthread_init));
//    push_slot(jthread_frame->operand_stack, jthread_object);
//    push_slot(jthread_frame->operand_stack, jthread_group_object);
//    create_string_object_without_back(&thread, heap, jthread_frame, "main");
//    add_params_and_plus1(jthread_frame, jthread_frame, jthread_init);
//    thread.jthread = jthread_object->object_value;
//    run(&thread, heap);

    //new System
    ClassFile *system = load_class(&thread, heap, "java/lang/System");
    Slot *system_object = create_object_slot(heap, system);

    //初始化3阶段
    MethodInfo *init_phase3 = find_method_with_desc(&thread, heap, system, "initPhase3", "()V");
    Frame *phase3_frame = create_vm_frame_by_method(&thread, system, init_phase3, get_method_code(system->constant_pool, *init_phase3));
    push_slot(phase3_frame->operand_stack, system_object);
    add_params_and_plus1(phase3_frame, phase3_frame, init_phase3);

    //初始化2阶段
    MethodInfo *init_phase2 = find_method_with_desc(&thread, heap, system, "initPhase2", "(ZZ)I");
    Frame *phase2_frame = create_vm_frame_by_method(&thread, system, init_phase2, get_method_code(system->constant_pool, *init_phase2));
    push_slot(phase2_frame->operand_stack, system_object);
    push_slot(phase2_frame->operand_stack, create_slot_set_value(1));
    push_slot(phase2_frame->operand_stack, create_slot_set_value(1));
    add_params_and_plus1(phase2_frame, phase2_frame, init_phase2);

    //初始化1阶段
    MethodInfo *init_phase1 = find_method_with_desc(&thread, heap, system, "initPhase1", "()V");
    Frame *phase1_frame = create_vm_frame_by_method(&thread, system, init_phase1, get_method_code(system->constant_pool, *init_phase1));
    push_slot(phase1_frame->operand_stack, system_object);
    add_params_and_plus1(phase1_frame, phase1_frame, init_phase1);

    //创建main Thread
    Frame *jthread_frame = create_vm_frame_by_method(&thread, jthread, jthread_init, get_method_code(jthread->constant_pool, *jthread_init));
    push_slot(jthread_frame->operand_stack, jthread_object);
    push_slot(jthread_frame->operand_stack, jthread_group_object);
    create_string_object_without_back(&thread, heap, jthread_frame, "main");
    add_params_and_plus1(jthread_frame, jthread_frame, jthread_init);
    thread.jthread = jthread_object->object_value;
//    run(&thread, heap);

    //创建ThreadGroup
    Frame *jthread_group_frame = create_vm_frame_by_method(&thread, jthread_group, jthread_group_init, get_method_code(jthread_group->constant_pool, *jthread_group_init));
    push_slot(jthread_group_frame->operand_stack, jthread_group_object);
    add_params_and_plus1(jthread_group_frame, jthread_group_frame, jthread_group_init);

//    run(&thread, heap);

//
//    ClassFile *jthread = load_class(&thread, heap, "java/lang/Thread");
//    MethodInfo *jthread_init = find_method_with_desc(&thread, heap, jthread, "<init>", "(Ljava/lang/ThreadGroup;Ljava/lang/String;)V");
//    clinit_class_and_exec(&thread, heap, jthread);
//    Frame *frame = create_vm_frame_by_method(&thread, jthread, jthread_init, get_method_code(jthread->constant_pool, *jthread_init));
//    Slot *slot = create_slot();
//    slot->object_value = malloc_object(heap, jthread);
//    push_slot(frame->operand_stack, slot);
//    run(&thread, heap);

//    ClassFile *class = load_class(&thread, heap, class_path);
//    clinit_class_and_exec(&thread, heap, class);
//
//    MethodInfo *main = find_method(&thread, heap, class, "main");
//    CodeAttribute *main_code = get_method_code(class->constant_pool, *main);
//
//    if (NULL == main) exit(-1);
//    create_vm_frame_by_method(&thread, class, main, main_code);
    run(&thread, heap);
}