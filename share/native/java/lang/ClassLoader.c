//
// Created by wangzhanzhi on 2020/8/13.
//

#include "ClassLoader.h"

void java_lang_ClassLoader_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame) {}

void java_lang_ClassLoader_findBuiltinLib_9Ljava_lang_String10Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    char *cname = get_str_field_value_by_object(get_ref_localvar(frame, 0));
    if (NULL == cname) {
        printf_err("java_lang_ClassLoader_findBuiltinLib_9Ljava_lang_String10Ljava_lang_String1, NULL filename for native library");
        exit(-1);
    }
//    char *libname = malloc(strlen(JNI_LIB_PREFIX) + strlen(JNI_LIB_SUFFIX) + strlen(cname) + 1);
//    sprintf(libname, "%s/lib/%s%s%s", JAVA_HOME, JNI_LIB_PREFIX, cname, JNI_LIB_SUFFIX);
//    if (access(libname, F_OK) < 0) {
//        push_slot(frame->operand_stack, NULL_SLOT);
//    } else {
//        push_object(frame->operand_stack, create_str_slot_set_str(thread, heap, libname));
//    }
//    free(libname);
    push_slot(frame->operand_stack, NULL_SLOT);
}