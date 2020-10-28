//
// Created by wangzhanzhi on 2020/6/22.
//

#ifndef DISCJVM_JVM_H
#define DISCJVM_JVM_H
#define CLASS_INITED 0
#define CLASS_IN_INIT 1
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

ClassFile *load_primitive_class_by_str_array(Thread *thread, SerialHeap *heap, Array *array);

ClassFile *load_class_ensure_init(Thread *thread, SerialHeap *heap, char *class_name);

Object *new_class_object(Thread *thread, SerialHeap *heap, ClassFile *class, Object *component_type);

void put_static_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info);

void put_static_field_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void put_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info);

void put_str_field(Thread *thread, SerialHeap *heap, Object *object, char *str);

CONSTANT_Utf8_info *get_utf8_info_from_string_index(ConstantPool *constant_pool, u2 index);

void put_str_field_with_length(Thread *thread, SerialHeap *heap, Object *object, char *str, int length);

void create_string_object_with_length(Thread *thread, SerialHeap *heap, Frame *frame, char *str, int length);

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

void do_invokedynamic_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void do_invokestatic_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void do_invokespecial_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void do_invokeinterface_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index, u1 count);

void do_invokevirtual_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index);

void init_class(Thread *thread, SerialHeap *heap, ClassFile *class);

u4 parse_method_param_count(CONSTANT_Utf8_info method_desc, u4 *real_count);

int class_is_not_init(ClassFile *class);

int class_is_in_init(ClassFile *class);

int class_is_inited(ClassFile *class);

void set_class_inited_by_frame(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame);

void set_monitor_exit_hook(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame);

void clinit_class_and_exec(Thread *thread, SerialHeap *heap, ClassFile *class);

void print_class_info(ClassFile class);

MethodInfo *get_method_info_by_ref(Thread *thread, SerialHeap *heap, ConstantPool *pool, CONSTANT_Methodref_info ref);

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

Slot *get_static_field_slot_by_name_and_desc(ClassFile *class, char *name, char *desc);

FieldInfo *get_static_field_by_name_and_desc(ClassFile *class, char *name, char *desc);

Array *get_str_field_array_value_by_object(Object *object);

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

Slot *create_object_slot(Thread *thread, SerialHeap *heap, ClassFile *class);

Slot *create_object_slot_set_object(SerialHeap *heap, void *object);

int is_parent(ClassFile *this, ClassFile *super);

int is_impl_interface(ClassFile *this, ClassFile *interface);

MethodInfo *find_interface_method_iter_super_with_desc(Thread *thread, SerialHeap *heap, ClassFile **class, char *name, char *desc);

Slot *create_str_slot_set_str(Thread *thread, SerialHeap *heap, char *str);

void put_static_field_by_name_and_desc(ClassFile *class, char *name, char *desc, void *value);

BootstrapMethods *get_bootstrap_methods(ConstantPool *pool, ClassFile *class);

Object *new_object_by_desc(Thread *thread, SerialHeap *heap, Object *this, char *class_name, char *desc, Stack *params);

Object *new_object(Thread *thread, SerialHeap *heap, Object *this, char *class_name, Stack *params);

Object *new_method_type(Thread *thread, SerialHeap *heap, char *desc);

Object *new_method_handle_lookup(Thread *thread, SerialHeap *heap);

Object *new_method_handle(Thread *thread, SerialHeap *heap, Object *method_type, Object *from_method_type);

Object *get_rtype(Thread *thread, SerialHeap *heap, char *desc);

Array *get_ptypes(Thread *thread, SerialHeap *heap, char *desc, int params_count);

u4 parse_method_param_count_by_desc(char *desc, int length, u4 *real_count);

char *get_str_field_value_by_object_and_name(Object *object, char *name);

void *get_resolved_method_name_from_mh(Object *method_handle);

ExceptionsAttribute *get_exception_handle(ConstantPool *pool, MethodInfo *method, ClassFile *class);

ClassFile *get_class_by_attr_index(Thread *thread, SerialHeap *heap, ConstantPool *pool, u2 index);

void ensure_inited_class(Thread *thread, SerialHeap *heap, ClassFile *class);

char** parse_param_types(Thread *thread, SerialHeap *heap, char *desc, int count);

u1 *get_signature(ConstantPool *pool, MethodInfo method);

ClassFile *get_class_class(Thread *thread, SerialHeap *heap);

Object *get_component_type(void *object);

Frame *get_caller_frame(Thread *thread);

void throw_exception(Thread *thread, SerialHeap *heap, Object *exception);

void throw_exception_by_name(Thread *thread, SerialHeap *heap, char *exception_name);

void throw_exception_by_name_and_msg(Thread *thread, SerialHeap *heap, char *exception_name, char *msg);

void throw_exception_with_msg(Thread *thread, SerialHeap *heap, Object *exception, char *msg);

Object *new_object_add_frame(Thread *thread, SerialHeap *heap, Object *this, char *class_name, Stack *params);

Object *new_object_by_desc_add_frame(Thread *thread, SerialHeap *heap, Object *this, char *class_name, char *desc, Stack *params);

#endif //DISCJVM_JVM_H
