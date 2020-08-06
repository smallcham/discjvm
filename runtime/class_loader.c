#include "class_loader.h"

u1* get_class_bytes(char *path);

ClassFile *load_class_by_bytes(Thread *thread, SerialHeap *heap, u1 *bytes)
{
    ClassFile *class = (ClassFile*)malloc(sizeof(ClassFile));
    class->init_state = CLASS_NOT_INIT;
    u1 *class_file = bytes;
    class->magic = l2b_4(*(u4 *) class_file);
    class_file += sizeof(u4);
    class->minor_version = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class->major_version = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class->constant_pool_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);

    class->constant_pool = (ConstantPool *) malloc(class->constant_pool_count * sizeof(ConstantPool));

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
    class->super_class = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class->interfaces_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class->interfaces_count > 0) {
        u2 len = class->interfaces_count * sizeof(u2);
        class->interfaces = (u2 *) malloc(len);
        memcpy(class->interfaces, class_file, len);
        class_file += len;
    }
    class->fields_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class->fields_count > 0) {
        class->fields = (FieldInfo *) malloc(class->fields_count * sizeof(FieldInfo));
        class->static_fields = create_map_by_size((int)((class->fields_count + 2) * 1.3));
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
//            Field *field = malloc(sizeof(Field));
//            field->field_info = &class->fields[i];
//            field->slot = NULL;
//            put_runtime_field_to_map(&class->static_fields, class->class_name, class->fields[i].name, class->fields[i].desc, field);
//            class->static_fields[i].field_info = &class->fields[i];
//            class->static_fields[i].slot = NULL;
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

ClassFile *load_class(Thread *thread, SerialHeap *heap, char *full_class_name)
{
    ClassFile *class_from_cache = get_class_from_cache(heap->class_pool, full_class_name);
    if (NULL != class_from_cache) {
        return class_from_cache;
    }

    ClassFile *class = (ClassFile*)malloc(sizeof(ClassFile));
    class->init_state = CLASS_NOT_INIT;
    u1 *class_file = get_class_bytes(full_class_name);
    return load_class_by_bytes(thread, heap, class_file);
}

//Field *get_runtime_field_from_map(HashMap **map, u1 *class_name, u1 *name, u1 *desc)
//{
//    char *key = malloc(strlen(class_name) + strlen(name) + strlen(desc) + 4);
//    sprintf(key, "%s.%s.%s", class_name, name, desc);
//    Field *field = get_map(map, key);
//    free(key);
//    return field;
//}

Slot *get_field_from_map(HashMap **map, u1 *class_name, u1 *name, u1 *desc)
{
    char *key = malloc(strlen(class_name) + strlen(name) + strlen(desc) + 4);
    sprintf(key, "%s.%s.%s", class_name, name, desc);
    Slot *field = get_map(map, key);
    free(key);
    return field;
}

//void put_runtime_field_to_map(HashMap **map, u1 *class_name, u1 *name, u1 *desc, Field *field)
//{
//    char *key = malloc(strlen(class_name) + strlen(name) + strlen(desc) + 4);
//    sprintf(key, "%s.%s.%s", class_name, name, desc);
//    put_map(map, key, field);
//}

void put_field_to_map(HashMap **map, u1 *class_name, u1 *name, u1 *desc, Slot *value)
{
    char *key = malloc(strlen(class_name) + strlen(name) + strlen(desc) + 4);
    sprintf(key, "%s.%s.%s", class_name, name, desc);
    put_map(map, key, value);
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
            case 'L': case '[': {
                for (int k = j + 1; k < method_desc.length; k++) {
                    if (method_desc.bytes[k] == ';') j = k;
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
    if ((method->access_flags & ACC_NATIVE) != 0) {
        create_c_frame_and_invoke(thread, frame, class->class_name, method->name, method->desc);
    } else {
        create_vm_frame_by_method_add_params(thread, class, frame, method, get_method_code(class->constant_pool, *method));
    }
}

void do_invokeinterface_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index, u1 count)
{
    CONSTANT_InterfaceMethodref_info interface_ref_info = *(CONSTANT_InterfaceMethodref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[interface_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[interface_ref_info.name_and_type_index].info;
//    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
//    CONSTANT_Utf8_info method_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
//    CONSTANT_Utf8_info method_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    u1 *class_name = get_utf8_bytes(frame->constant_pool, class_info.name_index);
    u1 *method_name = get_utf8_bytes(frame->constant_pool, name_and_type_info.name_index);
    u1 *method_desc = get_utf8_bytes(frame->constant_pool, name_and_type_info.descriptor_index);
    ClassFile *class = load_class(thread, heap, class_name);
//    Slot **slots = pop_slot_with_num(frame->operand_stack, count);
//    Object *object = pop_stack(frame->operand_stack);
//    for (int i = 0; i < count; i++) {
//    }
    printf("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class_name, name_and_type_info.name_index, method_name, name_and_type_info.descriptor_index, method_desc);
    MethodInfo *method = find_method_iter_super_with_desc(thread, heap, &class, method_name, method_name);
    if (NULL == method) exit(-1);
    if ((method->access_flags & ACC_NATIVE) != 0) {
        create_c_frame_and_invoke(thread, frame, class->class_name, method->name, method->desc);
    } else {
        create_vm_frame_by_method_add_params_and_this(thread, class, frame, method, get_method_code(class->constant_pool, *method));
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
    if ((method->access_flags & ACC_NATIVE) != 0) {
        create_c_frame_and_invoke(thread, frame, class->class_name, method->name, method->desc);
    } else {
        create_vm_frame_by_method_add_params_and_this(thread, class, frame, method, get_method_code(class->constant_pool, *method));
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
    printf("\n\t\t\t\t\t -> %s.#%d %s #%d%s\n\n", class_name_info.bytes, name_and_type_info.name_index, method_name_info.bytes, name_and_type_info.descriptor_index, method_desc_info.bytes);
    MethodInfo *method = find_method_iter_super_with_desc(thread, heap, &class, method_name_info.bytes, method_desc_info.bytes);
    if (NULL == method) exit(-1);
    if ((method->access_flags & ACC_NATIVE) != 0) {
        create_c_frame_and_invoke(thread, frame, class->class_name, method->name, method->desc);
    } else {
        create_vm_frame_by_method_add_params_and_this(thread, class, frame, method, get_method_code(class->constant_pool, *method));
    }
}

void get_field_to_opstack_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    CONSTANT_Fieldref_info field_ref_info = *(CONSTANT_Fieldref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    CONSTANT_Utf8_info field_type_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
    Object *object = pop_object(frame->operand_stack);
    Slot *field = get_field_from_map(&object->fields, class->class_name, field_type_info.bytes, field_desc_info.bytes);

    push_slot(frame->operand_stack, field);
}

void get_static_field_to_opstack_by_index(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    CONSTANT_Fieldref_info field_ref_info = *(CONSTANT_Fieldref_info*)frame->constant_pool[index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    CONSTANT_Utf8_info field_type_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }

    Slot *field = get_field_from_map(&class->static_fields, class->class_name, field_type_info.bytes, field_desc_info.bytes);
    push_slot(frame->operand_stack, field);
//    for (int i = 0; i < class->fields_count; i++) {
//        if (NULL == class->static_fields[i].slot) continue;
//        if (class->static_fields[i].field_info->name_index == name_and_type_info.name_index &&
//                class->static_fields[i].field_info->descriptor_index == name_and_type_info.descriptor_index) {
//            push_slot(frame->operand_stack, class->static_fields[i].slot);
//            if (str_start_with(field_desc_info.bytes, "B") ||
//                str_start_with(field_desc_info.bytes, "C") ||
//                str_start_with(field_desc_info.bytes, "I") ||
//                str_start_with(field_desc_info.bytes, "S") ||
//                str_start_with(field_desc_info.bytes, "Z") ||
//                str_start_with(field_desc_info.bytes, "F")) {
//                //Int
//                push_slot(frame->operand_stack, class->static_fields[i].slot);
//            }
//            else if (str_start_with(field_desc_info.bytes, "D") ||
//                     str_start_with(field_desc_info.bytes, "J")) {
//                //Long
//                push_int(frame->operand_stack, class->static_fields[i].slot[0].value);
//                push_int(frame->operand_stack, class->static_fields[i].slot[1].value);
//            }
//            else if (str_start_with(field_desc_info.bytes, "L") ||
//                     str_start_with(field_desc_info.bytes, "[")) {
//                //Object | Array
//                push_stack(frame->operand_stack, class->static_fields[i].slot->object_value);
//            }
//            return;
//        }
//    }
}

void put_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info)
{
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info field_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
    Slot *field;
    if (str_start_with(field_desc_info.bytes, "D") ||
        str_start_with(field_desc_info.bytes, "J")) {
        field = malloc(sizeof(Slot) * 2);
        field[1] = *pop_slot(frame->operand_stack);
        field[0] = *pop_slot(frame->operand_stack);
    } else {
        field = pop_slot(frame->operand_stack);
    }
    Object *object = pop_object(frame->operand_stack);
    put_field_to_map(&object->fields, object->class->class_name, field_name_info.bytes, field_desc_info.bytes, field);
}

void put_static_field(Thread *thread, SerialHeap *heap, Frame *frame, CONSTANT_Fieldref_info field_ref_info)
{
    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
    CONSTANT_Utf8_info field_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
    ClassFile *class = load_class(thread, heap, class_name_info.bytes);
    if (class_is_not_init(class)) {
        back_pc(frame, 3);
        init_class(thread, heap, class);
        return;
    }
//    int index = -1;
//    for (int i = 0; i < class->fields_count; i++) {
//        if (class->fields[i].name_index == name_and_type_info.name_index) {
//            index = i;
//            break;
//        }
//    }
//    if (index == -1) exit(-1);
//    class->static_fields[index].field_info = &class->fields[index];
    Slot *field = get_field_from_map(&class->static_fields, class->class_name, field_name_info.bytes, field_desc_info.bytes);
    free(field);
    if (str_start_with(field_desc_info.bytes, "D") ||
        str_start_with(field_desc_info.bytes, "J")) {
        field = malloc(sizeof(Slot) * 2);
        field[1] = *pop_slot(frame->operand_stack);
        field[0] = *pop_slot(frame->operand_stack);
    } else {
        field = pop_slot(frame->operand_stack);
    }
    put_field_to_map(&class->static_fields, class->class_name, field_name_info.bytes, field_desc_info.bytes, field);
//    class->static_fields[index].slot = pop_slot(frame->operand_stack);

//    if (str_start_with(field_desc_info.bytes, "B") ||
//    str_start_with(field_desc_info.bytes, "C") ||
//    str_start_with(field_desc_info.bytes, "I") ||
//    str_start_with(field_desc_info.bytes, "S") ||
//    str_start_with(field_desc_info.bytes, "Z")) {
//        //Int
//        int value = pop_int(frame->operand_stack);
//        class->static_fields[index].slot = malloc(sizeof(Slot));
//        class->static_fields[index].slot->value = value;
//    }
//    else if (str_start_with(field_desc_info.bytes, "F")) {
//        //Float
//        float value = pop_float(frame->operand_stack);
//        class->static_fields[index].slot = malloc(sizeof(Slot));
//        class->static_fields[index].slot->value = value;
//    }
//    else if (str_start_with(field_desc_info.bytes, "D") ||
//            str_start_with(field_desc_info.bytes, "J")) {
//        //Long
//        int higher = pop_int(frame->operand_stack);
//        int lower = pop_int(frame->operand_stack);
//        class->static_fields[index].slot = malloc(sizeof(Slot) * 2);
//        class->static_fields[index].slot[0].value = lower;
//        class->static_fields[index].slot[1].value = higher;
//    }
//    else if (str_start_with(field_desc_info.bytes, "L") ||
//            str_start_with(field_desc_info.bytes, "[")) {
//        //Object | Array
//        class->static_fields[index].slot = malloc(sizeof(Slot));
//        class->static_fields[index].slot->object_value = pop_stack(frame->operand_stack);
//    }
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
    push_object(frame->operand_stack, malloc_null_object(heap));
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

void create_object_with_backpc(Thread *thread, SerialHeap *heap, Frame *frame, u2 index, int back)
{
    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[index].info;
    u1 *class_name = get_utf8_bytes(frame->constant_pool, class_info.name_index);
    int is_arr = class_name[0] == '[';
    class_name = get_array_class_name_by_name_str(class_name);
    ClassFile *class = load_class(thread, heap, class_name);
    if (class_is_not_init(class)) {
        back_pc(frame, back);
        init_class(thread, heap, class);
        return;
    }
    if (is_arr) {
        push_object(frame->operand_stack, malloc_array(heap, class, 0));
    } else {
        push_object(frame->operand_stack, malloc_object(heap, class));
    }
}

void create_object_with_class_name_and_backpc(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, int back)
{
    int is_arr = class_name[0] == '[';
    class_name = get_array_class_name_by_name_str(class_name);
    ClassFile *class = load_class(thread, heap, class_name);
    if (class_is_not_init(class)) {
        back_pc(frame, back);
        init_class(thread, heap, class);
        return;
    }
    if (is_arr) {
        push_object(frame->operand_stack, malloc_array(heap, class, 0));
    } else {
        push_object(frame->operand_stack, malloc_object(heap, class));
    }
}

void create_object(Thread *thread, SerialHeap *heap, Frame *frame, u2 index)
{
    create_object_with_backpc(thread, heap, frame, index, 3);
}

void create_array_reference_by_type(Thread *thread, SerialHeap *heap, Frame *frame, u1 type, int count)
{
    ClassFile *class;
    int size = 1;
    switch (type) {
        case 4:
            class = load_class(thread, heap, "java/lang/Boolean");
            break;
        case 5:
            class = load_class(thread, heap, "java/lang/Character");
            break;
        case 6:
            class = load_class(thread, heap, "java/lang/Float");
            break;
        case 7:
            class = load_class(thread, heap, "java/lang/Double");
            size = 2;
            break;
        case 8:
            class = load_class(thread, heap, "java/lang/Byte");
            break;
        case 9:
            class = load_class(thread, heap, "java/lang/Short");
            break;
        case 10:
            class = load_class(thread, heap, "java/lang/Integer");
            break;
        case 11:
            class = load_class(thread, heap, "java/lang/Long");
            size = 2;
            break;
    }
    if (class_is_not_init(class)) {
        back_pc(frame, 2);
        init_class(thread, heap, class);
        return;
    }
//    Object *object = (Object*)malloc(sizeof(Object) + sizeof(Slot) * count);
//    object->class = class;
//    object->length = count;
    Array *array = malloc_array(heap, class, count);
//    for (int i = 0; i < count; i++) {
//        Slot *slot = create_slot_by_size(size);
//        Field *field = malloc(sizeof(Field));
//        for (int j = 0; j < class->fields_count; j++) {
//            if (strcmp(class->fields[j].name, "value") == 0) {
//                field->field_info = &class->fields[j];
//                break;
//            }
//        }
//        field->slot = slot;
//        u1 *desc = malloc(strlen(class->class_name) + 3);
//        sprintf(desc, "[L%s;", class->class_name);
//        put_field_to_map(&class->static_fields, class->class_name, "value", desc, );
//        free(desc);
//    }
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
//    Object *object = (Object*)malloc(sizeof(Object) + sizeof(Slot));
//    object->class = class;
//    object->length = 1;
//    object->slots[0] = NULL;

    Slot *slot = create_slot();
    slot->object_value = str;
//    Field *field = malloc(sizeof(Field));
//    for (int i = 0; i < class->fields_count; i++) {
//        if (strcmp(class->fields[i].name, "value") == 0) {
//            field->field_info = &class->fields[i];
//            break;
//        }
//    }
//    field->slot = slot;
    put_field_to_map(&object->fields, class->class_name, "value", "Ljava/lang/String;", slot);
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
    push_object(frame->operand_stack, malloc_array(heap, class, count));
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
    if (class->super_class == 0) return NULL;
    return load_class_by_class_info(thread, heap, class->constant_pool, *(CONSTANT_Class_info*)class->constant_pool[class->super_class].info);
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

void set_class_inited_by_frame(Thread *thread, SerialHeap *heap, Frame *frame)
{
    frame->class->class_object = malloc_object(heap, load_class(thread, heap, "java/lang/Class"));
    frame->class->init_state = CLASS_INITED;
}

void init_class(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    if (class_is_inited(class)) return;
    printf("\t\t\t\t-> jump init - %s\n", class->class_name);
    class->init_state = CLASS_IN_INIT;
//    class->static_fields = malloc(sizeof(Field) * class->fields_count);
//    MethodInfo *init = find_method_with_desc(thread, heap, class, "<init>", "()V");
//    CodeAttribute *init_code = get_method_code(*init);
//    create_vm_frame_by_method_add_hook(thread, class, init, init_code, (PopHook) set_class_inited_by_frame);

    MethodInfo *clinit = find_method_with_desc(thread, heap, class, "<clinit>", "()V");
    if (NULL != clinit) {
        CodeAttribute *clinit_code = get_method_code(class->constant_pool, *clinit);
//        create_vm_frame_by_method(thread, class, clinit, clinit_code);
        create_vm_frame_by_method_add_hook(thread, class, clinit, clinit_code, (PopHook) set_class_inited_by_frame);
    } else {
        class->class_object = malloc_object(heap, load_class(thread, heap, "java/lang/Class"));
        class->init_state = CLASS_INITED;
    }

    ClassFile *super = get_super_class(thread, heap, class);
    if (NULL != super && class_is_not_init(super)) {
        init_class(thread, heap, super);
    }
}

void init_class_and_exec(Thread *thread, SerialHeap *heap, ClassFile *class)
{
    printf("[init_lib] - %s\n", class->class_name);
    init_class(thread, heap, class);
    run(thread, heap);
}

u1* get_class_bytes(char *path)
{
//    if (str_start_with(path, "java/lang/") == 1 ||
//            str_start_with(path, "java/io/") == 1 ||
//            str_start_with(path, "java/util/") == 1 ||
//            str_start_with(path, "java/security/") == 1 ||
//            str_start_with(path, "java/nio/") == 1) {
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

    CONSTANT_Class_info constant_super_class_info = *(CONSTANT_Class_info*)class.constant_pool[class.super_class].info;
    CONSTANT_Utf8_info super_class = *(CONSTANT_Utf8_info*)class.constant_pool[constant_super_class_info.name_index].info;

    printf("\tMagicNumber: %X\n\tVersion: %d.%d (%d)\n\tConstantPoolCount: %d"
           "\n\tAccessFlags: %#x\n\tThisClass: #%d <%s>\n\tSuperClass: #%d <%s>"
           "\n\tInterfaceCount: %d\n\tFieldCount: %d\n\tMethodCount: %d\n\tAttributeCount: %d"
           "\n", class.magic, class.major_version, class.minor_version, class.major_version - 44,
           class.constant_pool_count,class.access_flags, class.this_class, this_class.bytes,
           class.super_class, super_class.bytes, class.interfaces_count, class.fields_count, class.methods_count, class.attributes_count);


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
    while (NULL != class)
    {
        MethodInfo *method = find_method_with_desc(thread, heap, *class, name, desc);
        if (NULL != method) return method;
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

MethodInfo *find_method(Thread *thread, SerialHeap *heap, ClassFile *class, char *name) {
    for (int i = 0; i < class->methods_count; i++)
    {
        CONSTANT_Utf8_info method_info = *(CONSTANT_Utf8_info*)class->constant_pool[class->methods[i].name_index].info;
        if (strcmp(method_info.bytes, name) == 0) return &class->methods[i];
    }
    return NULL;
}