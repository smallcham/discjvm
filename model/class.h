#include "base_type.h"
#include "constant_class.h"

#ifndef DISCJVM_CLASS_H
#define DISCJVM_CLASS_H

//魔数
#define CLASS_MAGIC_NUMBER 0xCAFEBABE
//public
#define ACC_PUBLIC 0x0001
//final
#define ACC_FINAL 0x0010
//当用到invokespecial指令时，需要对父类方法做特殊处理
#define ACC_SUPER 0x0020
//接口标识
#define ACC_INTERFACE 0x0200
//abstract
#define ACC_ABSTRACT 0x0400
//synthetic
#define ACC_SYNTHETIC 0x1000
//注解类型
#define ACC_ANNOTATION 0x2000
//枚举类型
#define ACC_ENUM 0x4000

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
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo *attributes;
} FieldInfo;

typedef struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
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
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    ConstantPool *constant_pool; // [constant_pool_count - 1]
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces; // [interfaces_count]
    u2 fields_count;
    FieldInfo *fields; // [fields_count]
    u2 methods_count;
    MethodInfo *methods; // [methods_count]
    u2 attributes_count;
    AttributeInfo *attributes; // [attributes_count]
} ClassFile;

#endif //DISCJVM_CLASS_H