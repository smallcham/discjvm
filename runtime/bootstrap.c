//
// Created by wangzhanzhi on 2020/7/9.
//

#include "bootstrap.h"

char *JAVA_HOME = NULL;

void init_lib(Thread *thread, SerialHeap *heap)
{
    zip_error_t err;
    char *jmod_name = "java.base.jmod";
    char *file_path = malloc(strlen(JAVA_HOME) + strlen(jmod_name) + 8);
    sprintf(file_path, "%s/jmods/%s", JAVA_HOME, jmod_name);
    FILE *fp = fopen(file_path, "rb");
    if (NULL == fp) exit(-1);
    fseek(fp, 0, SEEK_END);
    long f_size = ftell(fp);
    fclose(fp);
    int offset = 4;
    zip_error_t error;
    zip_source_t *source = zip_source_file_create(file_path, offset, f_size - offset, &error);
    zip_t *z = zip_open_from_source(source, 0, &err);
    //Search for the file of given name
    struct zip_stat st;
    zip_stat_init(&st);
    int file_count = zip_get_num_files(z);
    for (int i = 0; i < file_count; i++) {
        zip_stat_index(z, i, 0, &st);
        if (!str_start_with(st.name, "classes/java/")) {
            continue;
        }
        //Alloc memory for its uncompressed contents
        u1 *contents = malloc(st.size);
        //Read the compressed file
        zip_file_t *f = zip_fopen(z, st.name, 0);
        zip_fread(f, contents, st.size);
        zip_fclose(f);

        ClassFile *class = load_class_by_bytes(thread, heap, contents);
        init_class_and_exec(thread, heap, class);
    }
    zip_close(z);
    free(file_path);
}

void start_vm(char *class_path)
{
    JAVA_HOME = getenv("JAVA_HOME");

    SerialHeap *heap = init_gc();
    init_instructions();
    init_instructions_desc();
    Thread thread = create_thread(100, 100);
    init_lib(&thread, heap);
    ClassFile *class = load_class(&thread, heap, class_path);
    init_class_and_exec(&thread, heap, class);

    MethodInfo *main = find_method(&thread, heap, class, "main");
    CodeAttribute *main_code = get_method_code(class->constant_pool, *main);

    if (NULL == main) exit(-1);
    create_vm_frame_by_method(&thread, class, main, main_code);
    run(&thread, heap);
}