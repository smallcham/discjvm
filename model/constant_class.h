#ifndef DISCJVM_CONSTANT_CLASS_H
#define DISCJVM_CONSTANT_CLASS_H

#define CONSTANT_Class              7
#define CONSTANT_Fieldref           9
#define CONSTANT_Methodref          10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String             8
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_NameAndType        12
#define CONSTANT_Utf8               1
#define CONSTANT_MethodHandle       15
#define CONSTANT_MethodType         16
#define CONSTANT_InvokeDynamic      18
#define CONSTANT_Module             19
#define CONSTANT_Package            20

//魔数
#define CLASS_MAGIC_NUMBER 0xCAFEBABE

#define ACC_PUBLIC          0x0001
#define ACC_PRIVATE         0x0002
#define ACC_FINAL           0x0010
#define ACC_SUPER           0x0020
#define ACC_INTERFACE       0x0200
#define ACC_ABSTRACT        0x0400
#define ACC_SYNTHETIC       0x1000
#define ACC_ANNOTATION      0x2000
#define ACC_ENUM            0x4000
#define ACC_MODULE          0x8000
#define ACC_STRICT          0x0800
#define ACC_NATIVE          0x0100
#define ACC_VARARGS         0x0080
#define ACC_SYNCHRONIZED    0x0080
#define ACC_BRIDGE          0x0040
#define ACC_PROTECTED       0x0004
#define ACC_STATIC          0x0008

typedef struct {
    u1 tag;
    u2 name_index;
} CONSTANT_Class_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct {
    u1 tag;
    u2 string_index;
} CONSTANT_String_info;

typedef struct {
    u1 tag;
    u4 bytes;
} CONSTANT_Integer_info;

typedef struct {
    u1 tag;
    u4 bytes;
} CONSTANT_Float_info;

typedef struct {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
} CONSTANT_Long_info;

typedef struct {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
} CONSTANT_Double_info;

typedef struct {
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct {
    u1 tag;
    u2 length;
    u1 *bytes;
} CONSTANT_Utf8_info;

typedef struct {
    u1 tag;
    u1 reference_kind;
    u2 reference_index;
} CONSTANT_MethodHandle_info;

typedef struct {
    u1 tag;
    u2 descriptor_index;
} CONSTANT_MethodType_info;

typedef struct {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
} CONSTANT_Dynamic_info;

typedef struct {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
} CONSTANT_InvokeDynamic_info;

typedef struct {
    u1 tag;
    u2 name_index;
} CONSTANT_Module_info;

typedef struct {
    u1 tag;
    u2 name_index;
} CONSTANT_Package_info;

#endif //DISCJVM_CONSTANT_CLASS_H