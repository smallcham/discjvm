#include "jvm.h"

u1* get_class_bytes(char *path);

FieldInfo *get_field_by_name_and_desc_(ClassFile *class, char *name, char *desc, int _static);

ClassFile *load_class_by_bytes(Thread *thread, SerialHeap *heap, u1 *bytes)
{
    ClassFile *class = (ClassFile*)malloc(sizeof(ClassFile));
    class->init_state = CLASS_NOT_INIT;
    class->class_object = NULL;
    class->super_class = NULL;
    class->component_class = NULL;
    class->interfaces_info = NULL;
    class->object_fields_count = 0;
    class->static_fields_count = 0;
    u1 *class_file = bytes;
    class->magic = l2b_4(*(u4 *) class_file);
    class_file += sizeof(u4);
    class->minor_version = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class->major_version = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class->constant_pool_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);

    class->constant_pool = (ConstantPool*) malloc(class->constant_pool_count * sizeof(ConstantPool));

    for (u2 i = 1; i < class->constant_pool_count; i++) {
        class->constant_pool[i].tag = *(u1 *) class_file;
        switch (class->constant_pool[i].tag) {
            case CONSTANT_Class: {
                CONSTANT_Class_info *constant_class_info = (CONSTANT_Class_info *) malloc(sizeof(CONSTANT_Class_info));
                constant_class_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_class_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_class_info;
                continue;
            }
            case CONSTANT_Fieldref: {
                CONSTANT_Fieldref_info *constant_fieldref_info = (CONSTANT_Fieldref_info *) malloc(
                        sizeof(CONSTANT_Fieldref_info));
                constant_fieldref_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_fieldref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_fieldref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_fieldref_info;
                continue;
            }
            case CONSTANT_Methodref: {
                CONSTANT_Methodref_info *constant_methodref_info = (CONSTANT_Methodref_info *) malloc(
                        sizeof(CONSTANT_Methodref_info));
                constant_methodref_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_methodref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_methodref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_methodref_info;
                continue;
            }
            case CONSTANT_InterfaceMethodref: {
                CONSTANT_InterfaceMethodref_info *constant_interfacemethodref_info = (CONSTANT_InterfaceMethodref_info *) malloc(
                        sizeof(CONSTANT_InterfaceMethodref_info));
                constant_interfacemethodref_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_interfacemethodref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_interfacemethodref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_interfacemethodref_info;
                continue;
            }
            case CONSTANT_String: {
                CONSTANT_String_info *constant_string_info = (CONSTANT_String_info *) malloc(
                        sizeof(CONSTANT_String_info));
                constant_string_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_string_info->string_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_string_info;
                continue;
            }
            case CONSTANT_Integer: {
                CONSTANT_Integer_info *constant_integer_info = (CONSTANT_Integer_info *) malloc(
                        sizeof(CONSTANT_Integer_info));
                constant_integer_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_integer_info->bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                class->constant_pool[i].info = constant_integer_info;
                continue;
            }
            case CONSTANT_Float: {
                CONSTANT_Float_info *constant_float_info = (CONSTANT_Float_info *) malloc(sizeof(CONSTANT_Float_info));
                constant_float_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_float_info->bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                class->constant_pool[i].info = constant_float_info;
                continue;
            }
            case CONSTANT_Long: {
                CONSTANT_Long_info *constant_long_info = (CONSTANT_Long_info *) malloc(sizeof(CONSTANT_Long_info));
                constant_long_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_long_info->high_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_long_info->low_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                class->constant_pool[i].info = constant_long_info;
                //Long 和 Double类型需要跳过一格索引
                ++i;
                continue;
            }
            case CONSTANT_Double: {
                CONSTANT_Double_info *constant_double_info = (CONSTANT_Double_info *) malloc(
                        sizeof(CONSTANT_Double_info));
                constant_double_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_double_info->high_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_double_info->low_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                class->constant_pool[i].info = constant_double_info;
                //Long 和 Double类型需要跳过一格索引
                ++i;
                continue;
            }
            case CONSTANT_NameAndType: {
                CONSTANT_NameAndType_info *constant_nameandtype_info = (CONSTANT_NameAndType_info *) malloc(
                        sizeof(CONSTANT_NameAndType_info));
                constant_nameandtype_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_nameandtype_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_nameandtype_info->descriptor_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_nameandtype_info;
                continue;
            }
            case CONSTANT_Utf8: {
                CONSTANT_Utf8_info *constant_utf8_info = (CONSTANT_Utf8_info *) malloc(sizeof(CONSTANT_Utf8_info));
                constant_utf8_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_utf8_info->length = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_utf8_info->bytes = malloc(constant_utf8_info->length + 1);
                memcpy(constant_utf8_info->bytes, class_file, constant_utf8_info->length);
                constant_utf8_info->bytes[constant_utf8_info->length] = '\0';
                class_file += constant_utf8_info->length;
                class->constant_pool[i].info = constant_utf8_info;
                continue;
            }
            case CONSTANT_MethodHandle: {
                CONSTANT_MethodHandle_info *constant_methodhandle_info = (CONSTANT_MethodHandle_info *) malloc(
                        sizeof(CONSTANT_MethodHandle_info));
                constant_methodhandle_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_methodhandle_info->reference_kind = *(u1 *) class_file;
                class_file += sizeof(u1);
                constant_methodhandle_info->reference_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_methodhandle_info;
                continue;
            }
            case CONSTANT_MethodType: {
                CONSTANT_MethodType_info *constant_methodtype_info = (CONSTANT_MethodType_info *) malloc(
                        sizeof(CONSTANT_MethodType_info));
                constant_methodtype_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_methodtype_info->descriptor_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_methodtype_info;
                continue;
            }
            case CONSTANT_InvokeDynamic: {
                CONSTANT_InvokeDynamic_info *constant_invokedynamic_info = (CONSTANT_InvokeDynamic_info *) malloc(
                        sizeof(CONSTANT_InvokeDynamic_info));
                constant_invokedynamic_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_invokedynamic_info->bootstrap_method_attr_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_invokedynamic_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_invokedynamic_info;
                continue;
            }
            case CONSTANT_Module: {
                CONSTANT_Module_info *constant_module_info = (CONSTANT_Module_info *) malloc(
                        sizeof(CONSTANT_Module_info));
                constant_module_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_module_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_module_info;
                continue;
            }
            case CONSTANT_Package: {
                CONSTANT_Package_info *constant_package_info = (CONSTANT_Package_info *) malloc(
                        sizeof(CONSTANT_Package_info));
                constant_package_info->tag = class->constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_package_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class->constant_pool[i].info = constant_package_info;
                continue;
            }
        }
    }
    class->access_flags = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class->this_class = l2b_2(*(u2 *) class_file);
    class->class_name = get_class_name_by_index(class->constant_pool, class->this_class);
    class_file += sizeof(u2);
    class->super_class_index = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class->interfaces_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class->interfaces_count > 0) {
        u2 len = class->interfaces_count * sizeof(u2);
        class->interfaces = malloc(len);
        InterfaceInfo *interfaces_info = malloc(class->interfaces_count * sizeof(InterfaceInfo));
        for (int i = 0; i < class->interfaces_count; i++) {
            class->interfaces[i] = l2b_2(*(u2*)class_file);
            class_file += sizeof(u2);
            CONSTANT_Class_info interface_info = *(CONSTANT_Class_info*)class->constant_pool[class->interfaces[i]].info;
            interfaces_info[i].class = malloc(sizeof(ClassFile));
            interfaces_info[i].class = load_class_by_class_info_name_index(thread, heap, class->constant_pool, interface_info.name_index);
        }
        class->interfaces_info = interfaces_info;
    }
    class->fields_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class->fields_count > 0) {
        class->fields = (FieldInfo *) malloc(class->fields_count * sizeof(FieldInfo));
        for (int i = 0; i < class->fields_count; i++) {
            class->fields[i].access_flags = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class->fields[i].name_index = l2b_2(*(u2 *) class_file);
            class->fields[i].name = get_utf8_bytes(class->constant_pool, class->fields[i].name_index);
            class_file += sizeof(u2);
            class->fields[i].descriptor_index = l2b_2(*(u2 *) class_file);
            class->fields[i].desc = get_utf8_bytes(class->constant_pool, class->fields[i].descriptor_index);
            class_file += sizeof(u2);
            class->fields[i].attributes_count = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            if (class->fields[i].attributes_count > 0) {
                class->fields[i].attributes = (AttributeInfo *) malloc(
                        class->fields[i].attributes_count * sizeof(AttributeInfo));
                for (int j = 0; j < class->fields[i].attributes_count; j++) {
                    class->fields[i].attributes[j].attribute_name_index = l2b_2(*(u2 *) class_file);
                    class_file += sizeof(u2);
                    class->fields[i].attributes[j].attribute_length = l2b_4(*(u4 *) class_file);
                    class_file += sizeof(u4);
                    if (class->fields[i].attributes[j].attribute_length > 0) {
                        class->fields[i].attributes[j].info = malloc(
                                sizeof(u1) * class->fields[i].attributes[j].attribute_length);
                        memcpy(class->fields[i].attributes[j].info, class_file, class->fields[i].attributes[j].attribute_length);
                        class_file += class->fields[i].attributes[j].attribute_length;
                    }
                }
            }
        }
    }
    class->methods_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class->methods_count > 0) {
        class->methods = malloc(class->methods_count * sizeof(MethodInfo));
        for (int i = 0; i < class->methods_count; i++) {
            class->methods[i].access_flags = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class->methods[i].name_index = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class->methods[i].name = get_utf8_bytes(class->constant_pool, class->methods[i].name_index);
            class->methods[i].descriptor_index = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class->methods[i].desc = get_utf8_bytes(class->constant_pool, class->methods[i].descriptor_index);
            class->methods[i].attributes_count = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            if (class->methods[i].attributes_count > 0) {
                class->methods[i].attributes = (AttributeInfo *) malloc(class->methods[i].attributes_count * sizeof(AttributeInfo));
                for (int j = 0; j < class->methods[i].attributes_count; j++) {
                    class->methods[i].class = class;
                    class->methods[i].attributes[j].attribute_name_index = l2b_2(*(u2 *) class_file);
                    class_file += sizeof(u2);
                    class->methods[i].attributes[j].attribute_length = l2b_4(*(u4 *) class_file);
                    class_file += sizeof(u4);
                    if (class->methods[i].attributes[j].attribute_length > 0) {
                        class->methods[i].attributes[j].info = malloc(sizeof(u1) * class->methods[i].attributes[j].attribute_length);
                        memcpy(class->methods[i].attributes[j].info, class_file, class->methods[i].attributes[j].attribute_length);
                        class_file += class->methods[i].attributes[j].attribute_length;
                    }
                }
            }
            class->methods[i].params_count = parse_method_param_count(*(CONSTANT_Utf8_info*)class->constant_pool[class->methods[i].descriptor_index].info, &class->methods[i].real_params_count);
            class->methods[i].code_attribute = get_method_code(class->constant_pool, class->methods[i]);
            class->methods[i].signature = get_signature(class->constant_pool, class->methods[i]);
        }
    }
    class->attributes_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class->attributes_count > 0) {
        class->attributes = (AttributeInfo *) malloc(class->attributes_count * sizeof(AttributeInfo));
        for (int j = 0; j < class->attributes_count; j++) {
            class->attributes[j].attribute_name_index = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class->attributes[j].attribute_length = l2b_4(*(u4 *) class_file);
            class_file += sizeof(u4);
            if (class->attributes[j].attribute_length > 0) {
                class->attributes[j].info = malloc(sizeof(u1) * class->attributes[j].attribute_length);
                memcpy(class->attributes[j].info, class_file, class->attributes[j].attribute_length);
                class_file += class->attributes[j].attribute_length;
            }
        }
    }
    put_class_to_cache(&heap->class_pool, class);
    return class;
}

