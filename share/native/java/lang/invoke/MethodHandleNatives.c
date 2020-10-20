//
// Created by wangzhanzhi on 2020/10/19.
//

#include "MethodHandleNatives.h"

void java_lang_invoke_MethodHandleNatives_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{

}

void java_lang_invoke_MethodHandleNatives_resolve_9Ljava_lang_invoke_MemberName1Ljava_lang_Class1Z0Ljava_lang_invoke_MemberName1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *self = get_ref_localvar(frame, 0);
    Object *caller = get_ref_localvar(frame, 1);
    int speculative_resolve = get_localvar(frame, 3);

    Object *class = get_field_object_value_by_name_and_desc(self, "clazz", "Ljava/lang/Class;");
    char *name = get_str_field_value_by_object(get_field_object_value_by_name_and_desc(self, "name", "Ljava/lang/String;"));
    Object *type = get_field_object_value_by_name_and_desc(self, "type", "Ljava/lang/Object;");
    int flags = get_field_value_by_name_and_desc(self, "flags", "I");

    Stack *params = create_unlimit_stack();
    Slot *_return = create_slot();
    push_object(params, self);
    single_invoke(heap, self->class, "getSignature", "()Ljava/lang/String;", params, _return);
    free(params);
    char *signature = get_str_field_value_by_object(_return->object_value);
    if (signature[0] == '(') {
        MethodInfo *method = find_method_with_desc(thread, heap, class->raw_class, name, signature);
        put_value_field_by_name_and_desc(self, "flags", "I", method->access_flags);
    }

    push_object(frame->operand_stack, self);

//    int ref_kind = (flags >> MN_REFERENCE_KIND_SHIFT) & MN_REFERENCE_KIND_MASK;
//
//    if ((flags & ALL_KINDS) == MN_IS_METHOD && (ref_kind == REF_invokeVirtual || ref_kind == REF_invokeSpecial || ref_kind == REF_invokeStatic)) {
//
//    }

//    switch (flags & ALL_KINDS) {
//        case MN_IS_METHOD: {
//            if (ref_kind == REF_invokeStatic) {
//
//            } else if (ref_kind == REF_invokeInterface) {
//
//            } else if (ref_kind == REF_invokeSpecial) {
//
//            } else if (ref_kind == REF_invokeVirtual) {
//
//            } else {
//                printf_err("ref_kind=%d", ref_kind);
//                exit(-1);
//            }
//        }
//        case MN_IS_CONSTRUCTOR: {
//            if (strcmp(name, "<init>") == 0) {
//                //LinkResolver::resolve_special_call(result, Handle(), link_info, THREAD);
//            } else {
//                break;
//            }
//
//        }
//        case MN_IS_FIELD: {
//
//        }
//        default: {
//
//        }
//    }
}