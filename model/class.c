//
// Created by wangzhanzhi on 2020/7/31.
//

#include "class.h"

u1 *get_utf8_bytes(ConstantPool *pool, u2 index)
{
    CONSTANT_Utf8_info *info = (CONSTANT_Utf8_info*)pool[index].info;
    return info->bytes;
}

Slot *create_slot()
{
    Slot *slot = malloc(sizeof(Slot));
    slot->value = 0;
    slot->object_value = NULL;
    return slot;
}

Slot *create_slot_set_value(u8 value)
{
    Slot *slot = create_slot();
    slot->value = value;
    return slot;
}

Slot *create_slot_by_size(int size)
{
    if (size < 1) {
        return NULL;
    }
    Slot *slot = malloc(sizeof(Slot) * size);
    memset(slot, 0, sizeof(Slot) * size);
    for (int i = 0; i < size; i++) {
        slot[i].value = 0;
        slot[i].object_value = NULL;
    }
    return slot;
}

int is_array_by_name(char *name)
{
    return name[0] == '[';
}

int class_is_array(ClassFile *class)
{
    return class->class_name[0] == '[';
}

int is_array(void *ref)
{
    Array *object = ref;
    return is_array_by_name(object->class->class_name);
}

int is_array_by_raw(void *raw_class)
{
    Object *object = raw_class;
    return is_array_by_name(object->raw_class->class_name);
}

int is_object_array(void *ref)
{
    Array *object = ref;
    return is_array(ref) && object->class->class_name[1] == 'L';
}

int is_object_by_name(char *name)
{
    return name[0] == 'L';
}

int is_object_array_by_desc(char *desc)
{
    return is_array_by_name(desc) && desc[1] == 'L';
}

int is_object_array_by_raw(void *raw_class)
{
    Object *object = raw_class;
    return is_array_by_raw(raw_class) && object->raw_class->class_name[1] == 'L';
}

char *full_primitive_name(char name)
{
    if (name == 'Z') return "boolean";
    if (name == 'C') return "char";
    if (name == 'F') return "float";
    if (name == 'D') return "double";
    if (name == 'B') return "byte";
    if (name == 'S') return "short";
    if (name == 'I') return "int";
    if (name == 'J') return "long";
    if (name == 'V') return "void";
    return NULL;
}

int is_full_primitive_desc(char *desc)
{
    return strcmp(desc, "void") == 0 ||
           strcmp(desc, "boolean") == 0 ||
           strcmp(desc, "byte") == 0 ||
           strcmp(desc, "char") == 0 ||
           strcmp(desc, "short") == 0 ||
           strcmp(desc, "int") == 0 ||
           strcmp(desc, "long") == 0 ||
           strcmp(desc, "float") == 0 ||
           strcmp(desc, "double") == 0;
}

int is_primitive_desc(char *desc)
{
    return is_full_primitive_desc(desc) ||
           (desc[0] == '[' && (
                   desc[1] == 'Z' ||
                   desc[1] == 'C' ||
                   desc[1] == 'F' ||
                   desc[1] == 'D' ||
                   desc[1] == 'B' ||
                   desc[1] == 'S' ||
                   desc[1] == 'I' ||
                   desc[1] == 'J'));
}

int primitive_size(char *desc)
{
    if (strcmp(desc, "void") == 0) return sizeof(void);
    if (strcmp(desc, "boolean") == 0) return sizeof(char);
    if (strcmp(desc, "byte") == 0) return sizeof(char);
    if (strcmp(desc, "char") == 0) return sizeof(char);
    if (strcmp(desc, "short") == 0) return sizeof(short);
    if (strcmp(desc, "int") == 0) return sizeof(int);
    if (strcmp(desc, "float") == 0) return sizeof(float);
    if (strcmp(desc, "double") == 0) return sizeof(double);
    if (desc[0] == '[') {
        if (desc[1] == 'Z') return sizeof(char);
        if (desc[1] == 'C') return sizeof(char);
        if (desc[1] == 'F') return sizeof(float);
        if (desc[1] == 'D') return sizeof(double);
        if (desc[1] == 'B') return sizeof(char);
        if (desc[1] == 'S') return sizeof(short);
        if (desc[1] == 'I') return sizeof(int);
        if (desc[1] == 'J') return sizeof(long);
    }
    return -1;
}