Object *get_rtype(Thread *thread, SerialHeap *heap, char *desc)
{
    int offset = 0;
    int length = strlen(desc);
    for (int i = 0; i < length; i++) {
        if (desc[i] == ')') {
            offset = i + 1;
            break;
        }
    }
    int size = length - offset;
    char rtype[size + 1];
    ClassFile *class;
    if (desc[offset] == 'L') {
        memcpy(rtype, desc + offset + 1, size - 1);
        rtype[size - 2] = '\0';
        class = load_class(thread, heap, rtype);
    } else {
        memcpy(rtype, desc + offset, size);
        rtype[size] = '\0';
        class = load_primitive_class(thread, heap, primitive_to_name(rtype));
    }
    return class->class_object;
}

Array *get_ptypes(Thread *thread, SerialHeap *heap, char *desc, int params_count)
{
    int length = strlen(desc);
    Array *ptypes = malloc_array(thread, heap, load_class(thread, heap, "java/lang/Class"), params_count);
    if (params_count == 0) return ptypes;
    u4 count = 0;
    int idx = 0;
    for (int i = 0; i < length; i++) {
        if (desc[i] == '(') {
            idx = i + 1;
            break;
        }
    }
    int is_array = 0;
    for (int j = idx; j < length; j++) {
        switch (desc[j]) {
            case ')': break;
            case 'B': case 'C': case 'I': case 'S': case 'Z': case 'F': case 'D': case 'J':
                if (is_array) {
                    char name[3];
                    name[0] = '[';
                    name[1] = desc[j];
                    name[2] = '\0';
                    ptypes->objects[count++] = load_primitive_class(thread, heap, name)->class_object;
                    is_array = 0;
                } else {
                    ptypes->objects[count++] = load_primitive_class(thread, heap, primitive_to_name(desc))->class_object;
                }
                continue;
            case '[': {
                is_array = 1;
                continue;
            }
            case 'L': {
                int offset = j + 1;
                for (int k = j + 1; k < length; k++) {
                    j = k;
                    if (desc[k] == ';') {
                        break;
                    } else if (desc[k] == ')') {
                        j = k - 1;
                        break;
                    }
                }
                int size = j - offset + (is_array ? 2 : 1);
                char name[size];
                name[0] = '[';
                memcpy(name, desc + offset + 1, j - offset);
                name[size] = '\0';
                ptypes->objects[count++] = is_array ? load_primitive_class(thread, heap, name)->class_object : load_class(thread, heap, name)->class_object;
                is_array = is_array - is_array;
                continue;
            }
        }
        break;
    }
    return ptypes;
}

Object *get_bootstrap_class_loader(Thread *thread, SerialHeap *heap)
{
    ClassFile *class = load_class(thread, heap, "java/lang/ClassLoader");
    if (NULL == bootstrap_class_loader && class_is_inited(class)) {
        Object *object = malloc_object(thread, heap, class);
//        bootstrap_class_loader = object;
//        new_object(thread, heap, object, "java/lang/ClassLoader", NULL);
        Slot *name = create_slot();
        name->object_value = "BootstrapLoader";
        put_object_value_field_by_name_and_desc(object, "name", "Ljava/lang/String;", name);
        put_object_value_field_by_name_and_desc(object, "parent", "Ljava/lang/ClassLoader;", NULL);
        bootstrap_class_loader = object;
    }
    return bootstrap_class_loader;
}

ClassFile *load_class(Thread *thread, SerialHeap *heap, char *full_class_name)
{
    ClassFile *class_from_cache = get_class_from_cache(heap->class_pool, full_class_name);
    if (NULL != class_from_cache) {
        return class_from_cache;
    }
    if (full_class_name[0] == '[' || is_full_primitive_desc(full_class_name) || strlen(full_class_name) == 1) {
        return load_primitive_class(thread, heap, full_class_name);
    }
    ClassFile *class = (ClassFile*)malloc(sizeof(ClassFile));

    u1 *class_file = get_class_bytes(full_class_name);
    class = load_class_by_bytes(thread, heap, class_file);

    Object *class_object = malloc_object(thread, heap, get_class_class(thread, heap));
    class_object->raw_class = class;
    class->class_object = class_object;
    return class;
}

ClassFile *load_primitive_class_by_str_array(Thread *thread, SerialHeap *heap, Array *array)
{
    char *name = malloc(array->length + 1);
    memcpy(name, (char*)array->objects, array->length);
    name[array->length] = '\0';
    ClassFile *class = load_primitive_class(thread, heap, name);
    free(name);
    return class;
}

ClassFile *load_primitive_class(Thread *thread, SerialHeap *heap, char *primitive_name)
{
    unsigned long size = strlen(primitive_name);
    char *name = malloc(size + 1);
    memcpy(name, primitive_name, size);
    name[size] = '\0';
    int is_free = 1;
    if (size == 1) {
        free(name);
        is_free = 0;
        name = full_primitive_name(primitive_name[0]);
    }
    ClassFile *class_from_cache = get_class_from_cache(heap->class_pool, name);
    if (NULL != class_from_cache) {
        if (is_free == 1) free(name);
        return class_from_cache;
    }
    ClassFile *class_class = get_class_class(thread, heap);
    ClassFile *class = malloc(sizeof(ClassFile));
    memset(class, 0, sizeof(ClassFile));
    class->magic = CLASS_MAGIC_NUMBER;
    class->class_name = (u1*)name;
    class->fields_count = 1;
    class->object_fields_count = 1;
    class->methods_count = class_class->methods_count;
    class->methods = class_class->methods;
    class->init_state = CLASS_INITED;
    put_class_to_cache(&heap->class_pool, class);

    Object *component_type;
    if (primitive_name[0] == '[' && primitive_name[1] != 'L') {
        char *_name = full_primitive_name(primitive_name[1]);
        if (NULL == _name) {
            _name = malloc(strlen(primitive_name));
            memcpy(_name, primitive_name + 1, strlen(primitive_name));
            _name[strlen(primitive_name)] = '\0';
        }
        component_type = load_primitive_class(thread, heap, _name)->class_object;
    }
    else if (primitive_name[1] == 'L') {
        char _name[strlen(primitive_name) - 1];
        memcpy(_name, primitive_name + 2, strlen(primitive_name) - 2);
        _name[strlen(primitive_name) - 2 - (_name[strlen(primitive_name) - 3] == ';' ? 1 : 0)] = '\0';
        component_type = load_class(thread, heap, _name)->class_object;
    } else {
        component_type = NULL;
    }
    Object *class_object = malloc_object(thread, heap, class_class);
    put_object_value_field_by_name_and_desc(class_object, "classLoader", "Ljava/lang/ClassLoader;", get_bootstrap_class_loader(thread, heap));
    put_object_value_field_by_name_and_desc(class_object, "componentType", "Ljava/lang/Class;", component_type);
    class_object->raw_class = class;
    class->class_object = class_object;
//    class->class_object = new_class_object(thread, heap, class, component_type);
    return class;
}

Object *new_class_object(Thread *thread, SerialHeap *heap, ClassFile *class, Object *component_type)
{
    Object *class_object = malloc_object(thread, heap, get_class_class(thread, heap));
    put_object_value_field_by_name_and_desc(class_object, "classLoader", "Ljava/lang/ClassLoader;", get_bootstrap_class_loader(thread, heap));
    put_object_value_field_by_name_and_desc(class_object, "componentType", "Ljava/lang/Class;", component_type);
    class_object->raw_class = class;
    return class_object;
}

