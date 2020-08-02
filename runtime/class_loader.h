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

void set_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info);

void set_field_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

char *get_str_from_string_index(ConstantPool *constant_pool, u2 index);

void put_field_to_opstack_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

ClassFile *load_class_by_class_info_name_index(Thread *thread, SerialHeap *heap, ConstantPool *constant_pool, u2 index);

ClassFile *load_class_by_class_info(Thread *thread, SerialHeap *heap, ConstantPool *constant_pool, CONSTANT_Class_info class_info);

ClassFile *load_class_by_class_info_index(Thread *thread, SerialHeap *heap, ConstantPool *constant_pool, u2 index);

ClassFile *get_super_class(Thread *thread, SerialHeap *heap, ClassFile *class);

void create_null_object(Thread *thread, SerialHeap *heap, Frame *frame);

void create_object(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void do_invokestatic_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void do_invokespecial_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void do_invokeinterface_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index, u1 count);

void do_invokevirtual_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void init_class(Thread *thread, SerialHeap *heap, ClassFile *class);

u4 parse_method_param_count(CONSTANT_Utf8_info method_desc);

int class_is_not_init(ClassFile *class);

int class_is_in_init(ClassFile *class);

int class_is_inited(ClassFile *class);

void set_class_inited_by_frame(Frame *frame);

void init_class_and_exec(Thread *thread, SerialHeap *heap, ClassFile *class);

void print_class_info(ClassFile class);

CodeAttribute *get_method_code(ConstantPool *pool, MethodInfo method);

void create_string_object(Thread *thread, SerialHeap *heap, Frame *frame, char *str);

void create_array_reference(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

MethodInfo *find_method_iter_super_with_desc(Thread *thread, SerialHeap *heap, ClassFile **class, char *name, char *desc);

MethodInfo *find_method_with_desc(Thread *thread, SerialHeap *heap, ClassFile *class, char *name, char *desc);

MethodInfo *find_method(Thread *thread, SerialHeap *heap, ClassFile *class, char *name);

u1 *get_class_name_by_index(ConstantPool *pool, u2 index);

#endif //DISCJVM_CLASS_LOADER_H
