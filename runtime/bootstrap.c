//
// Created by wangzhanzhi on 2020/7/9.
//

#include "bootstrap.h"

char *JAVA_HOME = NULL;

void start_vm(char *class_path)
{
    JAVA_HOME = getenv("JAVA_HOME");

    SerialHeap *heap = init_gc();
    init_instructions();
    init_instructions_desc();
    Thread thread = create_thread(100, 100);
    ClassFile *class = load_class(&thread, heap, class_path);
    init_class_and_exec(&thread, heap, class);

    MethodInfo *main = find_method(&thread, heap, class, "main");
    CodeAttribute *main_code = get_method_code(class->constant_pool, *main);

    if (NULL == main) exit(-1);
    create_vm_frame_by_method(&thread, class, main, main_code);
    invoke_method(&thread, heap);
}