ClassFile *load_class_ensure_init(Thread *thread, SerialHeap *heap, char *class_name)
{
    ClassFile *class = load_class(thread, heap, class_name);
    ensure_inited_class(thread, heap, class);
    return class;
}

u1 *get_class_name_by_index(ConstantPool *pool, u2 index)
{
    CONSTANT_Class_info *info = pool[index].info;
    CONSTANT_Utf8_info *name = pool[info->name_index].info;
    return name->bytes;
}

u4 parse_method_param_count(CONSTANT_Utf8_info method_desc, u4 *real_count)
{
    return parse_method_param_count_by_desc(method_desc.bytes, method_desc.length, real_count);
}

u4 parse_method_param_count_by_desc(char *desc, int length, u4 *real_count)
{
    u4 count = 0;
    u4 _real_count = 0;
    int idx = 0;
    for (int i = 0; i < length; i++) {
        if (desc[i] == '(') {
            idx = i + 1;
            break;
        }
    }
    for (int j = idx; j < length; j++) {
        switch (desc[j]) {
            case ')': break;
            case 'B': case 'C': case 'I': case 'S': case 'Z': case 'F':
                count ++;
                _real_count ++;
                continue;
            case 'D': case 'J':
                if (desc[j - 1] == '[') {
                    count ++;
                } else {
                    count += 2;
                }
                _real_count ++;
                continue;
            case '[': {
                continue;
            }
            case 'L': {
                for (int k = j + 1; k < length; k++) {
                    j = k;
                    if (desc[k] == ';') {
                        break;
                    } else if (desc[k] == ')') {
                        j = k - 1;
                        break;
                    }
                }
                count ++;
                _real_count ++;
                continue;
            }
        }
        break;
    }
    if (NULL != real_count) *real_count = _real_count;
    return count;
}



void do_invokedynamic_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    Object *caller = get_caller_frame(thread)->class->class_object;
    CONSTANT_InvokeDynamic_info dynamic_info = *(CONSTANT_InvokeDynamic_info*)frame->constant_pool[index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[dynamic_info.name_and_type_index].info;
    u1* invoke_name = get_utf8_bytes(frame->constant_pool, name_and_type_info.name_index);
    u1* invoke_desc = get_utf8_bytes(frame->constant_pool, name_and_type_info.descriptor_index);
    BootstrapMethods* bootstrap_methods = get_bootstrap_methods(frame->constant_pool, frame->class);
    if (NULL == bootstrap_methods) {
        printf_err("IllegalStateException");
        exit(-1);
    }
    BootstrapMethodInfo boot_method_info = bootstrap_methods->methods[dynamic_info.bootstrap_method_attr_index];
    CONSTANT_MethodHandle_info mh_info = *(CONSTANT_MethodHandle_info*)frame->constant_pool[boot_method_info.bootstrap_method_ref].info;

    CONSTANT_Methodref_info m_ref_info = *(CONSTANT_Methodref_info*)frame->constant_pool[mh_info.reference_index].info;
    CONSTANT_NameAndType_info mh_name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[m_ref_info.name_and_type_index].info;
    ClassFile *class = load_class_by_class_info_index(thread, heap, frame->constant_pool, m_ref_info.class_index);
    ensure_inited_class(thread, heap, class);
    u1* x = get_utf8_bytes(frame->constant_pool, mh_name_and_type_info.name_index);
    u1* t = get_utf8_bytes(frame->constant_pool, mh_name_and_type_info.descriptor_index);
//    MethodInfo *method_info = find_method_iter_super_with_desc(thread, heap, &class, x, t);

    Object *lookup = new_method_handle_lookup(thread, heap);
    Object *method_type = new_method_type(thread, heap, t);

    switch (mh_info.reference_kind) {
        case REF_invokeSpecial: {
            break;
        }
        case REF_invokeStatic: {
            Slot *_return = create_slot();
            Stack *params = create_unlimit_stack();
            push_object(params, lookup);
            push_object(params, class->class_object);
            push_slot(params, create_str_slot_set_str(thread, heap, invoke_name));
            push_object(params, method_type);
            single_invoke(thread, heap, lookup->class, "findStatic", "(Ljava/lang/Class;Ljava/lang/String;Ljava/lang/invoke/MethodType;)Ljava/lang/invoke/MethodHandle;", params, _return);
            Object *method_handle = _return->object_value;
            MethodInfo *invoke = find_method_with_desc(thread, heap, method_handle->class, "invokeExact", "[Ljava/lang/Object;");
            push_object(params, method_handle);
            push_object(params, create_str_slot_set_str(thread, heap, "Hello"));
            create_vm_frame_by_method_add_params(thread, method_handle->class, params, invoke);
            break;
        }
        case REF_invokeVirtual: {
            break;
        }
    }

//    Object *lookup = new_method_handle_lookup(thread, heap, get_caller_frame(thread)->class->class_object);
//    Object *method_type = new_method_type(thread, heap, invoke_desc);
//    Object *method_handle = new_method_handle(thread, heap, method_type, method_type);
//    Object *method_str = create_str_slot_set_str(thread, heap, invoke_name)->object_value;
//
//    Array *arr = malloc_array(thread, heap, load_primitive_class(thread, heap, "[Ljava/lang/Object"), 4);
//    arr->objects[0] = lookup;
//    arr->objects[1] = method_handle;
//    arr->objects[2] = method_type;
//    for (int i = 0; i < boot_method_info.num_bootstrap_arguments; ++i) {
//        CONSTANT_Utf8_info *str = get_utf8_info_from_string_index(frame->constant_pool, boot_method_info.bootstrap_arguments[i]);
//        arr->objects[3] = create_str_slot_set_str(thread, heap, str->bytes)->object_value;
//    }
//    MethodInfo *invoke = find_method_with_desc(thread, heap, method_handle->class, "invokeExact", "[Ljava/lang/Object;");


//    int count = method_info->params_count - 3 - boot_method_info.num_bootstrap_arguments;
//    if (count > 0) {
//        char **params_names = parse_param_types(thread, heap, method_info->desc, method_info->params_count);
//        for (int i = 3 + boot_method_info.num_bootstrap_arguments; i < method_info->params_count; i++) {
//            ClassFile *param_class = load_class(thread, heap, params_names[i]);
//            if (class_is_array(param_class)) {
//                Array *array = malloc_array(thread, heap, param_class, 0);
//                push_object(params, array);
//            } else {
//                push_object(params, malloc_object(thread, heap, param_class));
//            }
//        }
//    }

//    ClassFile *mh_native = load_class(thread, heap, "java/lang/invoke/MethodHandleNatives");
//    MethodInfo *link_call_site_method = find_method_with_desc(thread, heap, mh_native, "linkCallSite", "(Ljava/lang/Object;ILjava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/invoke/MemberName;");
//    Stack *params = create_unlimit_stack();
//    push_object(params, arr);
//    create_vm_frame_by_method_add_params(thread, class, params, invoke);
//    switch (mh_info.reference_kind) {
//        case REF_invokeInterface: {
//            printf("123");
//        }
//        case REF_invokeSpecial: {
//            ClassFile *class = frame->class;
//        }
//        case REF_invokeStatic: {
//
//
//
////            new_method_handle(thread, heap, method_type);
//
//
////            //caller
////            new_method_handle_lookup(thread, heap, frame->class->class_object);
////
////            //invokedName
////            push_slot(params, create_str_slot_set_str(thread, heap, invoke_name));
////
////            //invokedType
////            Object *method_type = new_method_type(thread, heap, t);
////            push_object(params, method_type);
////
////            //samMethodType
////            Slot *sam_method_type;
////            if (NULL == method_info->signature) {
////                sam_method_type = NULL_SLOT;
////            } else {
////                sam_method_type = create_object_slot_set_object(heap, new_method_type(thread, heap, method_info->signature));
////            }
////            push_slot(params, sam_method_type);
////
////            //implMethod
////            push_object(params, new_method_handle(thread, heap, method_type, method_type));
////
////            //instantiatedMethodType
////            push_slot(params, sam_method_type);
////
////            create_vm_frame_by_method_add_params(thread, class, params, method_info);
//            printf("123");
//        }
//        case REF_invokeVirtual: {
//            printf("123");
//        }
//    }
    printf("123");
}

