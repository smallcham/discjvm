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
#include "jdk/internal/misc/VM.h"
#include "java/lang/reflect/Array.h"
#include "java/lang/Float.h"
#include "java/lang/Double.h"
#include "java/io/FileInputStream.h"
#include "java/io/FileDescriptor.h"
#include "java/io/FileOutputStream.h"
#include "jdk/internal/misc/Signal.h"
#include "java/io/UnixFileSystem.h"
#include "jdk/internal/reflect/Reflection.h"
#include "sun/nio/fs/UnixNativeDispatcher.h"
#include "java/lang/ref/Reference.h"
#include "jdk/internal/jimage/NativeImageBuffer.h"
#include "java/util/concurrent/atomic/AtomicLong.h"
#include "sun/nio/ch/IOUtil.h"
#include "sun/nio/ch/FileChannelImpl.h"
#include "sun/nio/ch/FileDispatcherImpl.h"
#include "java/lang/StringUTF16.h"
#include "jdk/internal/reflect/NativeMethodAccessorImpl.h"
#include "java/lang/invoke/MethodHandleNatives.h"
#include "java/lang/StackTraceElement.h"

typedef void (*NativeMethod)(Thread *, SerialHeap *, Frame *);

HashMap *native_pool;

void init_native_factory();

NativeMethod find_native(char *class_name, char *method_name, char *method_desc);

void invoke_native(Thread *thread, SerialHeap *heap);

Frame *create_c_frame_and_invoke_add_params(Thread *thread, SerialHeap *heap, Frame *frame, Stack *params, char *class_name, MethodInfo *method);

Frame *create_c_frame_and_invoke_add_params_plus1(Thread *thread, SerialHeap *heap, Frame *frame, Stack *params, char *class_name, MethodInfo *method);

#endif //DISCJVM_NATIVE_FACTORY_H
