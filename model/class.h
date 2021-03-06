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
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} ExceptionTable;

typedef struct {
    u2 start_pc;
    u2 line_number;
} LineNumberTable;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    LineNumberTable *line_number_table;
} LineNumberTableAttribute;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    ExceptionTable *exception_table;
    u2 attributes_count;
    LineNumberTableAttribute *line_number_table_attr;
    AttributeInfo *attributes;
} CodeAttribute;

typedef struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    u4 params_count;
    u4 real_params_count;
    u1 *name;
    u1 *desc;
    void *class;
    AttributeInfo *attributes;
    CodeAttribute *code_attribute;
    u1 *signature;
} MethodInfo;

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
    u2 attribute_name_index;
    u4 attribute_length;
    u2 signature_index;
} SignatureAttribute;

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
    u2 bootstrap_method_ref;
    u2 num_bootstrap_arguments;
    u2 *bootstrap_arguments;
} BootstrapMethodInfo;

typedef struct {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 num_bootstrap_methods;
    BootstrapMethodInfo *methods;
} BootstrapMethods;

typedef struct {
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
    u1 *standard_class_name;
    u1 *simple_class_name;
    u1 *package_name;
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
    void *owner;
    pthread_mutex_t *lock;
    pthread_cond_t *cond;
    int count;
} Monitor;

typedef struct {
    ClassFile *class;
    ClassFile *raw_class;
    Monitor *monitor;
    long _debug_flag;
    Slot *fields;
} Object;

typedef struct {
    ClassFile *class;
    ClassFile *raw_class;
    Monitor *monitor;
    u4 length;
    void *objects[];
} Array;

char *JAVA_HOME;
char *CLASS_PATH;
char *USER_NAME;
char *USER_HOME;
char *USER_DIR;
int VM_STACK_SIZE;
int C_STACK_SIZE;
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

char *full_primitive_name(char name);

int is_full_primitive_desc(char *desc);

int is_primitive_array_by_raw(void *raw_class);

int is_object_array_by_desc(char *desc);

int primitive_size(char *desc);

Slot *create_slot();

Slot *create_slot_set_value(u8 value);

Slot *create_slot_by_size(int size);

int object_is_string(Object *object);

int class_is_string(ClassFile *class);

int is_static(u2 access_flag);

int is_final(u2 access_flags);

int is_native(u2 access_flag);

int is_primitive_desc(char *desc);

int is_object_by_name(char *name);

int is_synchronized(u2 access_flags);

int is_signature_polymorphic(char *class_name, char *method_name);

void format_class_name(char *class_name);

int is_public(u2 access_flags);

char *return_type_name(char* desc);

u1 *standard_class_name(u1 *class_name);

u1 *reduction_class_name(u1 *class_name);

u1 *class_package_name(u1 *class_name);

u1 *simple_class_name(u1 *class_name);

#endif //DISCJVM_CLASS_H