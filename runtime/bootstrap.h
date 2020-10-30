//
// Created by wangzhanzhi on 2020/7/9.
//

#ifndef DISCJVM_BOOTSTRAP_H
#define DISCJVM_BOOTSTRAP_H

#include "../share/gc/serial/serial_heap.h"
#include "../share/native/native_factory.h"
#include "jvm.h"
#include "opcode.h"

#define LD_LIBRARY_PATH "LD_LIBRARY_PATH"

void print_version();

void print_help();

void init_lib(Thread *thread, SerialHeap *heap);

void init_lib_by_names(Thread *thread, SerialHeap *heap, char *names[], int count);

void start_vm(char *class_path, int log_level);

#endif //DISCJVM_BOOTSTRAP_H
