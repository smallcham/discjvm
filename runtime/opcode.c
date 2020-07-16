//
// Created by wangzhanzhi on 2020/6/25.
//

#include "opcode.h"

void step_pc(Frame *frame, int offset)
{
    frame->pc += offset;
}

int step_pc_and_read_pc(Frame *frame, int offset)
{
    frame->pc += offset;
    return frame->pc;
}

void step_pc_1(Frame *frame)
{
    frame->pc ++;
}

void back_pc_1(Frame *frame)
{
    frame->pc --;
}

u4 step_pc_no_submit(Frame *frame, u4 offset)
{
    return frame->pc + offset;
}

u4 back_pc_no_submit(Frame *frame, u4 offset)
{
    return frame->pc - offset;
}

u4 step_pc_1_no_submit(Frame *frame)
{
    return step_pc_no_submit(frame, 1);
}

u4 back_pc_1_no_submit(Frame *frame)
{
    return back_pc_no_submit(frame, 1);
}

u4 step_pc_2_no_submit(Frame *frame)
{
    return step_pc_no_submit(frame, 2);
}

u4 back_pc_2_no_submit(Frame *frame)
{
    return back_pc_no_submit(frame, 2);
}

int step_pc_1_read_pc(Frame *frame)
{
    step_pc_1(frame);
    return frame->pc;
}

int back_pc_1_read_pc(Frame *frame)
{
    back_pc_1(frame);
    return frame->pc;
}

void step_pc_2(Frame *frame)
{
    frame->pc += 2;
}

int step_pc_2_read_pc(Frame *frame)
{
    step_pc_2(frame);
    return frame->pc;
}

u1 read_code(Frame *frame)
{
    return frame->code_info->code[frame->pc];
}

u1 read_code_and_step_pc1(Frame *frame)
{
    u1 op_code = read_code(frame);
    step_pc_1(frame);
    return op_code;
}

u1 step_pc1_and_read_code_no_submit(Frame *frame)
{
    return frame->code_info->code[step_pc_1_no_submit(frame)];
}

u1 step_pc2_and_read_code_no_submit(Frame *frame)
{
    return frame->code_info->code[step_pc_2_no_submit(frame)];
}

u1 step_pc_and_read_code_no_submit(u1 *code, Frame *frame, u4 offset)
{
    return code[step_pc_no_submit(frame, offset)];
}

u1 step_pc1_and_read_code(Frame *frame)
{
    step_pc_1(frame);
    u1 op_code = read_code(frame);
    return op_code;
}

void nop(SerialHeap *heap, u1 *code, Frame *frame) {
    step_pc_1(frame);
}

void aconst_null(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_stack(frame->operand_stack, NULL);
    step_pc_1(frame);
}

void iconst_m1(SerialHeap *heap, Thread *thread, Frame *frame) {}

void iconst_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, 0);
}

void iconst_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, 1);
}

void iconst_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, 2);
}

void iconst_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, 3);
}

void iconst_4(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, 4);
}

void iconst_5(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, 5);
}

void lconst_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_long(frame->operand_stack, 0);
}

void lconst_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_long(frame->operand_stack, 1);
}

void fconst_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_float(frame->operand_stack, 0);
}

void fconst_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_float(frame->operand_stack, 1);
}

void fconst_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_float(frame->operand_stack, 2);
}

void dconst_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_double(frame->operand_stack, 0);
}

void dconst_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_float(frame->operand_stack, 1);
}

void bipush(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, step_pc1_and_read_code(frame));
    step_pc_1(frame);
}

void sipush(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte2 = step_pc1_and_read_code(frame);
    u1 byte1 = step_pc1_and_read_code(frame);
    short value = (byte1 << 8) | byte2;
    push_int(frame->operand_stack, (int)value);
    step_pc_1(frame);
}

void ldc(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_stack(frame->operand_stack, get_str_from_string_index(frame->constant_pool, step_pc1_and_read_code(frame)));
    step_pc_1(frame);
}

void ldc_w(SerialHeap *heap, Thread *thread, Frame *frame) {}

