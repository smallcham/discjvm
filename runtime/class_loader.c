#include "class_loader.h"

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
                constant_methodhandle_info->reference_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_methodhandle_info->reference_kind = *(u1 *) class_file;
                class_file += sizeof(u1);
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
                constant_invokedynamic_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_invokedynamic_info->bootstrap_method_attr_index = l2b_2(*(u2 *) class_file);
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
                class->methods[i].attributes = (AttributeInfo *) malloc(
                        class->methods[i].attributes_count * sizeof(AttributeInfo));
                for (int j = 0; j < class->methods[i].attributes_count; j++) {
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
            class->methods[i].params_count = parse_method_param_count(*(CONSTANT_Utf8_info*)class->constant_pool[class->methods[i].descriptor_index].info);
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

Object *get_bootstrap_class_loader(Thread *thread, SerialHeap *heap)
{
    if (NULL == bootstrap_class_loader) {
        Object *object = malloc_object(heap, load_class(thread, heap, "java/lang/ClassLoader"));
        Slot *name = create_slot();
        name->object_value = "BootstrapLoader";
        put_object_value_field_by_name_and_desc(object, "name", "Ljava/lang/String;", name);
        put_object_value_field_by_name_and_desc(object, "parent", "Ljava/lang/Classloader;", NULL);
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
    if (full_class_name[0] == '[') {
        return load_primitive_class(thread, heap, full_class_name);
    }
    ClassFile *class = (ClassFile*)malloc(sizeof(ClassFile));
    class->init_state = CLASS_NOT_INIT;

    u1 *class_file = get_class_bytes(full_class_name);
    class = load_class_by_bytes(thread, heap, class_file);

    Object *class_object = malloc_object(heap, load_class(thread, heap, "java/lang/Class"));
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
    ClassFile *class_from_cache = get_class_from_cache(heap->class_pool, primitive_name);
    if (NULL != class_from_cache) {
        return class_from_cache;
    }
    unsigned long size = strlen(primitive_name);
    char *name = malloc(size + 1);
    strcpy(name, primitive_name);
    name[size] = '\0';
    ClassFile *class = malloc(sizeof(ClassFile));
    memset(class, 0, sizeof(ClassFile));
    class->magic = CLASS_MAGIC_NUMBER;
    class->class_name = (u1*)name;
    class->fields_count = 1;
//    class->fields = malloc(sizeof(FieldInfo));
//    class->fields->name = (u1*)"value";
//    class->fields->offset = 0;
//    class->fields->desc = "[";
    class->object_fields_count = 1;
    class->init_state = CLASS_INITED;
    put_class_to_cache(&heap->class_pool, class);

    Object *class_object = malloc_object(heap, load_class(thread, heap, "java/lang/Class"));
    class_object->raw_class = class;
    class->class_object = class_object;

//    if (NULL != class->class_object && is_array_by_name(class->class_name)) {
//        ClassFile *component_class = class->component_class;
//        put_field_by_name_and_desc(class->class_object, "componentType", "Ljava/lang/Class;", create_object_slot_set_object(heap, component_class->class_object));
//    }

//    u1 *component_name = get_primitive_array_class_name_by_name_str(name);
//    if (NULL != component_name) {
//        ClassFile *component_class = load_class(thread, heap, component_name);
//        class->component_class = component_class;
//    }
    return class;
}

u1 *get_class_name_by_index(ConstantPool *pool, u2 index)
{
    CONSTANT_Class_info *info = pool[index].info;
    CONSTANT_Utf8_info *name = pool[info->name_index].info;
    return name->bytes;
}

u4 parse_method_param_count(CONSTANT_Utf8_info method_desc)
{
    u4 count = 0;
    int idx = 0;
    for (int i = 0; i < method_desc.length; i++) {
        if (method_desc.bytes[i] == '(') {
            idx = i + 1;
            break;
        }
    }
    for (int j = idx; j < method_desc.length; j++) {
        switch (method_desc.bytes[j]) {
            case ')': break;
            case 'B': case 'C': case 'I': case 'S': case 'Z': case 'F':
                count ++;
                continue;
            case 'D': case 'J':
                count += 2;
                continue;
            case '[': {
                continue;
            }
            case 'L': {
                for (int k = j + 1; k < method_desc.length; k++) {
                    j = k;
                    if (method_desc.bytes[k] == ';') {
                        break;
                    } else if (method_desc.bytes[k] == ')') {
                        j = k - 1;
                        break;
                    }
                }
                count ++;
                continue;
            }
        }
        break;
    }
    return count;
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
    printf("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class_name_info.bytes, name_and_type_info.name_index, method_name_info.bytes, name_and_type_info.descriptor_index, method_desc_info.bytes);
    MethodInfo *method = find_method_with_desc(thread, heap, class, method_name_info.bytes, method_desc_info.bytes);
    if (NULL == method) exit(-1);
    if (is_native(method->access_flags)) {
        create_c_frame_and_invoke_add_params(thread, heap, frame, class->class_name, method);
    } else {
        create_vm_frame_by_method_add_params(thread, class, frame, method, get_method_code(class->constant_pool, *method));
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
    printf("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class_name, name_and_type_info.name_index, method_name, name_and_type_info.descriptor_index, method_desc);
    int params_count = parse_method_param_count(*(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info);
    Slot **slots = pop_slot_with_num(frame->operand_stack, params_count + 1);
    for (int i = 0; i < params_count + 1; i++) {
        push_slot(frame->operand_stack, slots[i]);
    }
    Object *object = slots[0]->object_value;
    class = object->class;
    MethodInfo *method = find_interface_method_iter_super_with_desc(thread, heap, &class, method_name, method_desc);
    if (NULL == method) exit(-1);
    if (is_native(method->access_flags)) {
        create_c_frame_and_invoke_add_params_plus1(thread, heap, frame, class->class_name, method);
    } else {
        create_vm_frame_by_method_add_params_plus1(thread, class, frame, method, get_method_code(class->constant_pool, *method));
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
    printf("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class_name_info.bytes, name_and_type_info.name_index, method_name_info.bytes, name_and_type_info.descriptor_index, method_desc_info.bytes);
    MethodInfo *method = find_method_iter_super_with_desc(thread, heap, &class, method_name_info.bytes, method_desc_info.bytes);
    if (NULL == method) exit(-1);
    if (is_native(method->access_flags)) {
        create_c_frame_and_invoke_add_params_plus1(thread, heap, frame, class->class_name, method);
    } else {
        create_vm_frame_by_method_add_params_plus1(thread, class, frame, method, get_method_code(class->constant_pool, *method));
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
    printf("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class->class_name, name_and_type_info.name_index, method_name_info.bytes, name_and_type_info.descriptor_index, method_desc_info.bytes);

    int params_count = parse_method_param_count(*(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info);
    Slot **slots = pop_slot_with_num(frame->operand_stack, params_count + 1);
    for (int i = 0; i < params_count + 1; i++) {
        push_slot(frame->operand_stack, slots[i]);
    }
    Object *object = slots[0]->object_value;
    class = object->class;
    MethodInfo *method = find_method_iter_super_with_desc(thread, heap, &class, method_name_info.bytes, method_desc_info.bytes);
    if (NULL == method) exit(-1);
    if (is_native(method->access_flags)) {
        create_c_frame_and_invoke_add_params_plus1(thread, heap, frame, class->class_name, method);
    } else {
        create_vm_frame_by_method_add_params_plus1(thread, class, frame, method, get_method_code(class->constant_pool, *method));
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
    printf("\t\t\t\t:%s.%s->%s\n", class_name_info.bytes, field_name_info.bytes, field_desc_info.bytes);
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
    printf("\t\t\t\t:%s.%s->%s\n", class_name_info.bytes, field_name_info.bytes, field_desc_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
//    FieldInfo *field = get_static_field_by_name_and_desc(class, field_name_info.bytes, field_desc_info.bytes);
    Slot *slot = get_static_field_slot_by_name_and_desc(class, field_name_info.bytes, field_desc_info.bytes);
    if (str_start_with(field_desc_info.bytes, "D") ||
        str_start_with(field_desc_info.bytes, "J")) {
        push_long(frame->operand_stack, slot->value);
//        push_long(frame->operand_stack, class->static_fields[field->offset].value);
    } else {
        push_slot(frame->operand_stack, slot);
//        push_slot(frame->operand_stack, &class->static_fields[field->offset]);
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
    FieldInfo *field = get_field_by_name_and_desc(object->raw_class, "value", "[B");
    Array *array = object->fields[field->offset].object_value;
    char *str = malloc(array->length + 1);
    memcpy(str, (char*)array->objects, array->length);
    str[array->length] = '\0';
    return str;
}

u8 get_field_value_by_name_and_desc(Object *object, char *name, char *desc)
{
    FieldInfo *field = get_field_by_name_and_desc(object->class, name, desc);
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
    u8 len = strlen(str);
    FieldInfo *field = get_field_by_name_and_desc(object->class, "value", "[B");
    Array *array = malloc_array_by_type_size(heap, load_class(thread, heap, "[B"), len, sizeof(char));
    char *_str = (char *) array->objects;
    for (int i = 0; i < len; i++) {
        _str[i] = str[i];
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
    printf("\t\t\t\t:%s.%s = %s\n", class_name_info.bytes, field_name_info.bytes, field_desc_info.bytes);
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
    printf("\t\t\t\t:%s.%s = %s\n", class_name_info.bytes, field_name_info.bytes, field_desc_info.bytes);
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
//    Slot *field;
//    if (str_start_with(field_desc_info.bytes, "D") ||
//        str_start_with(field_desc_info.bytes, "J")) {
//        field = create_slot_by_size(2);
//        field[1] = *pop_slot(frame->operand_stack);
//        field[0] = *pop_slot(frame->operand_stack);
//    } else {
//        field = pop_slot(frame->operand_stack);
//    }
//    put_field_to_map(&class->static_fields, field_name_info.bytes, field_desc_info.bytes, field);

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
//    Slot *slot = create_slot();
//    slot->value = 0;
//    slot->object_value = NULL;
//    push_slot(frame->operand_stack, slot);
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
//    u1 *class_name = get_utf8_bytes(frame->constant_pool, class_info.name_index);
//    int is_arr = class_name[0] == '[';
//    class_name = get_array_class_name_by_name_str(class_name);
    ClassFile *class = load_class_by_class_info_name_index(thread, heap, frame->constant_pool, class_info.name_index);
    if (class_is_not_init(class)) {
        back_pc(frame, back);
        init_class(thread, heap, class);
        return;
    }
//    if (is_arr) {
//        push_object(frame->operand_stack, malloc_array(heap, class, 0));
//    } else {
    push_object(frame->operand_stack, malloc_object(heap, class));
//    }
}

void create_object_with_class_name_and_backpc(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, int back)
{
//    int is_arr = class_name[0] == '[';
//    class_name = get_array_class_name_by_name_str(class_name);
    ClassFile *class = load_class(thread, heap, class_name);
    if (class_is_not_init(class)) {
        back_pc(frame, back);
        init_class(thread, heap, class);
        return;
    }
//    if (is_arr) {
//        push_object(frame->operand_stack, malloc_array(heap, class, 0));
//    } else {
    push_object(frame->operand_stack, malloc_object(heap, class));
//    }
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
//    int size = count * type_size;
//    ClassFile *class = load_class(thread, heap, desc);
//    Object *object = malloc_object(heap, class);
//    void *value = malloc(size);
//    memset(value, 0, size);
//    object->fields[0].object_value = value;
//    push_object(frame->operand_stack, object);

    ClassFile *class = load_class(thread, heap, desc);
    Array *array = malloc_array_by_type_size(heap, class, count, type_size);
    push_object(frame->operand_stack, array);
}

void create_string_object(Thread *thread, SerialHeap *heap, Frame *frame, char *str)
{
    ClassFile *class = load_class(thread, heap, "java/lang/String");
    if (class_is_not_init(class)) {
        back_pc(frame, 2);
        init_class(thread, heap, class);
        return;
    }
    Object *object = malloc_object(heap, class);
    put_str_field(thread, heap, object, str);
    push_object(frame->operand_stack, object);
}

void create_string_object_without_back(Thread *thread, SerialHeap *heap, Frame *frame, char *str)
{
    ClassFile *class = load_class(thread, heap, "java/lang/String");
    Object *object = malloc_object(heap, class);
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
    Array *arr = malloc_array(heap, load_primitive_class(thread, heap, _arr_name), count);
    push_object(frame->operand_stack, arr);

    if (NULL != class->class_object) {
        put_field_by_name_and_desc(arr->class->class_object, "componentType", "Ljava/lang/Class;", create_object_slot_set_object(heap, class->class_object));
    }

    free(_arr_name);
}

ClassFile *load_class_by_class_info_name_index(Thread *thread, SerialHeap *heap, ConstantPool *constant_pool, u2 index)
{
//    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)constant_pool[index].info;
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
    return class->init_state == CLASS_NOT_INIT;
}

int class_is_in_init(ClassFile *class)
{
    return class->init_state == CLASS_IN_INIT;
}

int class_is_inited(ClassFile *class)
{
    return class->init_state == CLASS_INITED;
}

void set_class_inited_by_frame(Thread *thread, SerialHeap *heap, Frame *frame, Frame *next_frame)
{
    frame->class->init_state = CLASS_INITED;
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
//                        put_long_field_to_map(&class->static_fields, class->fields[i].name, class->fields[i].desc, info.low_bytes, info.high_bytes);
                        class->static_fields[class->fields[i].offset].value = (long)(info.high_bytes & 0xffff0000) | (long)(info.low_bytes & 0x0000ffff);
                        break;
                    }
                    case 'L':{
//                        put_str_field_to_map(&class->static_fields, class->fields[i].name, class->fields[i].desc, get_str_from_string_index(class->constant_pool, value.constant_value_index));
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
    printf("\t\t\t\t-> jump <clinit> - %s\n", class->class_name);
    class->init_state = CLASS_IN_INIT;
    ClassFile *_class = load_class(thread, heap, "java/lang/Class");
    if (class_is_not_init(_class)) {
        init_class(thread, heap, _class);
    }
//    class->static_fields = malloc(sizeof(Field) * class->fields_count);
//    MethodInfo *init = find_method_with_desc(thread, heap, class, "<init>", "()V");
//    CodeAttribute *init_code = get_method_code(*init);
//    create_vm_frame_by_method_add_hook(thread, class, init, init_code, (PopHook) set_class_inited_by_frame);

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
        CodeAttribute *clinit_code = get_method_code(class->constant_pool, *clinit);
//        create_vm_frame_by_method(thread, class, clinit, clinit_code);
        create_vm_frame_by_method_add_hook(thread, class, clinit, clinit_code, (PopHook) set_class_inited_by_frame);
    } else {
        class->init_state = CLASS_INITED;
    }
}

void clinit_class_and_exec(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    printf("[clinit] - %s\n", class->class_name);
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

CodeAttribute *get_method_code(ConstantPool *pool, MethodInfo method) {
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
    for (int j = 0; j < this->interfaces_count; j++) {
        ClassFile *source = this->interfaces_info[j].class;
        if (source == interface) {
            return 1;
        }
        if (source->interfaces_count > 0) return is_impl_interface(source, interface);
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

Slot *create_object_slot(SerialHeap *heap, ClassFile *class)
{
    Slot *slot = create_slot();
    slot->object_value = malloc_object(heap, class);
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
    Object *object = malloc_object(heap, class);
    put_str_field(thread, heap, object, str);
    return create_object_slot_set_object(heap, object);
}