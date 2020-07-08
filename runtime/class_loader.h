//
// Created by wangzhanzhi on 2020/6/22.
//

#ifndef DISCJVM_CLASS_LOADER_H
#define DISCJVM_CLASS_LOADER_H
#include "../util/endian.h"
#include "../util/string_util.h"
#include "../share/gc/serial/serial_heap.h"
#include "../runtime/jmod.h"

ClassFile load_class(SerialHeap *heap, char *full_class_name);
void link_class(SerialHeap *heap, ClassFile *class);
void print_class_info(ClassFile class);
CodeAttribute get_method_code(MethodInfo method);
MethodInfo *find_method(ClassFile class, char *name);

#endif //DISCJVM_CLASS_LOADER_H