void ldc2_w(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    u2 index = (byte1 << 8) | byte2;
    CONSTANT_Long_info long_info = *(CONSTANT_Long_info*)frame->constant_pool[index].info;
    push_int(frame->operand_stack, long_info.high_bytes);
    push_int(frame->operand_stack, long_info.low_bytes);
}

void iload(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, frame->local_variables[step_pc1_and_read_code(frame)]);
    step_pc_1(frame);
}

void lload(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 index = step_pc1_and_read_code(frame);
    push_int(frame->operand_stack, frame->local_variables[index + 1]);
    push_int(frame->operand_stack, frame->local_variables[index]);
    step_pc_1(frame);
}

void fload(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, frame->local_variables[step_pc1_and_read_code(frame)]);
    step_pc_1(frame);
}

void dload(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 index = step_pc1_and_read_code(frame);
    push_int(frame->operand_stack, frame->local_variables[index + 1]);
    push_int(frame->operand_stack, frame->local_variables[index]);
    step_pc_1(frame);
}

void aload(SerialHeap *heap, Thread *thread, Frame *frame) {}

void iload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, frame->local_variables[0]);
}

void iload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, frame->local_variables[1]);
}

void iload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, frame->local_variables[2]);
}

void iload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, frame->local_variables[3]);
}

void lload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    push_int(frame->operand_stack, 0);
    step_pc_1(frame);
}

void lload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    push_int(frame->operand_stack, 1);
    step_pc_1(frame);
}

void lload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    push_int(frame->operand_stack, 2);
    step_pc_1(frame);
}

void lload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    push_int(frame->operand_stack, 3);
    step_pc_1(frame);
}

void fload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, 0);
    step_pc_1(frame);
}

void fload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, 1);
    step_pc_1(frame);
}

void fload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, 2);
    step_pc_1(frame);
}

void fload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_float(frame->operand_stack, 3);
    step_pc_1(frame);
}

void dload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    push_int(frame->operand_stack, 0);
    step_pc_1(frame);
}

void dload_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    push_int(frame->operand_stack, 0);
    step_pc_1(frame);
}

void dload_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    push_int(frame->operand_stack, 2);
    step_pc_1(frame);
}

void dload_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_int(frame->operand_stack, 0);
    push_int(frame->operand_stack, 3);
    step_pc_1(frame);
}

void aload_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    push_stack(frame->operand_stack, &(frame->class->runtime_fields->slot[0]));
    step_pc_1(frame);
}

void aload_1(SerialHeap *heap, Thread *thread, Frame *frame) {}
void aload_2(SerialHeap *heap, Thread *thread, Frame *frame) {}
void aload_3(SerialHeap *heap, Thread *thread, Frame *frame) {}
void iaload(SerialHeap *heap, Thread *thread, Frame *frame) {}
void laload(SerialHeap *heap, Thread *thread, Frame *frame) {}
void faload(SerialHeap *heap, Thread *thread, Frame *frame) {}
void daload(SerialHeap *heap, Thread *thread, Frame *frame) {}
void aaload(SerialHeap *heap, Thread *thread, Frame *frame) {}
void baload(SerialHeap *heap, Thread *thread, Frame *frame) {}
void caload(SerialHeap *heap, Thread *thread, Frame *frame) {}
void saload(SerialHeap *heap, Thread *thread, Frame *frame) {}
void istore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lstore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fstore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dstore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void astore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void istore_0(SerialHeap *heap, Thread *thread, Frame *frame) {}

void istore_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame->local_variables[1] = pop_int(frame->operand_stack);
    step_pc_1(frame);
}

void istore_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame->local_variables[2] = pop_int(frame->operand_stack);
    step_pc_1(frame);
}

void istore_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame->local_variables[3] = pop_int(frame->operand_stack);
    step_pc_1(frame);
}

void lstore_0(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame->local_variables[0] = pop_int(frame->operand_stack);
    frame->local_variables[1] = pop_int(frame->operand_stack);
    step_pc_1(frame);
}

void lstore_1(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame->local_variables[1] = pop_int(frame->operand_stack);
    frame->local_variables[2] = pop_int(frame->operand_stack);
    step_pc_1(frame);
}

