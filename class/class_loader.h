#include <stdio.h>
#include <stdlib.h>
#include "../model/class.h"
#include "../util/endian.h"

int load_class(char *path) {
    FILE *fp = fopen(path, "rb");
    ClassFile class;

    fseek(fp, 0, SEEK_END);
    long f_size = ftell(fp);
    u1 *class_file = (u1 *) malloc(f_size * sizeof(u1));
    rewind(fp);
    fread(class_file, f_size, 1, fp);
    fclose(fp);
    class.magic = l2b_4(*(u4 *) class_file);
    class_file += sizeof(u4);
    class.major_version = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.minor_version = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.constant_pool_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);

    class.constant_pool = (ConstantPool*) malloc(class.constant_pool_count * sizeof(ConstantPool));

    for (u2 i = 1; i < class.constant_pool_count; i++) {
        ConstantPool *constant_pool = (ConstantPool *) malloc(sizeof(ConstantPool));
        constant_pool->tag = *(u1 *) class_file;
        printf("\nTAG: %d\n", constant_pool->tag);
        switch (constant_pool->tag) {
            case CONSTANT_Class:
                printf("CONSTANT_Class");
                CONSTANT_Class_info *constant_class_info = (CONSTANT_Class_info *) malloc(sizeof(CONSTANT_Class_info));
                constant_class_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_class_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_class_info;
                continue;
            case CONSTANT_Fieldref:
                printf("CONSTANT_Fieldref");
                CONSTANT_Fieldref_info *constant_fieldref_info = (CONSTANT_Fieldref_info *) malloc(
                        sizeof(CONSTANT_Fieldref_info));
                constant_fieldref_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_fieldref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_fieldref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_fieldref_info;
                continue;
            case CONSTANT_Methodref:
                printf("CONSTANT_Methodref");
                CONSTANT_Methodref_info *constant_methodref_info = (CONSTANT_Methodref_info *) malloc(
                        sizeof(CONSTANT_Methodref_info));
                constant_methodref_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_methodref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_methodref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_methodref_info;
                continue;
            case CONSTANT_InterfaceMethodref:
                printf("CONSTANT_InterfaceMethodref");
                CONSTANT_InterfaceMethodref_info *constant_interfacemethodref_info = (CONSTANT_InterfaceMethodref_info *) malloc(
                        sizeof(CONSTANT_InterfaceMethodref_info));
                constant_interfacemethodref_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_interfacemethodref_info->class_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_interfacemethodref_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_interfacemethodref_info;
                continue;
            case CONSTANT_String:
                printf("CONSTANT_String");
                CONSTANT_String_info *constant_string_info = (CONSTANT_String_info *) malloc(
                        sizeof(CONSTANT_String_info));
                constant_string_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_string_info->string_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_string_info;
                continue;
            case CONSTANT_Integer:
                printf("CONSTANT_Integer");
                CONSTANT_Integer_info *constant_integer_info = (CONSTANT_Integer_info *) malloc(
                        sizeof(CONSTANT_Integer_info));
                constant_integer_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_integer_info->bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_pool->info = constant_integer_info;
                continue;
            case CONSTANT_Float:
                printf("CONSTANT_Float");
                CONSTANT_Float_info *constant_float_info = (CONSTANT_Float_info *) malloc(sizeof(CONSTANT_Float_info));
                constant_float_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_float_info->bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_pool->info = constant_float_info;
                continue;
            case CONSTANT_Long:
                printf("CONSTANT_Long");
                CONSTANT_Long_info *constant_long_info = (CONSTANT_Long_info *) malloc(sizeof(CONSTANT_Long_info));
                constant_long_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_long_info->high_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_long_info->low_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_pool->info = constant_long_info;
                continue;
            case CONSTANT_Double:
                printf("CONSTANT_Double");
                CONSTANT_Double_info *constant_double_info = (CONSTANT_Double_info *) malloc(
                        sizeof(CONSTANT_Double_info));
                constant_double_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_double_info->high_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_double_info->low_bytes = l2b_4(*(u4 *) class_file);
                class_file += sizeof(u4);
                constant_pool->info = constant_double_info;
                continue;
            case CONSTANT_NameAndType:
                printf("CONSTANT_NameAndType");
                CONSTANT_NameAndType_info *constant_nameandtype_info = (CONSTANT_NameAndType_info *) malloc(
                        sizeof(CONSTANT_NameAndType_info));
                constant_nameandtype_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_nameandtype_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_nameandtype_info->descriptor_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_nameandtype_info;
                continue;
            case CONSTANT_Utf8:
                printf("CONSTANT_Utf8");
                CONSTANT_Utf8_info *constant_utf8_info = (CONSTANT_Utf8_info *) malloc(sizeof(CONSTANT_Utf8_info));
                constant_utf8_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_utf8_info->length = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                u4 len = sizeof(u1) * constant_utf8_info->length;
                constant_utf8_info->bytes = (u1 *) malloc(len);
                class_file += len;
                constant_pool->info = constant_utf8_info;
                continue;
            case CONSTANT_MethodHandle:
                printf("CONSTANT_MethodHandle");
                CONSTANT_MethodHandle_info *constant_methodhandle_info = (CONSTANT_MethodHandle_info *) malloc(
                        sizeof(CONSTANT_MethodHandle_info));
                constant_methodhandle_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_methodhandle_info->reference_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_methodhandle_info->reference_kind = *(u1 *) class_file;
                class_file += sizeof(u1);
                constant_pool->info = constant_methodhandle_info;
                continue;
            case CONSTANT_MethodType:
                printf("CONSTANT_MethodType");
                CONSTANT_MethodType_info *constant_methodtype_info = (CONSTANT_MethodType_info *) malloc(
                        sizeof(CONSTANT_MethodType_info));
                constant_methodtype_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_methodtype_info->descriptor_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_methodtype_info;
                continue;
            case CONSTANT_InvokeDynamic:
                printf("CONSTANT_InvokeDynamic");
                CONSTANT_InvokeDynamic_info *constant_invokedynamic_info = (CONSTANT_InvokeDynamic_info *) malloc(
                        sizeof(CONSTANT_InvokeDynamic_info));
                constant_invokedynamic_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_invokedynamic_info->name_and_type_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_invokedynamic_info->bootstrap_method_attr_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_invokedynamic_info;
                continue;
            case CONSTANT_Module:
                printf("CONSTANT_InvokeDynamic");
                CONSTANT_Module_info *constant_module_info = (CONSTANT_Module_info *) malloc(sizeof(CONSTANT_Module_info));
                constant_module_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_module_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_module_info;
                continue;
            case CONSTANT_Package:
                printf("CONSTANT_InvokeDynamic");
                CONSTANT_Package_info *constant_package_info = (CONSTANT_Package_info *) malloc(sizeof(CONSTANT_Package_info));
                constant_package_info->tag = constant_pool->tag;
                class_file += sizeof(u1);
                constant_package_info->name_index = l2b_2(*(u2 *) class_file);
                class_file += sizeof(u2);
                constant_pool->info = constant_package_info;
                continue;
        }
        class.constant_pool[i].info = constant_pool;
        printf("\n");
    }
    class.access_flags = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.this_class = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.super_class = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    class.interfaces_count = l2b_2(*(u2 *) class_file);
    class_file += sizeof(u2);
    if(class.interfaces_count > 0){
        class.interfaces = (u2*) malloc(class.interfaces_count * sizeof(u2));
        for(int i = 0; i < class.interfaces_count; i++) {
            class.interfaces[i] = l2b_2(*(u2*) class_file);
            class_file += sizeof(u2);
        }
    }
    class.fields_count = l2b_2(*(u2*) class_file);
    class_file += sizeof(u2);
    if (class.fields_count > 0) {
        class.fields = (FieldInfo*) malloc(class.fields_count * sizeof(FieldInfo));
        for (int i = 0; i < class.fields_count; i++) {
            class.fields[i].access_flags = l2b_2(*(u2*)class_file);
            class_file += sizeof(u2);
            class.fields[i].name_index = l2b_2(*(u2*)class_file);
            class_file += sizeof(u2);
            class.fields[i].descriptor_index = l2b_2(*(u2*)class_file);
            class_file += sizeof(u2);
            class.fields[i].attributes_count = l2b_2(*(u2*)class_file);
            class_file += sizeof(u2);
            if (class.fields[i].attributes_count > 0) {
                class.fields[i].attributes = (AttributeInfo*) malloc(class.fields[i].attributes_count * sizeof(AttributeInfo));
                for (int j = 0; j < class.fields[i].attributes_count; j++) {
                    class.fields[i].attributes[j].attribute_name_index = l2b_2(*(u2*) class_file);
                    class_file += sizeof(u2);
                    class.fields[i].attributes[j].attribute_length = l2b_4(*(u4*) class_file);
                    class_file += sizeof(u4);
                    if (class.fields[i].attributes[j].attribute_length > 0) {
                        class.fields[i].attributes[j].info = malloc(sizeof(u1) * class.fields[i].attributes[j].attribute_length);
                        for (int k = 0; k < class.fields[i].attributes[j].attribute_length; k++) {
                            class.fields[i].attributes[j].info[k] = *(u1*) class_file;
                            class_file += sizeof(u1);
                        }
                    }
                }
            }
        }
    }
    class.methods_count = l2b_2(*(u2*) class_file);
    class_file += sizeof(u2);
    if (class.methods_count > 0) {
        class.methods = malloc(class.methods_count * sizeof(MethodInfo));
        for (int i = 0; i < class.methods_count; i++) {
            class.methods[i].access_flags = l2b_2(*(u2*) class_file);
            class_file += sizeof(u2);
            class.methods[i].name_index = l2b_2(*(u2*) class_file);
            class_file += sizeof(u2);
            class.methods[i].descriptor_index = l2b_2(*(u2*) class_file);
            class_file += sizeof(u2);
            class.methods[i].attributes_count = l2b_2(*(u2*) class_file);
            class_file += sizeof(u2);
            if (class.methods[i].attributes_count > 0) {
                class.methods[i].attributes = (AttributeInfo*) malloc(class.methods[i].attributes_count * sizeof(AttributeInfo));
                for (int j = 0; j < class.methods[i].attributes_count; j++) {
                    class.methods[i].attributes[j].attribute_name_index = l2b_2(*(u2*) class_file);
                    class_file += sizeof(u2);
                    class.methods[i].attributes[j].attribute_length = l2b_4(*(u4*) class_file);
                    class_file += sizeof(u4);
                    if (class.methods[i].attributes[j].attribute_length > 0) {
                        class.methods[i].attributes[j].info = malloc(sizeof(u1) * class.methods[i].attributes[j].attribute_length);
                        for (int k = 0; k < class.methods[i].attributes[j].attribute_length; k++) {
                            class.methods[i].attributes[j].info[k] = *(u1*) class_file;
                            class_file += sizeof(u1);
                        }
                    }
                }
            }
        }
    }

    class.attributes_count = l2b_2(*(u2*) class_file);
    class_file += sizeof(u2);
    if (class.attributes_count > 0) {
        class.attributes = (AttributeInfo*) malloc(class.attributes_count * sizeof(AttributeInfo));
        for (int j = 0; j < class.attributes_count; j++) {
            class.attributes[j].attribute_name_index = l2b_2(*(u2*) class_file);
            class_file += sizeof(u2);
            class.attributes[j].attribute_length = l2b_4(*(u4*) class_file);
            class_file += sizeof(u4);
            if (class.attributes[j].attribute_length > 0) {
                class.attributes[j].info = malloc(sizeof(u1) * class.attributes[j].attribute_length);
                for (int k = 0; k < class.attributes[j].attribute_length; k++) {
                    class.attributes[j].info[k] = *(u1*) class_file;
                    class_file += sizeof(u1);
                }
            }
        }
    }

    printf("\n");
    printf("%X, %d.%d, %d, %d", class.magic, class.major_version, class.minor_version, class.constant_pool_count,
           class.constant_pool->tag);

//    char *info = (char*)malloc(class.constant_pool_count * constant_info_size);
//    class.constant_pool->info = info;

    return 0;
}
