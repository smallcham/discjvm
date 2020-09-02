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
#include "../share/native/native_factory.h"
#include "../runtime/opcode.h"
#include "../runtime/jmod.h"

Object *bootstrap_class_loader;

ClassFile *load_class_by_bytes(Thread *thread, SerialHeap *heap, u1 *bytes);

ClassFile *load_class(Thread *thread, SerialHeap *heap, char *full_class_name);

ClassFile *load_primitive_class(Thread *thread, SerialHeap *heap, char *primitive_name);

void put_static_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info);

void put_static_field_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void put_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info);

void put_str_field(SerialHeap *heap, Object *object, char *str);

void put_field_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

char *get_str_from_string_index(ConstantPool *constant_pool, u2 index);

void get_static_field_to_opstack_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void get_field_to_opstack_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

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

void set_class_inited_by_frame(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame);

void clinit_class_and_exec(Thread *thread, SerialHeap *heap, ClassFile *class);

void print_class_info(ClassFile class);

CodeAttribute *get_method_code(ConstantPool *pool, MethodInfo method);

void create_string_object(Thread *thread, SerialHeap *heap, Frame *frame, char *str);

void create_string_object_without_back(Thread *thread, SerialHeap *heap, Frame *frame, char *str);

void create_array_by_type(Thread *thread, SerialHeap *heap, Frame *frame, u1 type, int count);

void create_array_reference(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

MethodInfo *find_method_iter_super_with_desc(Thread *thread, SerialHeap *heap, ClassFile **class, char *name, char *desc);

MethodInfo *find_method_with_desc(Thread *thread, SerialHeap *heap, ClassFile *class, char *name, char *desc);

MethodInfo *find_method(Thread *thread, SerialHeap *heap, ClassFile *class, char *name);

u1 *get_class_name_by_name_str(char name);

u1 *get_primitive_array_class_name_by_name_str(u1 *name);

u1 *get_class_name_by_index(ConstantPool *pool, u2 index);

void put_field_by_name_and_desc(Object *object, char *name, char *desc, Slot *value);

void put_value_field_by_name_and_desc(Object *object, char *name, char *desc, int value);

void put_object_value_field_by_name_and_desc(Object *object, char *name, char *desc, void *value);

//Slot *get_field_from_map(HashMap **map, u1 *name, u1 *desc);

Object *get_bootstrap_class_loader(Thread *thread, SerialHeap *heap);

void init_fields(ClassFile *class);

void init_static_fields(ClassFile *class);

FieldInfo *get_field_by_name_and_desc(ClassFile *class, char *name, char *desc);

FieldInfo *get_static_field_by_name_and_desc(ClassFile *class, char *name, char *desc);

char *get_str_field_value_by_object(Object *object);

FieldInfo *get_field_by_name(ClassFile *class, char *name);

u8 get_field_value_by_name_and_desc(Object *object, char *name, char *desc);

void *get_field_object_value_by_name_and_desc(Object *object, char *name, char *desc);

//void put_field_to_map(HashMap **map, u1 *name, u1 *desc, Slot *value);
//
//void put_int_field_to_map(HashMap **map, u1 *name, u1 *desc, int value);
//
//void put_long_field_to_map(HashMap **map, u1 *name, u1 *desc, int lower, int higher);
//
//void put_str_field_to_map(HashMap **map, u1 *name, u1 *desc, char *value);

u4 get_u4_value_from_index(ConstantPool *constant_pool, u2 index);

void create_object_with_backpc(Thread *thread, SerialHeap *heap, Frame *frame, u2 index, int back);

void create_object_with_class_name_and_backpc(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, int back);

//char *get_str_field_from_map(HashMap **map);

int is_instance_of(ClassFile *source, ClassFile *target);

Slot *create_object_slot(SerialHeap *heap, ClassFile *class);

Slot *create_object_slot_set_object(SerialHeap *heap, void *object);

#endif //DISCJVM_CLASS_LOADER_H
