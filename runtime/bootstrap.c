//
// Created by wangzhanzhi on 2020/7/9.
//

#include "bootstrap.h"

char *JAVA_HOME = NULL;

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
    load_primitive_class(thread, heap, "[Z");
    load_primitive_class(thread, heap, "byte");
    load_primitive_class(thread, heap, "[B");
    load_primitive_class(thread, heap, "char");
    load_primitive_class(thread, heap, "[C");
    load_primitive_class(thread, heap, "short");
    load_primitive_class(thread, heap, "[S");
    load_primitive_class(thread, heap, "int");
    load_primitive_class(thread, heap, "[I");
    load_primitive_class(thread, heap, "long");
    load_primitive_class(thread, heap, "[J");
    load_primitive_class(thread, heap, "float");
    load_primitive_class(thread, heap, "[F");
    load_primitive_class(thread, heap, "double");
    load_primitive_class(thread, heap, "[D");
}

void start_vm(char *class_path)
{
    JAVA_HOME = getenv("JAVA_HOME");
    char *base_lib[] = {
            "java/lang/Object",
            "java/lang/Class",
            "java/lang/String",
            "java/lang/System",
            "java/lang/Integer",
            "java/lang/Float",
            "java/lang/Double",
            "java/lang/ClassLoader",
//            "java/lang/Thread",
//            "java/lang/ThreadGroup",
//            "java/io/PrintStream"
    };
    SerialHeap *heap = init_gc();
    init_instructions();
    init_native_factory();
    init_instructions_desc();
    Thread thread = create_thread(100, 100);
//    init_lib(&thread, heap);
    init_primitives(&thread, heap);
    init_lib_by_names(&thread, heap, base_lib, 8);

    ClassFile *system = load_class(&thread, heap, "java/lang/System");
    MethodInfo *init_phase1 = find_method_with_desc(&thread, heap, system, "initPhase1", "()V");
    MethodInfo *init_phase2 = find_method_with_desc(&thread, heap, system, "initPhase2", "(ZZ)I");
    MethodInfo *init_phase3 = find_method_with_desc(&thread, heap, system, "initPhase3", "()V");
    create_vm_frame_by_method(&thread, system, init_phase3, get_method_code(system->constant_pool, *init_phase3));
    create_vm_frame_by_method(&thread, system, init_phase2, get_method_code(system->constant_pool, *init_phase2));
    create_vm_frame_by_method(&thread, system, init_phase1, get_method_code(system->constant_pool, *init_phase1));
    run(&thread, heap);
//    ClassFile *jthread = load_class(&thread, heap, "java/lang/Thread");
//    MethodInfo *jthread_init = find_method_with_desc(&thread, heap, jthread, "<init>", "()V");
//    clinit_class_and_exec(&thread, heap, jthread);
//    Frame *frame = create_vm_frame_by_method(&thread, jthread, jthread_init, get_method_code(jthread->constant_pool, *jthread_init));
//    Slot *slot = create_slot();
//    slot->object_value = jthread->class_object;
//    push_slot(frame->operand_stack, slot);
//    run(&thread, heap);

//    ClassFile *jthread_group = load_class(&thread, heap, "java/lang/ThreadGroup");
//    MethodInfo *jthread_group_init = find_method_with_desc(&thread, heap, jthread_group, "<init>", "()V");
//    clinit_class_and_exec(&thread, heap, jthread_group);
//    Object *jthread_group_obj = malloc_object(heap, jthread_group);
//    Frame *jthread_group_frame = create_vm_frame_by_method(&thread, jthread_group, jthread_group_init, get_method_code(jthread_group->constant_pool, *jthread_group_init));
//    Slot *jthread_group_slot = create_slot();
//    jthread_group_slot->object_value = jthread_group_obj;
//    Slot *jthread_group_slot_this = create_slot();
//    jthread_group_slot_this->object_value = jthread_group->class_object;
//    push_slot(jthread_group_frame->operand_stack, jthread_group_slot);
//    push_slot(jthread_group_frame->operand_stack, jthread_group_slot);
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

    ClassFile *class = load_class(&thread, heap, class_path);
    clinit_class_and_exec(&thread, heap, class);

    MethodInfo *main = find_method(&thread, heap, class, "main");
    CodeAttribute *main_code = get_method_code(class->constant_pool, *main);

    if (NULL == main) exit(-1);
    create_vm_frame_by_method(&thread, class, main, main_code);
    run(&thread, heap);
}