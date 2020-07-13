//
// Created by wangzhanzhi on 2020/7/9.
//

#include "bootstrap.h"

void start_vm(char *class_path)
{
    SerialHeap *heap = init_gc();
    init_instructions();
    Thread thread = create_thread(100, 100);
    ClassFile *class = load_class(&thread, heap, class_path);
    init_class(&thread, heap, class);
    invoke_method(thread, heap);

    MethodInfo *main = find_method(*class, "main");
    CodeAttribute *main_code = get_method_code(*main);

    if (NULL == main) exit(-1);
    create_vm_frame_by_method(&thread, class->constant_pool, main, main_code);
    invoke_method(thread, heap);
}