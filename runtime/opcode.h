//
// Created by wangzhanzhi on 2020/6/25.
//

#ifndef DISCJVM_OPCODE_H
#define DISCJVM_OPCODE_H

#include "../model/stack.h"
#include "../model/thread.h"
#include "../runtime/class_loader.h"
#include "../share/gc/serial/serial_heap.h"

typedef void (*Operator)(SerialHeap *heap, Thread *, Frame *);

void step_pc(Frame *frame, int offset);

int step_pc_and_read_pc(Frame *frame, int offset);

void step_pc_1(Frame *frame);

void back_pc_1(Frame *frame);

u4 step_pc_no_submit(Frame *frame, u4 offset);

u4 back_pc_no_submit(Frame *frame, u4 offset);

u4 back_pc_1_no_submit(Frame *frame);

u4 back_pc_2_no_submit(Frame *frame);

int back_pc_1_read_pc(Frame *frame);

void step_pc_2(Frame *frame);

int step_pc_2_read_pc(Frame *frame);

u1 read_code(Frame *frame);

u1 read_code_and_step_pc1(Frame *frame);

u1 step_pc1_and_read_code_no_submit(Frame *frame);

u1 step_pc2_and_read_code_no_submit(Frame *frame);

u1 step_pc_and_read_code_no_submit(u1 *code, Frame *frame, u4 offset);

u1 step_pc1_and_read_code(Frame *frame);

void init_instructions();

void invoke_method(Thread *thread, SerialHeap *heap);

#endif //DISCJVM_OPCODE_H
