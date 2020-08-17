//
// Created by wangzhanzhi on 2020/8/6.
//

#ifndef DISCJVM_NATIVE_FACTORY_H
#define DISCJVM_NATIVE_FACTORY_H

#include "../../model/hash_map.h"
#include "../../util/string_util.h"
#include "../../util/ioutil.h"
#include "java/lang/Object.h"
#include "java/lang/Class.h"
#include "java/lang/System.h"
#include "java/lang/Thread.h"
#include "jdk/internal/misc/Unsafe.h"
#include "java/lang/ClassLoader.h"
#include "java/lang/Runtime.h"
#include "java/security/AccessController.h"
#include "java/lang/Throwable.h"

typedef void (*NativeMethod)(Thread *, SerialHeap *, Frame *);

HashMap *native_pool;

void init_native_factory();

NativeMethod find_native(char *class_name, char *method_name, char *method_desc);

void invoke_native(Thread *thread, SerialHeap *heap);

void create_c_frame_and_invoke(Thread *thread, SerialHeap *heap, Frame *frame, char *class_name, char *method_name, char *method_desc);

void create_c_frame_and_invoke_add_params(Thread *thread, SerialHeap *heap, Frame *frame, MethodInfo *method, char *class_name, char *method_name, char *method_desc);

void create_c_frame_and_invoke_add_params_plus1(Thread *thread, SerialHeap *heap, Frame *frame, MethodInfo *method, char *class_name, char *method_name, char *method_desc);

#endif //DISCJVM_NATIVE_FACTORY_H