void do_invokestatic_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    CONSTANT_Methodref_info method_ref_info = *(CONSTANT_Methodref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[method_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[method_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    CONSTANT_Utf8_info method_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info method_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
    printf_debug("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class_name_info.bytes, name_and_type_info.name_index, method_name_info.bytes, name_and_type_info.descriptor_index, method_desc_info.bytes);
    MethodInfo *method = find_interface_method_iter_super_with_desc(thread, heap, &class, method_name_info.bytes, method_desc_info.bytes);
    if (NULL == method) {
        printf_err("method [%s] not found", method_name_info.bytes);
        exit(-1);
    }
    Slot **slots = pop_slot_with_num(frame->operand_stack, method->params_count);
    Stack *params = create_unlimit_stack();
    for (int i = 0; i < method->params_count; i++) {
        push_slot(params, slots[i]);
    }
    Frame *new_frame;
    if (is_native(method->access_flags)) {
        new_frame = create_c_frame_and_invoke_add_params(thread, heap, frame, params, class->class_name, method);
    } else {
        new_frame = create_vm_frame_by_method_add_params(thread, class, params, method);
    }
    if (is_synchronized(method->access_flags)) {
        Object *class_object = class->class_object;
        new_frame->pop_args = class_object->monitor;
        new_frame->pop_hook = (PopHook) set_monitor_exit_hook;
        monitor_enter(class_object->monitor, thread);
    }
}

void do_invokeinterface_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index, u1 count)
{
    CONSTANT_InterfaceMethodref_info interface_ref_info = *(CONSTANT_InterfaceMethodref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[interface_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[interface_ref_info.name_and_type_index].info;
    u1 *class_name = get_utf8_bytes(frame->constant_pool, class_info.name_index);
    u1 *method_name = get_utf8_bytes(frame->constant_pool, name_and_type_info.name_index);
    u1 *method_desc = get_utf8_bytes(frame->constant_pool, name_and_type_info.descriptor_index);
    ClassFile *class = load_class(thread, heap, class_name);
    printf_debug("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class_name, name_and_type_info.name_index, method_name, name_and_type_info.descriptor_index, method_desc);
    int params_count = parse_method_param_count(*(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info, NULL);
    Slot **slots = pop_slot_with_num(frame->operand_stack, params_count + 1);
    Stack *params = create_unlimit_stack();
    for (int i = 0; i < params_count + 1; i++) {
        push_slot(params, slots[i]);
    }
    Object *object = slots[0]->object_value;
    class = object->class;
    MethodInfo *method = find_interface_method_iter_super_with_desc(thread, heap, &class, method_name, method_desc);
    if (NULL == method) {
        printf_err("method [%s] not found", method_name);
        exit(-1);
    }
    Frame *new_frame;
    if (is_native(method->access_flags)) {
        new_frame = create_c_frame_and_invoke_add_params_plus1(thread, heap, frame, params, class->class_name, method);
    } else {
        new_frame = create_vm_frame_by_method_add_params_plus1(thread, class, params, method);
    }
    if (is_synchronized(method->access_flags)) {
        new_frame->pop_args = object->monitor;
        new_frame->pop_hook = (PopHook) set_monitor_exit_hook;
        monitor_enter(object->monitor, thread);
    }
}

void do_invokespecial_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    CONSTANT_Methodref_info method_ref_info = *(CONSTANT_Methodref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[method_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[method_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    CONSTANT_Utf8_info method_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info method_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    printf_debug("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class_name_info.bytes, name_and_type_info.name_index, method_name_info.bytes, name_and_type_info.descriptor_index, method_desc_info.bytes);
    MethodInfo *method = find_method_iter_super_with_desc(thread, heap, &class, method_name_info.bytes, method_desc_info.bytes);

    int params_count = parse_method_param_count(*(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info, NULL);
    Slot **slots = pop_slot_with_num(frame->operand_stack, params_count + 1);
    Stack *params = create_unlimit_stack();
    for (int i = 0; i < params_count + 1; i++) {
        push_slot(params, slots[i]);
    }
    Object *object = slots[0]->object_value;
    if (NULL == method) {
        printf_err("method [%s] not found", method_name_info.bytes);
        exit(-1);
    }
    Frame *new_frame;
    if (is_native(method->access_flags)) {
        new_frame = create_c_frame_and_invoke_add_params_plus1(thread, heap, frame, params, class->class_name, method);
    } else {
        new_frame = create_vm_frame_by_method_add_params_plus1(thread, class, params, method);
    }
    if (is_synchronized(method->access_flags)) {
        new_frame->pop_args = object->monitor;
        new_frame->pop_hook = (PopHook) set_monitor_exit_hook;
        monitor_enter(object->monitor, thread);
    }
}

void do_invokevirtual_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    CONSTANT_Methodref_info method_ref_info = *(CONSTANT_Methodref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[method_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[method_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    CONSTANT_Utf8_info method_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info method_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    printf_debug("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class->class_name, name_and_type_info.name_index, method_name_info.bytes, name_and_type_info.descriptor_index, method_desc_info.bytes);

    int params_count = parse_method_param_count(*(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info, NULL);
    Slot **slots = pop_slot_with_num(frame->operand_stack, params_count + 1);
    Stack *params = create_unlimit_stack();
    for (int i = 0; i < params_count + 1; i++) {
        push_slot(params, slots[i]);
    }
    Object *object = slots[0]->object_value;
    class = object->class;
    MethodInfo *method = find_method_iter_super_with_desc(thread, heap, &class, method_name_info.bytes, method_desc_info.bytes);
    if (NULL == method) {
        printf_err("method [%s] not found", method_name_info.bytes);
        exit(-1);
    }
    Frame *new_frame;
    if (is_native(method->access_flags)) {
        new_frame = create_c_frame_and_invoke_add_params_plus1(thread, heap, frame, params, class->class_name, method);
    } else {
        new_frame = create_vm_frame_by_method_add_params_plus1(thread, class, params, method);
    }
    if (is_synchronized(method->access_flags)) {
        new_frame->pop_args = object->monitor;
        new_frame->pop_hook = (PopHook) set_monitor_exit_hook;
        monitor_enter(object->monitor, thread);
    }
}

void get_field_to_opstack_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    CONSTANT_Fieldref_info field_ref_info = *(CONSTANT_Fieldref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    CONSTANT_Utf8_info field_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    printf_debug("\t\t\t\t:%s.%s->%s\n", class_name_info.bytes, field_name_info.bytes, field_desc_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
    Object *object = pop_object(frame->operand_stack);
    FieldInfo *field = get_field_by_name_and_desc(class, field_name_info.bytes, field_desc_info.bytes);
    if (str_start_with(field_desc_info.bytes, "D") ||
        str_start_with(field_desc_info.bytes, "J")) {
        push_long(frame->operand_stack, object->fields[field->offset].value);
    } else {
        push_slot(frame->operand_stack, &object->fields[field->offset]);
    }
}

void get_static_field_to_opstack_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    CONSTANT_Fieldref_info field_ref_info = *(CONSTANT_Fieldref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    CONSTANT_Utf8_info field_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    printf_debug("\t\t\t\t:%s.%s->%s\n", class_name_info.bytes, field_name_info.bytes, field_desc_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
    Slot *slot = get_static_field_slot_by_name_and_desc(class, field_name_info.bytes, field_desc_info.bytes);
    if (str_start_with(field_desc_info.bytes, "D") ||
        str_start_with(field_desc_info.bytes, "J")) {
        push_long(frame->operand_stack, slot->value);
    } else {
        push_slot(frame->operand_stack, slot);
    }
}

FieldInfo *get_field_by_name_and_desc_(ClassFile *class, char *name, char *desc, int _static)
{
    while (NULL != class) {
        for (int i = 0; i < class->fields_count; i++) {
            if (strcmp(class->fields[i].name, name) == 0 && strcmp(class->fields[i].desc, desc) == 0) {
                if (_static) {
                    if (is_static(class->fields[i].access_flags)) {
                        return &class->fields[i];
                    }
                } else {
                    if (!is_static(class->fields[i].access_flags)) {
                        return &class->fields[i];
                    }
                }
            }
        }
        if (NULL != class->super_class) class = class->super_class;
        else return NULL;
    }
    return NULL;
}

FieldInfo *get_field_by_name_and_desc(ClassFile *class, char *name, char *desc)
{
    return get_field_by_name_and_desc_(class, name, desc, 0);
}

FieldInfo *get_field_by_name(ClassFile *class, char *name)
{
    for (int i = 0; i < class->fields_count; i++) {
        if (strcmp(class->fields[i].name, name) == 0) return &class->fields[i];
    }
    return NULL;
}

Array *get_str_field_array_value_by_object(Object *object)
{
    FieldInfo *field = get_field_by_name_and_desc(object->raw_class, "value", "[B");
    Array *array = object->fields[field->offset].object_value;
    return array;
}

char *get_str_field_value_by_object(Object *object)
{
    return get_str_field_value_by_object_and_name(object, "value");
}

char *get_str_field_value_by_object_and_name(Object *object, char *name)
{
    FieldInfo *field = get_field_by_name_and_desc(object->raw_class, name, "[B");
    Array *array = object->fields[field->offset].object_value;
    if (NULL == array) return NULL;
    char *str = malloc(array->length + 1);
    memcpy(str, (char*)array->objects, array->length);
    str[array->length] = '\0';
    return str;
}

u8 get_field_value_by_name_and_desc(Object *object, char *name, char *desc)
{
    FieldInfo *field = get_field_by_name_and_desc(object->raw_class, name, desc);
    return object->fields[field->offset].value;
}

void *get_field_object_value_by_name_and_desc(Object *object, char *name, char *desc)
{
    FieldInfo *field = get_field_by_name_and_desc(object->class, name, desc);
    return object->fields[field->offset].object_value;
}

FieldInfo *get_static_field_by_name_and_desc(ClassFile *class, char *name, char *desc)
{
    return get_field_by_name_and_desc_(class, name, desc, 1);
}

Slot *get_static_field_slot_by_name_and_desc(ClassFile *class, char *name, char *desc)
{
    while (NULL != class) {
        for (int i = 0; i < class->fields_count; i++) {
            if (strcmp(class->fields[i].name, name) == 0 && strcmp(class->fields[i].desc, desc) == 0) {
                if (is_static(class->fields[i].access_flags)) {
                    return &class->static_fields[class->fields[i].offset];
                }
            }
        }
        if (NULL != class->super_class) class = class->super_class;
        else return NULL;
    }
    return NULL;
}

void put_field_by_name_and_desc(Object *object, char *name, char *desc, Slot *value)
{
    FieldInfo *field = get_field_by_name_and_desc(object->class, name, desc);
    object->fields[field->offset] = *value;
}

void put_str_field(Thread *thread, SerialHeap *heap, Object *object, char *str)
{
    u8 len = NULL == str ? 0 : strlen(str);
    put_str_field_with_length(thread, heap, object, str, len);
}

void put_str_field_with_length(Thread *thread, SerialHeap *heap, Object *object, char *str, int length)
{
    FieldInfo *field = get_field_by_name_and_desc(object->class, "value", "[B");
    Array *array = malloc_array_by_type_size(thread, heap, load_class(thread, heap, "[B"), length, sizeof(char));
    char *_str = (char *) array->objects;
    if (NULL == str) {
        array->objects[0] = NULL;
    } else {
        for (int i = 0; i < length; i++) {
            _str[i] = str[i];
        }
    }
    Slot *slot = create_object_slot_set_object(heap, array);
    object->fields[field->offset] = *slot;
}

void put_value_field_by_name_and_desc(Object *object, char *name, char *desc, int value)
{
    FieldInfo *field = get_field_by_name_and_desc(object->class, name, desc);
    object->fields[field->offset].value = value;
}

void put_object_value_field_by_name_and_desc(Object *object, char *name, char *desc, void *value)
{
    FieldInfo *field = get_field_by_name_and_desc(object->class, name, desc);
    object->fields[field->offset].object_value = value;
}

Object *get_component_type(void *object)
{
    Object *obj = object;
    return get_field_object_value_by_name_and_desc(obj->class->class_object, "componentType", "Ljava/lang/Class;");
}

void put_static_field_by_name_and_desc(ClassFile *class, char *name, char *desc, void *value)
{
    FieldInfo *field = get_static_field_by_name_and_desc(class, name, desc);
    class->static_fields[field->offset].object_value = value;
}

void put_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info)
{
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info field_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    printf_debug("\t\t\t\t:%s.%s = %s\n", class_name_info.bytes, field_name_info.bytes, field_desc_info.bytes);
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
    FieldInfo *field = get_field_by_name_and_desc(class, field_name_info.bytes, field_desc_info.bytes);
    if (str_start_with(field_desc_info.bytes, "D") ||
        str_start_with(field_desc_info.bytes, "J")) {
        u8 value = pop_long(frame->operand_stack);
        Object *object = pop_object(frame->operand_stack);
        object->fields[field->offset].value = value;
    } else {
        Slot *slot = pop_slot(frame->operand_stack);
        Object *object = pop_object(frame->operand_stack);
        object->fields[field->offset] = *slot;
    }
}

void put_static_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info)
{
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info field_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    printf_debug("\t\t\t\t:%s.%s = %s\n", class_name_info.bytes, field_name_info.bytes, field_desc_info.bytes);
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
    FieldInfo *field = get_static_field_by_name_and_desc(class, field_name_info.bytes, field_desc_info.bytes);
    if (str_start_with(field_desc_info.bytes, "D") ||
        str_start_with(field_desc_info.bytes, "J")) {
        class->static_fields[field->offset].value = pop_long(frame->operand_stack);
    } else {
        class->static_fields[field->offset] = *pop_slot(frame->operand_stack);
    }
}

char *get_str_from_string_index(ConstantPool *constant_pool, u2 index)
{
    CONSTANT_String_info string_info = *(CONSTANT_String_info*)constant_pool[index].info;
    return get_utf8_bytes(constant_pool, string_info.string_index);
}

CONSTANT_Utf8_info *get_utf8_info_from_string_index(ConstantPool *constant_pool, u2 index)
{
    CONSTANT_String_info string_info = *(CONSTANT_String_info*)constant_pool[index].info;
    return (CONSTANT_Utf8_info*)constant_pool[string_info.string_index].info;
}

u4 get_u4_value_from_index(ConstantPool *constant_pool, u2 index)
{
    CONSTANT_Integer_info info = *(CONSTANT_Integer_info*)constant_pool[index].info;
    return info.bytes;
}

void put_static_field_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    put_static_field(thread, heap, frame, *(CONSTANT_Fieldref_info *) frame->constant_pool[index].info);
}

void put_field_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    put_field(thread, heap, frame, *(CONSTANT_Fieldref_info *) frame->constant_pool[index].info);
}

void create_null_object(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_object(frame->operand_stack, NULL);
}

u1 *get_array_class_name_by_name_str(u1 *name)
{
    if (!str_start_with(name, "[")) {
        return name;
    }
    switch (name[1]) {
        case 'V': return "java/lang/Void";
        case 'Z': return "java/lang/Boolean";
        case 'B': return "java/lang/Byte";
        case 'C': return "java/lang/Character";
        case 'S': return "java/lang/Short";
        case 'I': return "java/lang/Integer";
        case 'J': return "java/lang/Long";
        case 'F': return "java/lang/Float";
        case 'D': return "java/lang/Double";
    }
    return name;
}

u1 *get_primitive_array_class_name_by_name_str(u1 *name)
{
    if (!str_start_with(name, "[")) {
        return NULL;
    }
    switch (name[1]) {
        case 'V': return "void";
        case 'Z': return "boolean";
        case 'B': return "byte";
        case 'C': return "char";
        case 'S': return "short";
        case 'I': return "int";
        case 'J': return "long";
        case 'F': return "float";
        case 'D': return "double";
        case 'L': {
            name += 2;
            unsigned long size = strlen(name);
            if (name[size - 1] == ';') {
                u1 *_name = malloc(size);
                memcpy(_name, name, size - 1);
                _name[size - 1] = '\0';
                return _name;
            } else {
                return name;
            }
        }
    }
    return NULL;
}

void create_object_with_backpc(Thread *thread, SerialHeap *heap, Frame *frame, u2 index, int back)
{
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[index].info;
    ClassFile *class = load_class_by_class_info_name_index(thread, heap, frame->constant_pool, class_info.name_index);
    if (class_is_not_init(class)) {
        back_pc(frame, back);
        init_class(thread, heap, class);
        return;
    }
    push_object(frame->operand_stack, malloc_object(thread, heap, class));
}

void create_object_with_class_name_and_backpc(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, int back)
{
    ClassFile *class = load_class(thread, heap, class_name);
    if (class_is_not_init(class)) {
        back_pc(frame, back);
        init_class(thread, heap, class);
        return;
    }
    push_object(frame->operand_stack, malloc_object(thread, heap, class));
}

void create_object(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    create_object_with_backpc(thread, heap, frame, index, 3);
}

void create_array_by_type(Thread *thread, SerialHeap *heap, Frame *frame, u1 type, int count)
{
    char *desc;
    int type_size;
    switch (type) {
        case 4:
            desc = "[Z";
            type_size = sizeof(char);
            break;
        case 5:
            desc = "[C";
            type_size = sizeof(char);
            break;
        case 6:
            desc = "[F";
            type_size = sizeof(float);
            break;
        case 7:
            desc = "[D";
            type_size = sizeof(double);
            break;
        case 8:
            desc = "[B";
            type_size = sizeof(char);
            break;
        case 9:
            desc = "[S";
            type_size = sizeof(short);
            break;
        case 10:
            desc = "[I";
            type_size = sizeof(int);
            break;
        case 11:
            desc = "[J";
            type_size = sizeof(long);
            break;
    }
    ClassFile *class = load_class(thread, heap, desc);
    Array *array = malloc_array_by_type_size(thread, heap, class, count, type_size);
    push_object(frame->operand_stack, array);
}

void create_string_object(Thread *thread, SerialHeap *heap, Frame *frame, char *str)
{
    create_string_object_with_length(thread, heap, frame, str, strlen(str));
}

void create_string_object_with_length(Thread *thread, SerialHeap *heap, Frame *frame, char *str, int length)
{
    ClassFile *class = load_class(thread, heap, "java/lang/String");
    if (class_is_not_init(class)) {
        back_pc(frame, 2);
        init_class(thread, heap, class);
        return;
    }
    Object *object = malloc_object(thread, heap, class);
    put_str_field_with_length(thread, heap, object, str, length);
    push_object(frame->operand_stack, object);
}

void create_string_object_without_back(Thread *thread, SerialHeap *heap, Frame *frame, char *str)
{
    ClassFile *class = load_class(thread, heap, "java/lang/String");
    Object *object = malloc_object(thread, heap, class);
    put_str_field(thread, heap, object, str);
    push_object(frame->operand_stack, object);
}

void create_array_reference(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    ClassFile *class = load_class_by_class_info_index(thread, heap, frame->constant_pool, index);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
    int count = pop_int(frame->operand_stack);
    char *_arr_name = malloc(strlen(class->class_name) + 2);
    sprintf(_arr_name, "[L%s", class->class_name);
    Array *arr = malloc_array(thread, heap, load_primitive_class(thread, heap, _arr_name), count);
    push_object(frame->operand_stack, arr);

    if (NULL != arr->class->class_object) {
        put_field_by_name_and_desc(arr->class->class_object, "componentType", "Ljava/lang/Class;", create_object_slot_set_object(heap, class->class_object));
    }

    free(_arr_name);
}

ClassFile *load_class_by_class_info_name_index(Thread *thread, SerialHeap *heap, ConstantPool *constant_pool, u2 index)
{
    return load_class(thread, heap, get_utf8_bytes(constant_pool, index));
}

ClassFile *load_class_by_class_info(Thread *thread, SerialHeap *heap, ConstantPool *constant_pool, CONSTANT_Class_info class_info)
{
    return load_class_by_class_info_name_index(thread, heap, constant_pool, class_info.name_index);
}

ClassFile *load_class_by_class_info_index(Thread *thread, SerialHeap *heap, ConstantPool *constant_pool, u2 index)
{
    return load_class_by_class_info(thread, heap, constant_pool, *(CONSTANT_Class_info*)constant_pool[index].info);
}

ClassFile *get_super_class(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    if (class->super_class_index == 0 || is_interface(class)) return NULL;
    return load_class_by_class_info(thread, heap, class->constant_pool, *(CONSTANT_Class_info*)class->constant_pool[class->super_class_index].info);
}

int class_is_not_init(ClassFile *class)
{
    return class->init_state >= CLASS_NOT_INIT;
}

int class_is_in_init(ClassFile *class)
{
    return class->init_state <= CLASS_IN_INIT;
}

int class_is_inited(ClassFile *class)
{
    return class->init_state <= CLASS_INITED;
}

void set_class_inited_by_frame(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame)
{
    frame->class->init_state = CLASS_INITED;
}

void set_monitor_exit_hook(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame)
{
    monitor_exit(frame->pop_args, thread);
}

void init_static_fields(ClassFile *class)
{
    for (int i = 0; i < class->fields_count; i++) {
        if (!is_final(class->fields[i].access_flags) || !is_static(class->fields[i].access_flags)) {
            continue;
        }
        for (int j = 0; j < class->fields[i].attributes_count; j++) {
            if (strcmp(get_utf8_bytes(class->constant_pool, class->fields[i].attributes[j].attribute_name_index), "ConstantValue") == 0) {
                ConstantValue value = *(ConstantValue*)malloc(sizeof(ConstantValue));
                value.attribute_name_index = class->fields[i].attributes[j].attribute_name_index;
                value.attribute_length = class->fields[i].attributes[j].attribute_length;
                value.constant_value_index = l2b_2(*(u2*)class->fields[i].attributes[j].info);
                switch (class->fields[i].desc[0]) {
                    case 'Z': case 'B': case 'C': case 'S': case 'I': case 'F': {
                        CONSTANT_Integer_info info = *(CONSTANT_Integer_info*)class->constant_pool[value.constant_value_index].info;
//                        put_int_field_to_map(&class->static_fields, class->fields[i].name, class->fields[i].desc, info.bytes);
                        class->static_fields[class->fields[i].offset].value = info.bytes;
                        break;
                    }
                    case 'J': case 'D':{
                        CONSTANT_Double_info info = *(CONSTANT_Double_info*)class->constant_pool[value.constant_value_index].info;
                        class->static_fields[class->fields[i].offset].value = (long)(info.high_bytes & 0xffff0000) | (long)(info.low_bytes & 0x0000ffff);
                        break;
                    }
                    case 'L':{
                        class->static_fields[class->fields[i].offset].object_value = get_str_from_string_index(class->constant_pool, value.constant_value_index);
                        break;
                    }
                }
            }
        }
    }
}

void init_fields(ClassFile *class)
{
    ClassFile *super = class->super_class;
    int object_fields_offset = NULL != super ? super->object_fields_count : 0;
    int static_fields_offset = 0;
    for (int i = 0; i < class->fields_count; i++) {
        if (!is_static(class->fields[i].access_flags)) {
            class->fields[i].offset = object_fields_offset;
            object_fields_offset++;
        } else {
            class->fields[i].offset = static_fields_offset;
            static_fields_offset++;
        }
    }
    class->object_fields_count = object_fields_offset;
    class->static_fields_count = static_fields_offset;
    class->static_fields = create_slot_by_size(class->static_fields_count);
    init_static_fields(class);
}

void init_class(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    if (class_is_inited(class)) return;
    printf_debug("\t\t\t\t-> jump <clinit> - %s\n", class->class_name);
    class->init_state = CLASS_IN_INIT;
    get_class_class(thread, heap);

    ClassFile *super = get_super_class(thread, heap, class);
    if (NULL != super) {
        if (class_is_not_init(super)) {
            init_class(thread, heap, super);
        }
        class->super_class = super;
    }
    init_fields(class);
    MethodInfo *clinit = find_method_with_desc(thread, heap, class, "<clinit>", "()V");
    if (NULL != clinit) {
        create_vm_frame_by_method_add_hook(thread, class, clinit, (PopHook) set_class_inited_by_frame);
    } else {
        class->init_state = CLASS_INITED;
    }
}

Object *new_object(Thread *thread, SerialHeap *heap, Object *this, char *class_name, Stack *params)
{
    return new_object_by_desc(thread, heap, this, class_name, "()V", params);
}

Object *new_object_by_desc(Thread *thread, SerialHeap *heap, Object *this, char *class_name, char *desc, Stack *params)
{
    ClassFile *class = load_class(thread, heap, class_name);
    ensure_inited_class(thread, heap, class);
    this = (NULL == this) ? malloc_object(thread, heap, class) : this;
    params = NULL == params ? create_unlimit_stack() : params;
    int size = params->size;
    Slot **slots = pop_slot_with_num(params, size);
    push_object(params, this);
    for (int i = 0; i < size; i++) {
        push_slot(params, slots[i]);
    }
//    MethodInfo *init_method = find_method_with_desc(thread, heap, class, "<init>", desc);
//    create_vm_frame_by_method_add_params_plus1(thread, class, params, init_method);
    single_invoke(thread, heap, class, "<init>", desc, params, NULL);
    return this;
}

Object *new_method_handle_lookup(Thread *thread, SerialHeap *heap)
{
    Slot *_return = create_slot();
    single_invoke(thread, heap, load_class_ensure_init(thread, heap, "java/lang/invoke/MethodHandles"), "lookup", "()Ljava/lang/invoke/MethodHandles$Lookup;", NULL, _return);
//    Object *lookup = new_object_by_desc(thread, heap, NULL, "java/lang/invoke/MethodHandles$Lookup", "(Ljava/lang/Class;)V", params);
    return _return->object_value;
}

Object *new_method_type(Thread *thread, SerialHeap *heap, char *desc)
{
    u4 count;
    parse_method_param_count_by_desc(desc, strlen(desc), &count);
    Stack *params = create_unlimit_stack();
    ClassFile *rtype_class = load_class_ensure_init(thread, heap, return_type_name(desc));
    push_object(params, rtype_class->class_object);
    char **param_names = parse_param_types(thread, heap, desc, count);
    Array *ptypes = malloc_array(thread, heap, load_primitive_class(thread, heap, "[Ljava/lang/Class"), count);
    for (int i = 0; i < count; i++) {
        ptypes->objects[i] = load_class_ensure_init(thread, heap, param_names[i])->class_object;
    }
    push_object(params, ptypes);
    ClassFile *class = load_class_ensure_init(thread, heap, "java/lang/invoke/MethodType");
    Slot *_return = create_slot();
    single_invoke(thread, heap, class, "methodType", "(Ljava/lang/Class;[Ljava/lang/Class;)Ljava/lang/invoke/MethodType;", params, _return);
//    Object *method_type = new_object_by_desc(thread, heap, NULL, "", "(Ljava/lang/Class;[Ljava/lang/Class;)V", params);
    put_object_value_field_by_name_and_desc(_return->object_value, "methodDescriptor", "Ljava/lang/String;", desc);
    return _return->object_value;
}

Object *new_method_handle(Thread *thread, SerialHeap *heap, Object *method_type, Object *from_method_type)
{
    Stack *params = create_unlimit_stack();
    push_object(params, method_type);
    push_object(params, new_object_by_desc(thread, heap, NULL, "java/lang/invoke/LambdaForm", "(Ljava/lang/invoke/MethodType;)V", params));
    return new_object_by_desc(thread, heap, NULL, "java/lang/invoke/MethodHandle", "(Ljava/lang/invoke/MethodType;Ljava/lang/invoke/LambdaForm;)V", params);
}

void clinit_class_and_exec(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    printf_debug("[clinit] - %s\n", class->class_name);
    init_class(thread, heap, class);
    run(thread, heap);
}

u1* get_class_bytes(char *path)
{
    if (str_start_with(path, "java/") ||
        str_start_with(path, "jdk/") ||
        str_start_with(path, "sun/")) {
        return load_from_jmod("java.base.jmod", path);
    }
    FILE *fp = fopen(path, "rb");
    fseek(fp, 0, SEEK_END);
    long f_size = ftell(fp);
    u1 *class_file = (u1 *) malloc(f_size * sizeof(u1));
    rewind(fp);
    fread(class_file, f_size, 1, fp);
    fclose(fp);
    return class_file;
}

MethodInfo *get_method_info_by_ref(Thread *thread, SerialHeap *heap, ConstantPool *pool, CONSTANT_Methodref_info ref)
{
    CONSTANT_NameAndType_info name_and_type = *(CONSTANT_NameAndType_info*)pool[ref.name_and_type_index].info;
    u1 *method_name = get_utf8_bytes(pool, name_and_type.name_index);
    u1 *method_desc = get_utf8_bytes(pool, name_and_type.descriptor_index);
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)pool[ref.class_index].info;
    ClassFile *class = load_class(thread, heap, get_utf8_bytes(pool, class_info.name_index));
    return find_method_iter_super_with_desc(thread, heap, &class, method_name, method_desc);
}

u1 *get_signature(ConstantPool *pool, MethodInfo method)
{
    if (method.attributes_count == 0) return NULL;
    int index = -1;
    for (int i = 0; i < method.attributes_count; i++) {
        CONSTANT_Utf8_info info = *(CONSTANT_Utf8_info *) pool[method.attributes[i].attribute_name_index].info;
        if (strcmp(info.bytes, "Signature") == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return NULL;
    AttributeInfo info = method.attributes[index];
    SignatureAttribute *signature = malloc(sizeof(SignatureAttribute));
    u1 *bytes = info.info;
    signature->attribute_name_index = info.attribute_name_index;
    signature->attribute_length = info.attribute_length;
    signature->signature_index = l2b_2(*(u2*)bytes);
    return get_utf8_bytes(pool, signature->signature_index);
}

CodeAttribute *get_method_code(ConstantPool *pool, MethodInfo method)
{
    if (method.attributes_count == 0) return NULL;
    int index = -1;
    for (int i = 0; i < method.attributes_count; i++) {
        CONSTANT_Utf8_info info = *(CONSTANT_Utf8_info *) pool[method.attributes[i].attribute_name_index].info;
        if (strcmp(info.bytes, "Code") == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) return NULL;
    AttributeInfo code_info = method.attributes[index];
    CodeAttribute *code_attribute = (CodeAttribute*) malloc(sizeof(CodeAttribute));
    code_attribute->attribute_name_index = code_info.attribute_name_index;
    code_attribute->attribute_length = code_info.attribute_length;
    u1 *bytes = code_info.info;
    code_attribute->max_stack = l2b_2(*(u2*) bytes);
    bytes += sizeof(u2);
    code_attribute->max_locals = l2b_2(*(u2*) bytes);
    bytes += sizeof(u2);
    code_attribute->code_length = l2b_4(*(u4*) bytes);
    bytes += sizeof(u4);
    if (code_attribute->code_length > 0) {
        code_attribute->code = malloc(code_attribute->code_length);
        memcpy(code_attribute->code, bytes, code_attribute->code_length);
        bytes += code_attribute->code_length;
    }
    code_attribute->exception_table_length = l2b_2(*(u2*) bytes);
    bytes += sizeof(u2);
    if (code_attribute->exception_table_length > 0) {
        u8 exception_table_len = code_attribute->exception_table_length * sizeof(u8);
        code_attribute->exception_table = malloc(exception_table_len);
        memcpy(code_attribute->exception_table, bytes, exception_table_len);
        bytes += exception_table_len;
    }
    code_attribute->attributes_count = l2b_2(*(u2*) bytes);
    bytes += sizeof(u2);
    if (code_attribute->attributes_count > 0) {
        code_attribute->attributes = malloc(sizeof(AttributeInfo) * code_attribute->attributes_count);
        for (int i = 0; i < code_attribute->attributes_count; i++) {
            code_attribute->attributes[i].attribute_name_index = l2b_2(*(u2*) bytes);
            bytes += sizeof(u2);
            code_attribute->attributes[i].attribute_length = l2b_4(*(u4*) bytes);
            bytes += sizeof(u4);
            code_attribute->attributes[i].info = malloc(code_attribute->attributes[i].attribute_length);
            memcpy(code_attribute->attributes[i].info, bytes, code_attribute->attributes[i].attribute_length);
            bytes += code_attribute->attributes[i].attribute_length;
        }
    }
    return code_attribute;
}

BootstrapMethods *get_bootstrap_methods(ConstantPool *pool, ClassFile *class)
{
    for (int i = 0; i < class->attributes_count; i++) {
        if (strcmp(get_utf8_bytes(pool, class->attributes[i].attribute_name_index), "BootstrapMethods") != 0) continue;
        BootstrapMethods *bootstrap_methods = (BootstrapMethods*)malloc(sizeof(BootstrapMethods));
        u1 *bytes = class->attributes[i].info;
        bootstrap_methods->attribute_name_index = class->attributes[i].attribute_name_index;
        bootstrap_methods->attribute_length = class->attributes[i].attribute_name_index;
        bootstrap_methods->num_bootstrap_methods = l2b_2(*(u2*)bytes);
        bytes += sizeof(u2);
        bootstrap_methods->methods = malloc(sizeof(BootstrapMethodInfo) * bootstrap_methods->num_bootstrap_methods);
        for (int j = 0; j < bootstrap_methods->num_bootstrap_methods; j++) {
            bootstrap_methods->methods[j].bootstrap_method_ref = l2b_2(*(u2*)bytes);
            bytes += sizeof(u2);
            bootstrap_methods->methods[j].num_bootstrap_arguments = l2b_2(*(u2*)bytes);
            bytes += sizeof(u2);
            bootstrap_methods->methods[j].bootstrap_arguments = malloc(sizeof(u2) * bootstrap_methods->methods[j].num_bootstrap_arguments);
            for (int k = 0; k < bootstrap_methods->methods[j].num_bootstrap_arguments; k++) {
                bootstrap_methods->methods[j].bootstrap_arguments[k] = l2b_2(*(u2*)bytes);
                bytes += sizeof(u2);
            }
        }
        return bootstrap_methods;
    }
    return NULL;
}

ExceptionsAttribute *get_exception_handle(ConstantPool *pool, MethodInfo *method, ClassFile *class)
{
    for (int i = 0; i < class->attributes_count; i++) {
        if (strcmp(get_utf8_bytes(pool, class->attributes[i].attribute_name_index), "Exceptions") != 0) continue;
        ExceptionsAttribute *exceptions_attribute = (ExceptionsAttribute*)malloc(sizeof(ExceptionsAttribute));
        u1 *bytes = class->attributes[i].info;
        exceptions_attribute->attribute_name_index = class->attributes[i].attribute_name_index;
        exceptions_attribute->attribute_length = class->attributes[i].attribute_name_index;
        exceptions_attribute->number_of_exceptions = l2b_2(*(u2*)bytes);
        bytes += sizeof(u2);
        exceptions_attribute->exception_index_table = malloc(sizeof(u2) * exceptions_attribute->number_of_exceptions);
        for (int j = 0; j < exceptions_attribute->number_of_exceptions; j++) {
            exceptions_attribute->exception_index_table[j] = l2b_2(*(u2*)bytes);
            bytes += sizeof(u2);
        }
        return exceptions_attribute;
    }
    return NULL;
}

ClassFile *get_class_by_attr_index(Thread *thread, SerialHeap *heap, ConstantPool *pool, u2 index)
{
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)pool[index].info;
    return load_class(thread, heap, get_utf8_bytes(pool, class_info.name_index));
}

void print_class_info(ClassFile class)
{
    printf("General Infomation:\n");

    CONSTANT_Class_info constant_class_info = *(CONSTANT_Class_info*)class.constant_pool[class.this_class].info;
    CONSTANT_Utf8_info this_class = *(CONSTANT_Utf8_info*)class.constant_pool[constant_class_info.name_index].info;

    CONSTANT_Class_info constant_super_class_info = *(CONSTANT_Class_info*)class.constant_pool[class.super_class_index].info;
    CONSTANT_Utf8_info super_class = *(CONSTANT_Utf8_info*)class.constant_pool[constant_super_class_info.name_index].info;

    printf("\tMagicNumber: %X\n\tVersion: %d.%d (%d)\n\tConstantPoolCount: %d"
           "\n\tAccessFlags: %#x\n\tThisClass: #%d <%s>\n\tSuperClass: #%d <%s>"
           "\n\tInterfaceCount: %d\n\tFieldCount: %d\n\tMethodCount: %d\n\tAttributeCount: %d"
           "\n", class.magic, class.major_version, class.minor_version, class.major_version - 44,
           class.constant_pool_count, class.access_flags, class.this_class, this_class.bytes,
           class.super_class_index, super_class.bytes, class.interfaces_count, class.fields_count, class.methods_count, class.attributes_count);


    printf("Constant Pool:\n");
    for (int i = 1; i < class.constant_pool_count; i++) {
        switch (class.constant_pool[i].tag) {
            case CONSTANT_Class:
                printf("\t[%2d] CONSTANT_Class_info\n", i);
                continue;
            case CONSTANT_Fieldref:
                printf("\t[%2d] CONSTANT_Fieldref_info\n", i);
                continue;
            case CONSTANT_Methodref:
                printf("\t[%2d] CONSTANT_Methodref_info\n", i);
                continue;
            case CONSTANT_InterfaceMethodref:
                printf("\t[%2d] CONSTANT_InterfaceMethodref_info\n", i);
                continue;
            case CONSTANT_String:
                printf("\t[%2d] CONSTANT_String_info\n", i);
                continue;
            case CONSTANT_Integer:
                printf("\t[%2d] CONSTANT_Integer_info\n", i);
                continue;
            case CONSTANT_Float:
                printf("\t[%2d] CONSTANT_Float_info\n", i);
                continue;
            case CONSTANT_Long:
                printf("\t[%2d] CONSTANT_Long_info\n", i);
                continue;
            case CONSTANT_Double:
                printf("\t[%2d] CONSTANT_Double_info\n", i);
                continue;
            case CONSTANT_NameAndType:
                printf("\t[%2d] CONSTANT_NameAndType_info\n", i);
                continue;
            case CONSTANT_Utf8:
                printf("\t[%2d] CONSTANT_Utf8_info\n", i);
                continue;
            case CONSTANT_MethodHandle:
                printf("\t[%2d] CONSTANT_MethodHandle_info\n", i);
                continue;
            case CONSTANT_MethodType:
                printf("\t[%2d] CONSTANT_MethodType_info\n", i);
                continue;
            case CONSTANT_InvokeDynamic:
                printf("\t[%2d] CONSTANT_InvokeDynamic_info\n", i);
                continue;
            case CONSTANT_Module:
                printf("\t[%2d] CONSTANT_Module_info\n", i);
                continue;
            case CONSTANT_Package:
                printf("\t[%2d] CONSTANT_Package_info\n", i);
                continue;
        }
    }

    printf("Interfaces:\n");
    for (int i = 0; i < class.interfaces_count; i++) {
        CONSTANT_Class_info interface = *(CONSTANT_Class_info *)class.constant_pool[class.interfaces[i]].info;
        CONSTANT_Utf8_info interface_name = *(CONSTANT_Utf8_info*)class.constant_pool[interface.name_index].info;
        printf("\t[%d] %s #%d\n", i, interface_name.bytes, interface.name_index);
    }
    printf("Fields:\n");
    for (int i = 0; i < class.fields_count; i++) {
        CONSTANT_Utf8_info field_name = *(CONSTANT_Utf8_info*)class.constant_pool[class.fields[i].name_index].info;
        printf("\t[%d] %s #%d [%#x]\n", i, field_name.bytes, class.fields[i].name_index, class.fields[i].access_flags);
    }
    printf("Methods:\n");
    for (int i = 0; i < class.methods_count; i++) {
        CONSTANT_Utf8_info method_name = *(CONSTANT_Utf8_info*)class.constant_pool[class.methods[i].name_index].info;
        printf("\t[%d] %s #%d [%#x]\n", i, method_name.bytes, class.methods[i].name_index, class.methods[i].access_flags);
        for (int j = 0; j < class.methods[i].attributes_count; j++) {
            CONSTANT_Utf8_info attribute_name = *(CONSTANT_Utf8_info*)class.constant_pool[class.methods[i].attributes[j].attribute_name_index].info;
            printf("\t\t[%d] %s #%d %d\n", j, attribute_name.bytes, class.methods[i].attributes[j].attribute_name_index, class.methods[i].attributes[j].attribute_length);
            if (strcmp(attribute_name.bytes, "Code") == 0) {
                CodeAttribute *code = get_method_code(class.constant_pool, class.methods[i]);
                printf("\t\t\t[%d] MaxStack: %d | CodeLength: %d\n", j, code->max_stack, code->code_length);
                for (int k = 0; k < code->code_length; k++) {
                    printf("\t\t\t%#X\n", code->code[k]);
                }
            }
        }
    }
    printf("Attributes:\n");
    for (int i = 0; i < class.attributes_count; i++) {
        CONSTANT_Utf8_info attribute_name = *(CONSTANT_Utf8_info*)class.constant_pool[class.attributes[i].attribute_name_index].info;
        printf("\t[%d] %s #%d Length: %d\n", i, attribute_name.bytes, class.attributes[i].attribute_name_index, class.attributes[i].attribute_length);
    }
}

MethodInfo *find_method_iter_super_with_desc(Thread *thread, SerialHeap *heap, ClassFile **class, char *name, char *desc) {
    if (is_array_by_name((*class)->class_name)) {
        *class = get_class_class(thread, heap);
        MethodInfo *method = find_method_iter_super_with_desc(thread, heap, class, name, desc);
        if (NULL != method) return method;
        *class = load_class(thread, heap, "java/lang/Object");
    }
    while (NULL != class)
    {
        MethodInfo *method = find_method_with_desc(thread, heap, *class, name, desc);
        if (NULL != method) return method;
        *class = get_super_class(thread, heap, *class);
    }
    return NULL;
}

MethodInfo *find_interface_method_iter_super_with_desc(Thread *thread, SerialHeap *heap, ClassFile **class, char *name, char *desc) {
    ClassFile *back_class = *class;
    MethodInfo *method = find_method_iter_super_with_desc(thread, heap, class, name, desc);
    if (NULL != method) return method;
    for (int i = 0; i < back_class->interfaces_count; i++) {
        ClassFile *interface = back_class->interfaces_info[i].class;
        method = find_method_iter_super_with_desc(thread, heap, &interface, name, desc);
        if (NULL != method) {
            *class = interface;
            return method;
        }
        *class = get_super_class(thread, heap, *class);
    }
    return NULL;
}

MethodInfo *find_method_with_desc(Thread *thread, SerialHeap *heap, ClassFile *class, char *name, char *desc) {
    for (int i = 0; i < class->methods_count; i++)
    {
        CONSTANT_Utf8_info method_info = *(CONSTANT_Utf8_info*)class->constant_pool[class->methods[i].name_index].info;
        CONSTANT_Utf8_info method_desc = *(CONSTANT_Utf8_info*)class->constant_pool[class->methods[i].descriptor_index].info;
        if (strcmp(method_info.bytes, name) == 0 && strcmp(method_desc.bytes, desc) == 0) return &class->methods[i];
    }
    return NULL;
}

//TODO 逻辑未完成, 需要测试调整
int is_instance_of(ClassFile *s, ClassFile *t)
{
    if (NULL == s || NULL == t) return 0;
    if (s == t) return 1;
    if (!class_is_array(s)) {
        if (!is_interface(s)) {
            if (!is_interface(t)) {
                return is_parent(s, t);
            } else {
                return is_impl_interface(s, t);
            }
        } else {
            if (!is_interface(t)) {
                return strcmp(t->class_name, "java/lang/Object") == 0;
            } else {
                return is_impl_interface(s, t);
            }
        }
    } else {
        ClassFile *sc = s->component_class;
        if (!class_is_array(t)) {
            if (!is_interface(t)) {
                return strcmp(t->class_name, "java/lang/Object") == 0;
            } else {
                return strcmp(t->class_name, "java/lang/Cloneable") == 0 || strcmp(t->class_name, "java/io/Serializable") == 0;
            }
        } else {
            ClassFile *tc = t->component_class;
            return tc == sc || is_instance_of(sc, tc);
        }
    }
    return 0;
}

int is_impl_interface(ClassFile *this, ClassFile *interface)
{
    ClassFile *temp = this;
    while (NULL != temp) {
        if (strcmp(temp->class_name, "java/lang/Object") == 0) {
            return 0;
        }
        for (int j = 0; j < temp->interfaces_count; j++) {
            ClassFile *source = temp->interfaces_info[j].class;
            if (source == interface) {
                return 1;
            }
            if (source->interfaces_count > 0) return is_impl_interface(source, interface);
        }
        temp = temp->super_class;
    }
    return 0;
}

int is_parent(ClassFile *this, ClassFile *super)
{
    ClassFile *temp = this;
    while (1) {
        if (NULL == temp) return 0;
        if (strcmp(temp->class_name, "java/lang/Object") == 0) {
            if (this == super) return 1;
            else return 0;
        }
        if (temp == super) return 1;
        temp = temp->super_class;
    }
}

MethodInfo *find_method(Thread *thread, SerialHeap *heap, ClassFile *class, char *name) {
    for (int i = 0; i < class->methods_count; i++)
    {
        CONSTANT_Utf8_info method_info = *(CONSTANT_Utf8_info*)class->constant_pool[class->methods[i].name_index].info;
        if (strcmp(method_info.bytes, name) == 0) return &class->methods[i];
    }
    return NULL;
}

Slot *create_object_slot(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    Slot *slot = create_slot();
    slot->object_value = malloc_object(thread, heap, class);
    return slot;
}

Slot *create_object_slot_set_object(SerialHeap *heap, void *object)
{
    Slot *slot = create_slot();
    slot->object_value = object;
    return slot;
}

Slot *create_str_slot_set_str(Thread *thread, SerialHeap *heap, char *str)
{
    ClassFile *class = load_class(thread, heap, "java/lang/String");
    Object *object = malloc_object(thread, heap, class);
    put_str_field(thread, heap, object, str);
    return create_object_slot_set_object(heap, object);
}

void ensure_inited_class(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    if (class_is_not_init(class)) {
        Thread *new_thread = create_thread_with_jthread(VM_STACK_SIZE, C_STACK_SIZE, thread->jthread);
        new_thread->pthread = thread->pthread;
        clinit_class_and_exec(new_thread, heap, class);
    }
}

ClassFile *get_class_class(Thread *thread, SerialHeap *heap)
{
    ClassFile *class_class = load_class(thread, heap, "java/lang/Class");
    ensure_inited_class(thread, heap, class_class);
    return class_class;
}

char** parse_param_types(Thread *thread, SerialHeap *heap, char *desc, int count)
{
    if (count == 0) return NULL;
    char **param_types = malloc(sizeof(char*) * count);
    int desc_size = strlen(desc);
    int params_count = 0;
    int _offset = 0;
    int _end = 0;
    for (int k = 0; k < desc_size; ++k) {
        if (desc[k] == '(') {
            _offset = k + 1;
        }
        else if (desc[k] == ')') {
            _end = k;
            break;
        }
    }
    while (_offset < _end) {
        char *full_name = NULL;
        while (1) {
            if (desc[_offset] == ')' || desc[_offset] == ';') break;
            else if (desc[_offset] == '[') {
                if (desc[_offset + 1] == 'L') {
                    int _count = 0;
                    char name[100];
                    for (int s = _offset; s < desc_size; ++s) {
                        if (desc[s] == ';' || desc[s] == ')') {
                            _offset = s;
                            name[_count] = '\0';
                            full_name = name;
                            break;
                        } else {
                            name[_count++] = desc[s];
                        }
                    }
                } else {
                    char name[3];
                    name[0] = '[';
                    name[1] = desc[_offset + 1];
                    name[2] = '\0';
                    _offset += 2;
                    full_name = name;
                    break;
                }
            } else if (desc[_offset] == 'L') {
                int _flag = _offset + 1;
                int _count = 0;
                char name[100];
                for (int s = _flag; s < desc_size; ++s) {
                    if (desc[s] == ';' || desc[s] == ')') {
                        name[_count] = '\0';
                        full_name = name;
                        _offset = s;
                        break;
                    } else {
                        name[_count++] = desc[s];
                    }
                }
            } else {
                char name[2];
                name[0] = desc[_offset];
                name[1] = '\0';
                full_name = name;
                _offset += 1;
                break;
            }
        }
        if (NULL != full_name) {
            int size = strlen(full_name);
            char *_name = malloc(size + 1);
            memcpy(_name, full_name, size);
            _name[size] = '\0';
            param_types[params_count++] = _name;
        } else {
            _offset ++;
        }
    }
    return param_types;
}

Frame *get_caller_frame(Thread *thread)
{
    return get_stack_offset(thread->vm_stack, 2);
}