int is_primitive_array(void *ref)
{
    Array *object = ref;
    return is_array(ref) && object->class->class_name[1] != 'L';
}

int is_primitive_array_by_raw(void *raw_class)
{
    Object *object = raw_class;
    return is_array_by_raw(raw_class) && object->raw_class->class_name[1] != 'L';
}

int is_interface(ClassFile *class)
{
    return (class->access_flags & ACC_INTERFACE) != 0;
}

int object_is_string(Object *object)
{
    return NULL != object && class_is_string(object->raw_class);
}

int class_is_string(ClassFile *class)
{
    return NULL != class && strcmp(class->class_name, "java/lang/String") == 0;
}

int is_synchronized(u2 access_flags)
{
    return 0 != (access_flags & ACC_SYNCHRONIZED);
}

int is_static(u2 access_flags)
{
    return 0 != (access_flags & ACC_STATIC);
}

int is_public(u2 access_flags)
{
    return 0 != (access_flags & ACC_PUBLIC);
}

int is_final(u2 access_flags)
{
    return 0 != (access_flags & ACC_FINAL);
}

int is_native(u2 access_flag)
{
    return 0 != (access_flag & ACC_NATIVE);
}

int is_signature_polymorphic(char *class_name, char *method_name)
{
    if (strcmp(class_name, "java/lang/invoke/MethodHandle") == 0 || strcmp(class_name, "java/lang/invoke/VarHandle") == 0) {
        if (strcmp(method_name, "invoke") == 0 || strcmp(method_name, "invokeExact") == 0) {
            return 1;
        }
    }
    return 0;
}

void format_class_name(char *class_name)
{
    for (int i = 0; i < strlen(class_name); i++) {
        if (class_name[i] == '/') { break; }
        if (class_name[i] == '.') {
            class_name[i] = '/';
        }
    }
}

char* return_type_name(char* desc)
{
    int size = strlen(desc);
    int offset = 0;
    for (int i = 0; i < size; i++) {
        if (desc[i] == ')') {
            offset = i + 1;
            break;
        }
    }
    int is_obj = desc[offset] == 'L';
    int name_size = size - offset + 1 + (desc[size - 1] == ';' ? -1 : 0) - is_obj;
    char *name = malloc(name_size);
    memcpy(name, desc + offset + is_obj, name_size - 1);
    name[name_size - 1] = '\0';
    if (name_size == 2) {
        return full_primitive_name(name[0]);
    }
    return name;
}

u1 *standard_class_name(u1 *class_name)
{
    int size = strlen(class_name);
    u1 *_class_name = malloc(size + 1);
    memcpy(_class_name, class_name, size);
    _class_name[size] = '\0';
    for (int i = 0; i < size; i++) {
        if (_class_name[i] == '/') {
            _class_name[i] = '.';
        }
    }
    return _class_name;
}

u1 *simple_class_name(u1 *class_name)
{
    int offset = 0;
    int size = strlen(class_name);
    for (int i = size - 1; i > 0; i--) {
        if (class_name[i] == '/' || class_name[i] == '.') {
            offset = i + 1;
            break;
        }
    }
    int new_size = size - offset;
    u1 *buf = malloc(new_size + 1);
    memcpy(buf, class_name + offset, new_size);
    buf[new_size] = '\0';
    return buf;
}

u1 *class_package_name(u1 *class_name)
{
    int offset = 0;
    int size = strlen(class_name);
    for (int i = size - 1; i > 0; i--) {
        if (class_name[i] == '/' || class_name[i] == '.') {
            offset = i;
            break;
        }
    }
    u1 *buf = malloc(offset + 1);
    for (int i = 0; i < offset; ++i) {
        if (class_name[i] == '/') {
            buf[i] = '.';
        } else {
            buf[i] = class_name[i];
        }
    }
    buf[offset] = '\0';
    return buf;
}

u1 *reduction_class_name(u1 *class_name)
{
    for (int i = 0; i < strlen(class_name); i++) {
        if (class_name[i] == '.') {
            class_name[i] = '/';
        }
    }
    return class_name;
}