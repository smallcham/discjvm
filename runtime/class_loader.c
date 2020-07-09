#include "class_loader.h"


u1* get_class_bytes(char *path);

ClassFile load_class(SerialHeap *heap, char *full_class_name) {
    ClassFile *class_from_cache = get_class_from_cache(heap->class_pool, full_class_name);
    if (NULL != class_from_cache) return *class_from_cache;

    ClassFile class = *(ClassFile*)malloc(sizeof(ClassFile));
    u1 *class_file = get_class_bytes(full_class_name);
    class.magic = l2b_4(*(u4 *) class_file);
    class_file += sizeof(u4);
    class.minor_version = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.major_version = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.constant_pool_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);

    class.constant_pool = (ConstantPool *) malloc(class.constant_pool_count * sizeof(ConstantPool));

    for (u2 i = 1; i < class.constant_pool_count; i++) {
        class.constant_pool[i].tag = *(u1 *) class_file;
        switch (class.constant_pool[i].tag) {
            case CONSTANT_Class: {
                CONSTANT_Class_info *constant_class_info = (CONSTANT_Class_info *) malloc(sizeof(CONSTANT_Class_info));
                constant_class_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_class_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_class_info;
                continue;
            }
            case CONSTANT_Fieldref: {
                CONSTANT_Fieldref_info *constant_fieldref_info = (CONSTANT_Fieldref_info *) malloc(
                        sizeof(CONSTANT_Fieldref_info));
                constant_fieldref_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_fieldref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_fieldref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_fieldref_info;
                continue;
            }
            case CONSTANT_Methodref: {
                CONSTANT_Methodref_info *constant_methodref_info = (CONSTANT_Methodref_info *) malloc(
                        sizeof(CONSTANT_Methodref_info));
                constant_methodref_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_methodref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_methodref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_methodref_info;
                continue;
            }
            case CONSTANT_InterfaceMethodref: {
                CONSTANT_InterfaceMethodref_info *constant_interfacemethodref_info = (CONSTANT_InterfaceMethodref_info *) malloc(
                        sizeof(CONSTANT_InterfaceMethodref_info));
                constant_interfacemethodref_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_interfacemethodref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_interfacemethodref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_interfacemethodref_info;
                continue;
            }
            case CONSTANT_String: {
                CONSTANT_String_info *constant_string_info = (CONSTANT_String_info *) malloc(
                        sizeof(CONSTANT_String_info));
                constant_string_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_string_info->string_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_string_info;
                continue;
            }
            case CONSTANT_Integer: {
                CONSTANT_Integer_info *constant_integer_info = (CONSTANT_Integer_info *) malloc(
                        sizeof(CONSTANT_Integer_info));
                constant_integer_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_integer_info->bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                class.constant_pool[i].info = constant_integer_info;
                continue;
            }
            case CONSTANT_Float: {
                CONSTANT_Float_info *constant_float_info = (CONSTANT_Float_info *) malloc(sizeof(CONSTANT_Float_info));
                constant_float_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_float_info->bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                class.constant_pool[i].info = constant_float_info;
                continue;
            }
            case CONSTANT_Long: {
                CONSTANT_Long_info *constant_long_info = (CONSTANT_Long_info *) malloc(sizeof(CONSTANT_Long_info));
                constant_long_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_long_info->high_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_long_info->low_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                class.constant_pool[i].info = constant_long_info;
                continue;
            }
            case CONSTANT_Double: {
                CONSTANT_Double_info *constant_double_info = (CONSTANT_Double_info *) malloc(
                        sizeof(CONSTANT_Double_info));
                constant_double_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_double_info->high_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_double_info->low_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                class.constant_pool[i].info = constant_double_info;
                continue;
            }
            case CONSTANT_NameAndType: {
                CONSTANT_NameAndType_info *constant_nameandtype_info = (CONSTANT_NameAndType_info *) malloc(
                        sizeof(CONSTANT_NameAndType_info));
                constant_nameandtype_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_nameandtype_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_nameandtype_info->descriptor_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_nameandtype_info;
                continue;
            }
            case CONSTANT_Utf8: {
                CONSTANT_Utf8_info *constant_utf8_info = (CONSTANT_Utf8_info *) malloc(sizeof(CONSTANT_Utf8_info));
                constant_utf8_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_utf8_info->length = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_utf8_info->bytes = malloc(constant_utf8_info->length + 1);
                memcpy(constant_utf8_info->bytes, class_file, constant_utf8_info->length);
                constant_utf8_info->bytes[constant_utf8_info->length] = '\0';
                class_file += constant_utf8_info->length;
                class.constant_pool[i].info = constant_utf8_info;
                continue;
            }
            case CONSTANT_MethodHandle: {
                CONSTANT_MethodHandle_info *constant_methodhandle_info = (CONSTANT_MethodHandle_info *) malloc(
                        sizeof(CONSTANT_MethodHandle_info));
                constant_methodhandle_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_methodhandle_info->reference_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_methodhandle_info->reference_kind = *(u1 *) class_file;
                class_file += sizeof(u1);
                class.constant_pool[i].info = constant_methodhandle_info;
                continue;
            }
            case CONSTANT_MethodType: {
                CONSTANT_MethodType_info *constant_methodtype_info = (CONSTANT_MethodType_info *) malloc(
                        sizeof(CONSTANT_MethodType_info));
                constant_methodtype_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_methodtype_info->descriptor_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_methodtype_info;
                continue;
            }
            case CONSTANT_InvokeDynamic: {
                CONSTANT_InvokeDynamic_info *constant_invokedynamic_info = (CONSTANT_InvokeDynamic_info *) malloc(
                        sizeof(CONSTANT_InvokeDynamic_info));
                constant_invokedynamic_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_invokedynamic_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_invokedynamic_info->bootstrap_method_attr_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_invokedynamic_info;
                continue;
            }
            case CONSTANT_Module: {
                CONSTANT_Module_info *constant_module_info = (CONSTANT_Module_info *) malloc(
                        sizeof(CONSTANT_Module_info));
                constant_module_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_module_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_module_info;
                continue;
            }
            case CONSTANT_Package: {
                CONSTANT_Package_info *constant_package_info = (CONSTANT_Package_info *) malloc(
                        sizeof(CONSTANT_Package_info));
                constant_package_info->tag = class.constant_pool[i].tag;
                class_file += sizeof(u1);
                constant_package_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                class.constant_pool[i].info = constant_package_info;
                continue;
            }
        }
    }
    class.access_flags = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.this_class = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.super_class = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.interfaces_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class.interfaces_count > 0) {
        u2 len = class.interfaces_count * sizeof(u2);
        class.interfaces = (u2 *) malloc(len);
        memcpy(class.interfaces, class_file, len);
        class_file += len;
    }
    class.fields_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class.fields_count > 0) {
        class.fields = (FieldInfo *) malloc(class.fields_count * sizeof(FieldInfo));
        for (int i = 0; i < class.fields_count; i++) {
            class.fields[i].access_flags = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class.fields[i].name_index = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class.fields[i].descriptor_index = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class.fields[i].attributes_count = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            if (class.fields[i].attributes_count > 0) {
                class.fields[i].attributes = (AttributeInfo *) malloc(
                        class.fields[i].attributes_count * sizeof(AttributeInfo));
                for (int j = 0; j < class.fields[i].attributes_count; j++) {
                    class.fields[i].attributes[j].attribute_name_index = l2b_2(*(u2 *) class_file);
                    class_file += sizeof(u2);
                    class.fields[i].attributes[j].attribute_length = l2b_4(*(u4 *) class_file);
                    class_file += sizeof(u4);
                    if (class.fields[i].attributes[j].attribute_length > 0) {
                        class.fields[i].attributes[j].info = malloc(
                                sizeof(u1) * class.fields[i].attributes[j].attribute_length);
                        memcpy(class.fields[i].attributes[j].info, class_file, class.fields[i].attributes[j].attribute_length);
                        class_file += class.fields[i].attributes[j].attribute_length;
                    }
                }
            }
        }
    }
    class.methods_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class.methods_count > 0) {
        class.methods = malloc(class.methods_count * sizeof(MethodInfo));
        for (int i = 0; i < class.methods_count; i++) {
            class.methods[i].access_flags = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class.methods[i].name_index = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class.methods[i].descriptor_index = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class.methods[i].attributes_count = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            if (class.methods[i].attributes_count > 0) {
                class.methods[i].attributes = (AttributeInfo *) malloc(
                        class.methods[i].attributes_count * sizeof(AttributeInfo));
                for (int j = 0; j < class.methods[i].attributes_count; j++) {
                    class.methods[i].attributes[j].attribute_name_index = l2b_2(*(u2 *) class_file);
                    class_file += sizeof(u2);
                    class.methods[i].attributes[j].attribute_length = l2b_4(*(u4 *) class_file);
                    class_file += sizeof(u4);
                    if (class.methods[i].attributes[j].attribute_length > 0) {
                        class.methods[i].attributes[j].info = malloc(sizeof(u1) * class.methods[i].attributes[j].attribute_length);
                        memcpy(class.methods[i].attributes[j].info, class_file, class.methods[i].attributes[j].attribute_length);
                        class_file += class.methods[i].attributes[j].attribute_length;
                    }
                }
            }
        }
    }
    class.attributes_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if (class.attributes_count > 0) {
        class.attributes = (AttributeInfo *) malloc(class.attributes_count * sizeof(AttributeInfo));
        for (int j = 0; j < class.attributes_count; j++) {
            class.attributes[j].attribute_name_index = l2b_2(*(u2 *) class_file);
            class_file += sizeof(u2);
            class.attributes[j].attribute_length = l2b_4(*(u4 *) class_file);
            class_file += sizeof(u4);
            if (class.attributes[j].attribute_length > 0) {
                class.attributes[j].info = malloc(sizeof(u1) * class.attributes[j].attribute_length);
                memcpy(class.attributes[j].info, class_file, class.attributes[j].attribute_length);
                class_file += class.attributes[j].attribute_length;
            }
        }
    }
    put_class_to_cache(heap->class_pool, &class);
    link_class(heap, &class);
    return class;
}