void lstore_2(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame->local_variables[2] = pop_int(frame->operand_stack);
    frame->local_variables[3] = pop_int(frame->operand_stack);
    step_pc_1(frame);
}

void lstore_3(SerialHeap *heap, Thread *thread, Frame *frame) {
    frame->local_variables[3] = pop_int(frame->operand_stack);
    frame->local_variables[4] = pop_int(frame->operand_stack);
    step_pc_1(frame);
}

void fstore_0(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fstore_1(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fstore_2(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fstore_3(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dstore_0(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dstore_1(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dstore_2(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dstore_3(SerialHeap *heap, Thread *thread, Frame *frame) {}
void astore_0(SerialHeap *heap, Thread *thread, Frame *frame) {}
void astore_1(SerialHeap *heap, Thread *thread, Frame *frame) {}
void astore_2(SerialHeap *heap, Thread *thread, Frame *frame) {}
void astore_3(SerialHeap *heap, Thread *thread, Frame *frame) {}
void iastore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lastore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fastore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dastore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void aastore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void bastore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void castore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void sastore(SerialHeap *heap, Thread *thread, Frame *frame) {}
void j_pop(SerialHeap *heap, Thread *thread, Frame *frame) {}
void pop2(SerialHeap *heap, Thread *thread, Frame *frame) {}

void dup(SerialHeap *heap, Thread *thread, Frame *frame) {
    void *value = get_stack(frame->operand_stack);
    push_stack(frame->operand_stack, value);
    push_stack(frame->operand_stack, value);
    step_pc_1(frame);
}
void dup_x1(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dup_x2(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dup2(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dup2_x1(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dup2_x2(SerialHeap *heap, Thread *thread, Frame *frame) {}
void swap(SerialHeap *heap, Thread *thread, Frame *frame) {}

void iadd(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc_1(frame);
    push_int(frame->operand_stack, pop_int(frame->operand_stack) + pop_int(frame->operand_stack));
}

void ladd(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fadd(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dadd(SerialHeap *heap, Thread *thread, Frame *frame) {}
void isub(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lsub(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fsub(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dsub(SerialHeap *heap, Thread *thread, Frame *frame) {}
void imul(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lmul(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fmul(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dmul(SerialHeap *heap, Thread *thread, Frame *frame) {}
void idiv(SerialHeap *heap, Thread *thread, Frame *frame) {}
void j_ldiv(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fdiv(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ddiv(SerialHeap *heap, Thread *thread, Frame *frame) {}
void irem(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lrem(SerialHeap *heap, Thread *thread, Frame *frame) {}
void frem(SerialHeap *heap, Thread *thread, Frame *frame) {}
void j_drem(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ineg(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lneg(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fneg(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dneg(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ishl(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lshl(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ishr(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lshr(SerialHeap *heap, Thread *thread, Frame *frame) {}
void iushr(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lushr(SerialHeap *heap, Thread *thread, Frame *frame) {}
void iand(SerialHeap *heap, Thread *thread, Frame *frame) {}
void land(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ior(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lor(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ixor(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lxor(SerialHeap *heap, Thread *thread, Frame *frame) {}

void iinc(SerialHeap *heap, Thread *thread, Frame *frame) {
    u4 index = step_pc1_and_read_code(frame);
    u4 increment =  step_pc1_and_read_code(frame);
    frame->local_variables[index] += increment;
    step_pc_1(frame);
}

void i2l(SerialHeap *heap, Thread *thread, Frame *frame) {}
void i2f(SerialHeap *heap, Thread *thread, Frame *frame) {}
void i2d(SerialHeap *heap, Thread *thread, Frame *frame) {}
void l2i(SerialHeap *heap, Thread *thread, Frame *frame) {}
void l2f(SerialHeap *heap, Thread *thread, Frame *frame) {}
void l2d(SerialHeap *heap, Thread *thread, Frame *frame) {}
void f2i(SerialHeap *heap, Thread *thread, Frame *frame) {}
void f2l(SerialHeap *heap, Thread *thread, Frame *frame) {}
void f2d(SerialHeap *heap, Thread *thread, Frame *frame) {}
void d2i(SerialHeap *heap, Thread *thread, Frame *frame) {}
void d2l(SerialHeap *heap, Thread *thread, Frame *frame) {}
void d2f(SerialHeap *heap, Thread *thread, Frame *frame) {}
void i2b(SerialHeap *heap, Thread *thread, Frame *frame) {}
void i2c(SerialHeap *heap, Thread *thread, Frame *frame) {}
void i2s(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lcmp(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fcmpl(SerialHeap *heap, Thread *thread, Frame *frame) {}
void fcmpg(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dcmpl(SerialHeap *heap, Thread *thread, Frame *frame) {}
void dcmpg(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ifeq(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ifne(SerialHeap *heap, Thread *thread, Frame *frame) {}
void iflt(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ifge(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ifgt(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ifle(SerialHeap *heap, Thread *thread, Frame *frame) {}

void if_icmpeq(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    frame->pc = (value1 == value2) ? step_pc_and_read_pc(frame, (branch1 << 8) | branch2) : step_pc_and_read_pc(frame, 3);
}

void if_icmpne(SerialHeap *heap, Thread *thread, Frame *frame) {}
void if_icmplt(SerialHeap *heap, Thread *thread, Frame *frame) {}
void if_icmpge(SerialHeap *heap, Thread *thread, Frame *frame) {}

void if_icmpgt(SerialHeap *heap, Thread *thread, Frame *frame) {
    int value2 = pop_int(frame->operand_stack);
    int value1 = pop_int(frame->operand_stack);
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    // 如果条件成立，则将程序计数器pc前移分支1、2计算得出的offset偏移量， 否则将程pc前移3步（分别为 - 1：前移指令、2：分支一指令、3：分支二指令）
    frame->pc = (value1 > value2) ? step_pc_and_read_pc(frame, (short)((branch1 << 8) | branch2)) : step_pc_and_read_pc(frame, 3);
}

void if_icmple(SerialHeap *heap, Thread *thread, Frame *frame) {}
void if_acmpeq(SerialHeap *heap, Thread *thread, Frame *frame) {}
void if_acmpne(SerialHeap *heap, Thread *thread, Frame *frame) {
    Object *value2 = pop_stack(frame->operand_stack);
    Object *value1 = pop_stack(frame->operand_stack);
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    // 如果条件成立，则将程序计数器pc前移分支1、2计算得出的offset偏移量， 否则将程pc前移3步（分别为 - 1：前移指令、2：分支一指令、3：分支二指令）
    frame->pc = (value1 > value2) ? step_pc_and_read_pc(frame, (short)((branch1 << 8) | branch2)) : step_pc_and_read_pc(frame, 3);
}

void j_goto(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 branch1 = step_pc1_and_read_code_no_submit(frame);
    u1 branch2 = step_pc2_and_read_code_no_submit(frame);
    frame->pc = step_pc_and_read_pc(frame, (short)((branch1 << 8) | branch2));
}

void jsr(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ret(SerialHeap *heap, Thread *thread, Frame *frame) {}
void tableswitch(SerialHeap *heap, Thread *thread, Frame *frame) {}
void lookupswitch(SerialHeap *heap, Thread *thread, Frame *frame) {}

int ireturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    pop_frame(thread->vm_stack);
    return pop_int(frame->operand_stack);
}

long lreturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    pop_frame(thread->vm_stack);
    return pop_long(frame->operand_stack);
}

float freturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    pop_frame(thread->vm_stack);
    return pop_float(frame->operand_stack);
}

double dreturn(SerialHeap *heap, Thread *thread, Frame *frame) {
    pop_frame(thread->vm_stack);
    return pop_double(frame->operand_stack);
}

void areturn(SerialHeap *heap, Thread *thread, Frame *frame) {}
void j_return(SerialHeap *heap, Thread *thread, Frame *frame) {
    printf("%d", frame->local_variables[1]);
    pop_frame(thread->vm_stack);
}

void getstatic(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
//    CONSTANT_Fieldref_info field_ref_info = *(CONSTANT_Fieldref_info*)frame->constant_pool[(byte1 << 8) | byte2].info;
//    CONSTANT_Class_info class_info = *(CONSTANT_Class_info*)frame->constant_pool[field_ref_info.class_index].info;
//    CONSTANT_NameAndType_info name_and_type_info = *(CONSTANT_NameAndType_info*)frame->constant_pool[field_ref_info.name_and_type_index].info;
//    CONSTANT_Utf8_info class_name_info = *(CONSTANT_Utf8_info*)frame->constant_pool[class_info.name_index].info;
//    CONSTANT_Utf8_info field_type_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.name_index].info;
//    CONSTANT_Utf8_info field_desc_info = *(CONSTANT_Utf8_info*)frame->constant_pool[name_and_type_info.descriptor_index].info;
    get_field_by_index(thread, heap, frame, (byte1 << 8) | byte2);
}

void putstatic(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    set_field_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}
void getfield(SerialHeap *heap, Thread *thread, Frame *frame) {}
void putfield(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    set_field_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}
void invokevirtual(SerialHeap *heap, Thread *thread, Frame *frame) {}
void invokespecial(SerialHeap *heap, Thread *thread, Frame *frame) {
    step_pc(frame, 3);
}
void invokestatic(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    do_invokestatic_by_index(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc(frame, 3);
}
void invokeinterface(SerialHeap *heap, Thread *thread, Frame *frame) {}
void invokedynamic(SerialHeap *heap, Thread *thread, Frame *frame) {}
void new(SerialHeap *heap, Thread *thread, Frame *frame) {
    u1 byte1 = step_pc1_and_read_code(frame);
    u1 byte2 = step_pc1_and_read_code(frame);
    create_object(thread, heap, frame, (byte1 << 8) | byte2);
    step_pc_1(frame);
}
void newarray(SerialHeap *heap, Thread *thread, Frame *frame) {}
void anewarray(SerialHeap *heap, Thread *thread, Frame *frame) {}
void arraylength(SerialHeap *heap, Thread *thread, Frame *frame) {}
void athrow(SerialHeap *heap, Thread *thread, Frame *frame) {}
void checkcast(SerialHeap *heap, Thread *thread, Frame *frame) {}
void instanceof(SerialHeap *heap, Thread *thread, Frame *frame) {}
void monitorenter(SerialHeap *heap, Thread *thread, Frame *frame) {}
void monitorexit(SerialHeap *heap, Thread *thread, Frame *frame) {}
void wide(SerialHeap *heap, Thread *thread, Frame *frame) {}
void multianewarray(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ifnull(SerialHeap *heap, Thread *thread, Frame *frame) {}
void ifnonnull(SerialHeap *heap, Thread *thread, Frame *frame) {}
void goto_w(SerialHeap *heap, Thread *thread, Frame *frame) {}
void jsr_w(SerialHeap *heap, Thread *thread, Frame *frame) {}
void breakpoint(SerialHeap *heap, Thread *thread, Frame *frame) {}
void impdep1(SerialHeap *heap, Thread *thread, Frame *frame) {}
void impdep2(SerialHeap *heap, Thread *thread, Frame *frame) {}

Operator instructions[0x100];

void init_instructions()
{
    // Constants
    instructions[0x00] = nop;
    instructions[0x01] = aconst_null;
    instructions[0x02] = iconst_m1;
    instructions[0x03] = iconst_0;
    instructions[0x04] = iconst_1;
    instructions[0x05] = iconst_2;
    instructions[0x06] = iconst_3;
    instructions[0x07] = iconst_4;
    instructions[0x08] = iconst_5;
    instructions[0x09] = lconst_0;
    instructions[0x0a] = lconst_1;
    instructions[0x0b] = fconst_0;
    instructions[0x0c] = fconst_1;
    instructions[0x0d] = fconst_2;
    instructions[0x0e] = dconst_0;
    instructions[0x0f] = dconst_1;
    instructions[0x10] = bipush;
    instructions[0x11] = sipush;
    instructions[0x12] = ldc;
    instructions[0x13] = ldc_w;
    instructions[0x14] = ldc2_w;

    //Loads
    instructions[0x15] = iload;
    instructions[0x16] = lload;
    instructions[0x17] = fload;
    instructions[0x18] = dload;
    instructions[0x19] = aload;
    instructions[0x1a] = iload_0;
    instructions[0x1b] = iload_1;
    instructions[0x1c] = iload_2;
    instructions[0x1d] = iload_3;
    instructions[0x1e] = lload_0;
    instructions[0x1f] = lload_1;
    instructions[0x20] = lload_2;
    instructions[0x21] = lload_3;
    instructions[0x22] = fload_0;
    instructions[0x23] = fload_1;
    instructions[0x24] = fload_2;
    instructions[0x25] = fload_3;
    instructions[0x26] = dload_0;
    instructions[0x27] = dload_1;
    instructions[0x28] = dload_2;
    instructions[0x29] = dload_3;
    instructions[0x2a] = aload_0;
    instructions[0x2b] = aload_1;
    instructions[0x2c] = aload_2;
    instructions[0x2d] = aload_3;
    instructions[0x2e] = iaload;
    instructions[0x2f] = laload;
    instructions[0x30] = faload;
    instructions[0x31] = daload;
    instructions[0x32] = aaload;
    instructions[0x33] = baload;
    instructions[0x34] = caload;
    instructions[0x35] = saload;

    //Stores
    instructions[0x36] = istore;
    instructions[0x37] = lstore;
    instructions[0x38] = fstore;
    instructions[0x39] = dstore;
    instructions[0x3a] = astore;
    instructions[0x3b] = istore_0;
    instructions[0x3c] = istore_1;
    instructions[0x3d] = istore_2;
    instructions[0x3e] = istore_3;
    instructions[0x3f] = lstore_0;
    instructions[0x40] = lstore_1;
    instructions[0x41] = lstore_2;
    instructions[0x42] = lstore_3;
    instructions[0x43] = fstore_0;
    instructions[0x44] = fstore_1;
    instructions[0x45] = fstore_2;
    instructions[0x46] = fstore_3;
    instructions[0x47] = dstore_0;
    instructions[0x48] = dstore_1;
    instructions[0x49] = dstore_2;
    instructions[0x4a] = dstore_3;
    instructions[0x4b] = astore_0;
    instructions[0x4c] = astore_1;
    instructions[0x4d] = astore_2;
    instructions[0x4e] = astore_3;
    instructions[0x4f] = iastore;
    instructions[0x50] = lastore;
    instructions[0x51] = fastore;
    instructions[0x52] = dastore;
    instructions[0x53] = aastore;
    instructions[0x54] = bastore;
    instructions[0x55] = castore;
    instructions[0x56] = sastore;

    //Stack
    instructions[0x57] = j_pop;
    instructions[0x58] = pop2;
    instructions[0x59] = dup;
    instructions[0x5a] = dup_x1;
    instructions[0x5b] = dup_x2;
    instructions[0x5c] = dup2;
    instructions[0x5d] = dup2_x1;
    instructions[0x5e] = dup2_x2;
    instructions[0x5f] = swap;

    //Math
    instructions[0x60] = iadd;
    instructions[0x61] = ladd;
    instructions[0x62] = fadd;
    instructions[0x63] = dadd;
    instructions[0x64] = isub;
    instructions[0x65] = lsub;
    instructions[0x66] = fsub;
    instructions[0x67] = dsub;
    instructions[0x68] = imul;
    instructions[0x69] = lmul;
    instructions[0x6a] = fmul;
    instructions[0x6b] = dmul;
    instructions[0x6c] = idiv;
    instructions[0x6d] = j_ldiv;
    instructions[0x6e] = fdiv;
    instructions[0x6f] = ddiv;
    instructions[0x70] = irem;
    instructions[0x71] = lrem;
    instructions[0x72] = frem;
    instructions[0x73] = j_drem;
    instructions[0x74] = ineg;
    instructions[0x75] = lneg;
    instructions[0x76] = fneg;
    instructions[0x77] = dneg;
    instructions[0x78] = ishl;
    instructions[0x79] = lshl;
    instructions[0x7a] = ishr;
    instructions[0x7b] = lshr;
    instructions[0x7c] = iushr;
    instructions[0x7d] = lushr;
    instructions[0x7e] = iand;
    instructions[0x7f] = land;
    instructions[0x80] = ior;
    instructions[0x81] = lor;
    instructions[0x82] = ixor;
    instructions[0x83] = lxor;
    instructions[0x84] = iinc;

    //Conversions
    instructions[0x85] = i2l;
    instructions[0x86] = i2f;
    instructions[0x87] = i2d;
    instructions[0x88] = l2i;
    instructions[0x89] = l2f;
    instructions[0x8a] = l2d;
    instructions[0x8b] = f2i;
    instructions[0x8c] = f2l;
    instructions[0x8d] = f2d;
    instructions[0x8e] = d2i;
    instructions[0x8f] = d2l;
    instructions[0x90] = d2f;
    instructions[0x91] = i2b;
    instructions[0x92] = i2c;
    instructions[0x93] = i2s;

    //Comparisons
    instructions[0x94] = lcmp;
    instructions[0x95] = fcmpl;
    instructions[0x96] = fcmpg;
    instructions[0x97] = dcmpl;
    instructions[0x98] = dcmpg;
    instructions[0x99] = ifeq;
    instructions[0x9a] = ifne;
    instructions[0x9b] = iflt;
    instructions[0x9c] = ifge;
    instructions[0x9d] = ifgt;
    instructions[0x9e] = ifle;
    instructions[0x9f] = if_icmpeq;
    instructions[0xa0] = if_icmpne;
    instructions[0xa1] = if_icmplt;
    instructions[0xa2] = if_icmpge;
    instructions[0xa3] = if_icmpgt;
    instructions[0xa4] = if_icmple;
    instructions[0xa5] = if_acmpeq;
    instructions[0xa6] = if_acmpne;

    //Control
    instructions[0xa7] = j_goto;
    instructions[0xa8] = jsr;
    instructions[0xa9] = ret;
    instructions[0xaa] = tableswitch;
    instructions[0xab] = lookupswitch;
    instructions[0xac] = ireturn;
    instructions[0xad] = lreturn;
    instructions[0xae] = freturn;
    instructions[0xaf] = dreturn;
    instructions[0xb0] = areturn;
    instructions[0xb1] = j_return;

    //References
    instructions[0xb2] = getstatic;
    instructions[0xb3] = putstatic;
    instructions[0xb4] = getfield;
    instructions[0xb5] = putfield;
    instructions[0xb6] = invokevirtual;
    instructions[0xb7] = invokespecial;
    instructions[0xb8] = invokestatic;
    instructions[0xb9] = invokeinterface;
    instructions[0xba] = invokedynamic;
    instructions[0xbb] = new;
    instructions[0xbc] = newarray;
    instructions[0xbd] = anewarray;
    instructions[0xbe] = arraylength;
    instructions[0xbf] = athrow;
    instructions[0xc0] = checkcast;
    instructions[0xc1] = instanceof;
    instructions[0xc2] = monitorenter;
    instructions[0xc3] = monitorexit;

    //Extended
    instructions[0xc4] = wide;
    instructions[0xc5] = multianewarray;
    instructions[0xc6] = ifnull;
    instructions[0xc7] = ifnonnull;
    instructions[0xc8] = goto_w;
    instructions[0xc9] = jsr_w;

    //Reserved
    instructions[0xca] = breakpoint;
    instructions[0xfe] = impdep1;
    instructions[0xff] = impdep2;
}

void pop_frame(Stack *vm_stack)
{
    Frame *frame = pop_stack(vm_stack);
    if (NULL != frame->pop_hook) frame->pop_hook(frame);
}

void exec(Operator operator, SerialHeap *heap, Thread *thread, Frame *frame)
{
    operator(heap, thread, frame);
}

void invoke_method(Thread *thread, SerialHeap *heap) {
    do {
        Frame *frame = get_stack(thread->vm_stack);
        exec(instructions[read_code(frame)], heap, thread, frame);
        printf("%#x\n", read_code(frame));
    } while (!is_empty_stack(thread->vm_stack));
}