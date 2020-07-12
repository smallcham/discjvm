//
// Created by wangzhanzhi on 2020/6/22.
//

#ifndef DISCJVM_CLASS_LOADER_H
#define DISCJVM_CLASS_LOADER_H
#define CLASS_INITED 1
#define CLASS_IN_INIT 0
#define CLASS_NOT_INIT 2

#include "../util/endian.h"
#include "../util/string_util.h"
#include "../share/gc/serial/serial_heap.h"
#include "../runtime/opcode.h"
#include "../runtime/jmod.h"

ClassFile *load_class(Thread *thread, SerialHeap *heap, char *full_class_name);

ClassFile *load_class_and_init_if_not(Thread *thread, SerialHeap *heap, char *full_class_name);

ClassFile *load_class_and_init_if_not_by_class_info(Thread *thread, SerialHeap *heap, ConstantPool *constant_pool, CONSTANT_Class_info class_info);

void set_static_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info);

void set_static_field_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u1 index);

void init_class(Thread *thread, SerialHeap *heap, ClassFile *class);

void print_class_info(ClassFile class);

CodeAttribute *get_method_code(MethodInfo method);

MethodInfo *find_method(ClassFile class, char *name);

#endif //DISCJVM_CLASS_LOADER_H
