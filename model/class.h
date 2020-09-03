#ifndef DISCJVM_CLASS_H
#define DISCJVM_CLASS_H

#include "base_type.h"
#include "constant_class.h"
#include "hash_map.h"

typedef struct {
    /**
     *  CONSTANT_Class 7
        CONSTANT_Fieldref 9
        CONSTANT_Methodref 10
        CONSTANT_InterfaceMethodref 11
        CONSTANT_String 8
        CONSTANT_Integer 3
        CONSTANT_Float 4
        CONSTANT_Long 5
        CONSTANT_Double 6
        CONSTANT_NameAndType 12
        CONSTANT_Utf8 1
        CONSTANT_MethodHandle 15
        CONSTANT_MethodType 16
        CONSTANT_InvokeDynamic 18
     */
    u1 tag;
    void *info;
} ConstantPool;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 *info;
} AttributeInfo;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constant_value_index;
} ConstantValue;

typedef struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo *attributes;
    u1 *name;
    u1 *desc;
    u2 offset;
} FieldInfo;

typedef struct {
    void *class;
} InterfaceInfo;

typedef struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    u4 params_count;
    u1 *name;
    u1 *desc;
    AttributeInfo *attributes;
} MethodInfo;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    struct {
        u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
    } *exception_table;
    u2 attributes_count;
    AttributeInfo *attributes;
} CodeAttribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    struct {
        u2 start_pc;
        u2 line_number;
    } *line_number_table;
} LineNumberTableAttribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_table_length;
    struct {
        u2 start_pc;
        u2 length;
        u2 name_index;
        u2 descriptor_index;
        u2 index;
        u1 *name;
        u1 *desc;
    } local_variable_table[];
} LocalVariableTableAttribute;

//__attribute__ ((packed))

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_type_table_length;
    struct {
        u2 start_pc;
        u2 length;
        u2 name_index;
        u2 signature_index;
        u2 index;
    } *local_variable_type_table;
} LocalVariableTypeTableAttribute;

typedef struct {

} StackMapFrame;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_entries;
    StackMapFrame *entries;
} StackMapTable;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 *exception_index_table;
} ExceptionsAttribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    struct {
        u2 inner_class_info_index;
        u2 outer_class_info_index;
        u2 inner_name_index;
        u2 inner_class_access_flags;
    } *classes;
} InnerClassesAttribute;

typedef struct {
    int is_string;
    u8 value;
    void *object_value;
} Slot;

typedef struct {
    FieldInfo *field_info;
    Slot *slot;
} Field;

typedef struct {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    ConstantPool *constant_pool; // [constant_pool_count - 1]
    u2 access_flags;
    u2 this_class;
    u1 *class_name;
    u2 super_class_index;
    u2 interfaces_count;
    u2 *interfaces;
    InterfaceInfo *interfaces_info;
    u2 fields_count;
    FieldInfo *fields;
    u2 object_fields_count;
    u2 static_fields_count;
    u2 methods_count;
    MethodInfo *methods;
    u2 attributes_count;
    AttributeInfo *attributes;
    Slot *static_fields;
    void *class_object;
    void *component_class;
    void *super_class;
    u1 init_state;
} ClassFile;

typedef struct {
    ClassFile *class;
    ClassFile *raw_class;
    Slot *fields;
} Object;

typedef struct {
    ClassFile *class;
    ClassFile *raw_class;
    u4 length;
    void *raw_object;
    Object *objects[];
} Array;

//typedef struct{
//    u2 *class_name;
//    u2 access_flags;
//    struct Class *super_class_index;
//    u2 interfaces_count;
//    struct Class *interfaces;
//    u2 fields_count;
//    u2 constant_pool_count;
//    ConstantPool *constant_pool;
//    Slot *runtime_constant_pool;
//    Slot *fields;
//    u2 methods_count;
//    MethodInfo *methods;
//    u2 attributes_count;
//    AttributeInfo *attributes;
//    u1 init_state;
//} Class;

char *JAVA_HOME;
HashMap *VM_OPTS;
Slot *NULL_SLOT;

u1 *get_utf8_bytes(ConstantPool *pool, u2 index);

int is_interface(ClassFile *class);

int is_array(void *ref);

int is_array_by_name(char *name);

int is_array_by_raw(void *raw_class);

int class_is_array(ClassFile *class);

int is_object_array(void *ref);

int is_object_array_by_raw(void *raw_class);

int is_primitive_array(void *ref);

int is_primitive_array_by_raw(void *raw_class);

Slot *create_slot();

Slot *create_slot_set_value(u4 value);

Slot *create_slot_by_size(int size);

#endif //DISCJVM_CLASS_H