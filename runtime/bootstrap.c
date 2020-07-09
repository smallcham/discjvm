//
// Created by wangzhanzhi on 2020/7/9.
//

#include "bootstrap.h"

void start_vm(char *class_path)
{
    SerialHeap *heap = init_gc();
    init_instructions();
    ClassFile class = load_class(heap, class_path);
    MethodInfo *main = find_method(class, "main");
    if (NULL == main) exit(-1);
    invoke_method(heap, &class, *main);
}