u1* get_class_bytes(char *path)
{
    if (str_start_with(path, "java/lang/") == 1) {
        return load_from_jmod("java.base.jmod", path);
    } else {
        FILE *fp = fopen(path, "rb");
        fseek(fp, 0, SEEK_END);
        long f_size = ftell(fp);
        u1 *class_file = (u1 *) malloc(f_size * sizeof(u1));
        rewind(fp);
        fread(class_file, f_size, 1, fp);
        fclose(fp);
        return class_file;
    }
}

CodeAttribute get_method_code(MethodInfo method) {
    AttributeInfo code_info = method.attributes[0];
    CodeAttribute code_attribute = *(CodeAttribute*) malloc(sizeof(CodeAttribute));
    code_attribute.attribute_name_index = code_info.attribute_name_index;
    code_attribute.attribute_length = code_info.attribute_length;
    u1 *bytes = code_info.info;
    code_attribute.max_stack = l2b_2(*(u2*) bytes);
    bytes += sizeof(u2);
    code_attribute.max_locals = l2b_2(*(u2*) bytes);
    bytes += sizeof(u2);
    code_attribute.code_length = l2b_4(*(u4*) bytes);
    bytes += sizeof(u4);
    if (code_attribute.code_length > 0) {
        code_attribute.code = malloc(code_attribute.code_length);
        memcpy(code_attribute.code, bytes, code_attribute.code_length);
        bytes += code_attribute.code_length;
    }
    code_attribute.exception_table_length = l2b_2(*(u2*) bytes);
    bytes += sizeof(u2);
    if (code_attribute.exception_table_length > 0) {
        u8 exception_table_len = code_attribute.exception_table_length * sizeof(u8);
        code_attribute.exception_table = malloc(exception_table_len);
        memcpy(code_attribute.exception_table, bytes, exception_table_len);
        bytes += exception_table_len;
    }
    code_attribute.attributes_count = l2b_2(*(u2*) bytes);
    bytes += sizeof(u2);
    if (code_attribute.attributes_count > 0) {
        code_attribute.attributes = malloc(sizeof(AttributeInfo) * code_attribute.attributes_count);
        code_attribute.attributes->attribute_name_index = l2b_2(*(u2*) bytes);
        bytes += sizeof(u2);
        code_attribute.attributes->attribute_length = l2b_4(*(u4*) bytes);
        bytes += sizeof(u4);
        code_attribute.attributes->info = malloc(code_attribute.attributes->attribute_length);
        memcpy(code_attribute.attributes->info, bytes, code_attribute.attributes->attribute_length);
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
                CodeAttribute code = get_method_code(class.methods[i]);
                printf("\t\t\t[%d] MaxStack: %d | CodeLength: %d\n", j, code.max_stack, code.code_length);
                for (int k = 0; k < code.code_length; k++) {
                    printf("\t\t\t%#X\n", code.code[k]);
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

MethodInfo *find_method(ClassFile class, char *name) {
    for (int i = 0; i < class.methods_count; i++)
    {
        CONSTANT_Utf8_info method_info = *(CONSTANT_Utf8_info*)class.constant_pool[class.methods[i].name_index].info;
        char method_name[method_info.length + 1];
        memcpy(method_name, method_info.bytes, method_info.length);
        method_name[method_info.length] = '\0';
        if (strcmp(method_name, name) == 0) return &class.methods[i];
    }
    return NULL;
}

void link_class(SerialHeap *heap, ClassFile *class)
{
    invoke_method(heap, class, *find_method(*class, "<clinit>"));
    invoke_method(heap, class, *find_method(*class, "<init>"));
}