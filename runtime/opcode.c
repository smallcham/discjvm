//
// Created by wangzhanzhi on 2020/6/25.
//


#include "../model/data_struct.h"
#include "../model/thread.h"
#include "../runtime/class_loader.h"

typedef void (*Operator)(u1 *code, Thread *, Frame *);

void step_pc(Thread *thread, int offset)
{
    thread->pc += offset;
}

int step_pc_and_read_pc(Thread *thread, int offset)
{
    thread->pc += offset;
    return thread->pc;
}

void step_pc_1(Thread *thread)
{
    thread->pc ++;
}

int step_pc_1_read_pc(Thread *thread)
{
    step_pc_1(thread);
    return thread->pc;
}

void step_pc_2(Thread *thread)
{
    thread->pc += 2;
}

int step_pc_2_read_pc(Thread *thread)
{
    step_pc_2(thread);
    return thread->pc;
}

u1 read_code(u1 *code, Thread *thread)
{
    return code[thread->pc];
}

u1 read_code_and_step_pc1(u1 *code, Thread *thread)
{
    u1 op_code = read_code(code, thread);
    step_pc_1(thread);
    return op_code;
}

u1 step_pc1_and_read_code(u1 *code, Thread *thread)
{
    step_pc_1(thread);
    u1 op_code = read_code(code, thread);
    return op_code;
}

void nop(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
}
void aconst_null(u1 *code, Thread *thread, Frame *frame) {}
void iconst_m1(u1 *code, Thread *thread, Frame *frame) {}
void iconst_0(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    push_int(&(frame->operand_stack), 0);
}
void iconst_1(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    push_int(&(frame->operand_stack), 1);
}
void iconst_2(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    push_int(&(frame->operand_stack), 2);
}
void iconst_3(u1 *code, Thread *thread, Frame *frame) {}
void iconst_4(u1 *code, Thread *thread, Frame *frame) {}
void iconst_5(u1 *code, Thread *thread, Frame *frame) {}
void lconst_0(u1 *code, Thread *thread, Frame *frame) {}
void lconst_1(u1 *code, Thread *thread, Frame *frame) {}
void fconst_0(u1 *code, Thread *thread, Frame *frame) {}
void fconst_1(u1 *code, Thread *thread, Frame *frame) {}
void fconst_2(u1 *code, Thread *thread, Frame *frame) {}
void dconst_0(u1 *code, Thread *thread, Frame *frame) {}
void dconst_1(u1 *code, Thread *thread, Frame *frame) {}
void bipush(u1 *code, Thread *thread, Frame *frame) {
    push_int(&(frame->operand_stack), step_pc1_and_read_code(code, thread));
    step_pc_1(thread);
}
void sipush(u1 *code, Thread *thread, Frame *frame) {}
void ldc(u1 *code, Thread *thread, Frame *frame) {}
void ldc_w(u1 *code, Thread *thread, Frame *frame) {}
void ldc2_w(u1 *code, Thread *thread, Frame *frame) {}
void iload(u1 *code, Thread *thread, Frame *frame) {}
void lload(u1 *code, Thread *thread, Frame *frame) {}
void fload(u1 *code, Thread *thread, Frame *frame) {}
void dload(u1 *code, Thread *thread, Frame *frame) {}
void aload(u1 *code, Thread *thread, Frame *frame) {}
void iload_0(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    push_int(&(frame->operand_stack), frame->local_variables[0]);
}
void iload_1(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    push_int(&(frame->operand_stack), frame->local_variables[1]);
}
void iload_2(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    push_int(&(frame->operand_stack), frame->local_variables[2]);
}
void iload_3(u1 *code, Thread *thread, Frame *frame) {}
void lload_0(u1 *code, Thread *thread, Frame *frame) {}
void lload_1(u1 *code, Thread *thread, Frame *frame) {}
void lload_2(u1 *code, Thread *thread, Frame *frame) {}
void lload_3(u1 *code, Thread *thread, Frame *frame) {}
void fload_0(u1 *code, Thread *thread, Frame *frame) {}
void fload_1(u1 *code, Thread *thread, Frame *frame) {}
void fload_2(u1 *code, Thread *thread, Frame *frame) {}
void fload_3(u1 *code, Thread *thread, Frame *frame) {}
void dload_0(u1 *code, Thread *thread, Frame *frame) {}
void dload_1(u1 *code, Thread *thread, Frame *frame) {}
void dload_2(u1 *code, Thread *thread, Frame *frame) {}
void dload_3(u1 *code, Thread *thread, Frame *frame) {}
void aload_0(u1 *code, Thread *thread, Frame *frame) {}
void aload_1(u1 *code, Thread *thread, Frame *frame) {}
void aload_2(u1 *code, Thread *thread, Frame *frame) {}
void aload_3(u1 *code, Thread *thread, Frame *frame) {}
void iaload(u1 *code, Thread *thread, Frame *frame) {}
void laload(u1 *code, Thread *thread, Frame *frame) {}
void faload(u1 *code, Thread *thread, Frame *frame) {}
void daload(u1 *code, Thread *thread, Frame *frame) {}
void aaload(u1 *code, Thread *thread, Frame *frame) {}
void baload(u1 *code, Thread *thread, Frame *frame) {}
void caload(u1 *code, Thread *thread, Frame *frame) {}
void saload(u1 *code, Thread *thread, Frame *frame) {}
void istore(u1 *code, Thread *thread, Frame *frame) {}
void lstore(u1 *code, Thread *thread, Frame *frame) {}
void fstore(u1 *code, Thread *thread, Frame *frame) {}
void dstore(u1 *code, Thread *thread, Frame *frame) {}
void astore(u1 *code, Thread *thread, Frame *frame) {}
void istore_0(u1 *code, Thread *thread, Frame *frame) {}
void istore_1(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    frame->local_variables[1] = pop_int(&(frame->operand_stack));
}
void istore_2(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    frame->local_variables[2] = pop_int(&(frame->operand_stack));
}
void istore_3(u1 *code, Thread *thread, Frame *frame) {}
void lstore_0(u1 *code, Thread *thread, Frame *frame) {}
void lstore_1(u1 *code, Thread *thread, Frame *frame) {}
void lstore_2(u1 *code, Thread *thread, Frame *frame) {}
void lstore_3(u1 *code, Thread *thread, Frame *frame) {}
void fstore_0(u1 *code, Thread *thread, Frame *frame) {}
void fstore_1(u1 *code, Thread *thread, Frame *frame) {}
void fstore_2(u1 *code, Thread *thread, Frame *frame) {}
void fstore_3(u1 *code, Thread *thread, Frame *frame) {}
void dstore_0(u1 *code, Thread *thread, Frame *frame) {}
void dstore_1(u1 *code, Thread *thread, Frame *frame) {}
void dstore_2(u1 *code, Thread *thread, Frame *frame) {}
void dstore_3(u1 *code, Thread *thread, Frame *frame) {}
void astore_0(u1 *code, Thread *thread, Frame *frame) {}
void astore_1(u1 *code, Thread *thread, Frame *frame) {}
void astore_2(u1 *code, Thread *thread, Frame *frame) {}
void astore_3(u1 *code, Thread *thread, Frame *frame) {}
void iastore(u1 *code, Thread *thread, Frame *frame) {}
void lastore(u1 *code, Thread *thread, Frame *frame) {}
void fastore(u1 *code, Thread *thread, Frame *frame) {}
void dastore(u1 *code, Thread *thread, Frame *frame) {}
void aastore(u1 *code, Thread *thread, Frame *frame) {}
void bastore(u1 *code, Thread *thread, Frame *frame) {}
void castore(u1 *code, Thread *thread, Frame *frame) {}
void sastore(u1 *code, Thread *thread, Frame *frame) {}
void j_pop(u1 *code, Thread *thread, Frame *frame) {}
void pop2(u1 *code, Thread *thread, Frame *frame) {}
void dup(u1 *code, Thread *thread, Frame *frame) {}
void dup_x1(u1 *code, Thread *thread, Frame *frame) {}
void dup_x2(u1 *code, Thread *thread, Frame *frame) {}
void dup2(u1 *code, Thread *thread, Frame *frame) {}
void dup2_x1(u1 *code, Thread *thread, Frame *frame) {}
void dup2_x2(u1 *code, Thread *thread, Frame *frame) {}
void swap(u1 *code, Thread *thread, Frame *frame) {}
void iadd(u1 *code, Thread *thread, Frame *frame) {
    step_pc_1(thread);
    push_int(&(frame->operand_stack), pop_int(&(frame->operand_stack)) + pop_int(&(frame->operand_stack)));
}
void ladd(u1 *code, Thread *thread, Frame *frame) {}
void fadd(u1 *code, Thread *thread, Frame *frame) {}
void dadd(u1 *code, Thread *thread, Frame *frame) {}
void isub(u1 *code, Thread *thread, Frame *frame) {}
void lsub(u1 *code, Thread *thread, Frame *frame) {}
void fsub(u1 *code, Thread *thread, Frame *frame) {}
void dsub(u1 *code, Thread *thread, Frame *frame) {}
void imul(u1 *code, Thread *thread, Frame *frame) {}
void lmul(u1 *code, Thread *thread, Frame *frame) {}
void fmul(u1 *code, Thread *thread, Frame *frame) {}
void dmul(u1 *code, Thread *thread, Frame *frame) {}
void idiv(u1 *code, Thread *thread, Frame *frame) {}
void j_ldiv(u1 *code, Thread *thread, Frame *frame) {}
void fdiv(u1 *code, Thread *thread, Frame *frame) {}
void ddiv(u1 *code, Thread *thread, Frame *frame) {}
void irem(u1 *code, Thread *thread, Frame *frame) {}
void lrem(u1 *code, Thread *thread, Frame *frame) {}
void frem(u1 *code, Thread *thread, Frame *frame) {}
void drem(u1 *code, Thread *thread, Frame *frame) {}
void ineg(u1 *code, Thread *thread, Frame *frame) {}
void lneg(u1 *code, Thread *thread, Frame *frame) {}
void fneg(u1 *code, Thread *thread, Frame *frame) {}
void dneg(u1 *code, Thread *thread, Frame *frame) {}
void ishl(u1 *code, Thread *thread, Frame *frame) {}
void lshl(u1 *code, Thread *thread, Frame *frame) {}
void ishr(u1 *code, Thread *thread, Frame *frame) {}
void lshr(u1 *code, Thread *thread, Frame *frame) {}
void iushr(u1 *code, Thread *thread, Frame *frame) {}
void lushr(u1 *code, Thread *thread, Frame *frame) {}
void iand(u1 *code, Thread *thread, Frame *frame) {}
void land(u1 *code, Thread *thread, Frame *frame) {}
void ior(u1 *code, Thread *thread, Frame *frame) {}
void lor(u1 *code, Thread *thread, Frame *frame) {}
void ixor(u1 *code, Thread *thread, Frame *frame) {}
void lxor(u1 *code, Thread *thread, Frame *frame) {}
void iinc(u1 *code, Thread *thread, Frame *frame) {
    frame->local_variables[step_pc1_and_read_code(code, thread)] += step_pc1_and_read_code(code, thread);
    step_pc_1(thread);
}
void i2l(u1 *code, Thread *thread, Frame *frame) {}
void i2f(u1 *code, Thread *thread, Frame *frame) {}
void i2d(u1 *code, Thread *thread, Frame *frame) {}
void l2i(u1 *code, Thread *thread, Frame *frame) {}
void l2f(u1 *code, Thread *thread, Frame *frame) {}
void l2d(u1 *code, Thread *thread, Frame *frame) {}
void f2i(u1 *code, Thread *thread, Frame *frame) {}
void f2l(u1 *code, Thread *thread, Frame *frame) {}
void f2d(u1 *code, Thread *thread, Frame *frame) {}
void d2i(u1 *code, Thread *thread, Frame *frame) {}
void d2l(u1 *code, Thread *thread, Frame *frame) {}
void d2f(u1 *code, Thread *thread, Frame *frame) {}
void i2b(u1 *code, Thread *thread, Frame *frame) {}
void i2c(u1 *code, Thread *thread, Frame *frame) {}
void i2s(u1 *code, Thread *thread, Frame *frame) {}
void lcmp(u1 *code, Thread *thread, Frame *frame) {}
void fcmpl(u1 *code, Thread *thread, Frame *frame) {}
void fcmpg(u1 *code, Thread *thread, Frame *frame) {}
void dcmpl(u1 *code, Thread *thread, Frame *frame) {}
void dcmpg(u1 *code, Thread *thread, Frame *frame) {}
void ifeq(u1 *code, Thread *thread, Frame *frame) {}
void ifne(u1 *code, Thread *thread, Frame *frame) {}
void iflt(u1 *code, Thread *thread, Frame *frame) {}
void ifge(u1 *code, Thread *thread, Frame *frame) {}
void ifgt(u1 *code, Thread *thread, Frame *frame) {}
void ifle(u1 *code, Thread *thread, Frame *frame) {}
void if_icmpeq(u1 *code, Thread *thread, Frame *frame) {
    int value2 = pop_int(&(frame->operand_stack));
    int value1 = pop_int(&(frame->operand_stack));
    u1 branch1 = step_pc1_and_read_code(code, thread);
    u1 branch2 = step_pc1_and_read_code(code, thread);
    thread->pc = (value1 == value2) ? step_pc_and_read_pc(thread, (branch1 << 8) | branch2) : step_pc_1_read_pc(thread);
}
void if_icmpne(u1 *code, Thread *thread, Frame *frame) {}
void if_icmplt(u1 *code, Thread *thread, Frame *frame) {}
void if_icmpge(u1 *code, Thread *thread, Frame *frame) {}
void if_icmpgt(u1 *code, Thread *thread, Frame *frame) {
    int value2 = pop_int(&(frame->operand_stack));
    int value1 = pop_int(&(frame->operand_stack));
    u1 branch1 = step_pc1_and_read_code(code, thread);
    u1 branch2 = step_pc1_and_read_code(code, thread);
    thread->pc = (value1 > value2) ? step_pc_and_read_pc(thread, (short)((branch1 << 8) | branch2)) : step_pc_1_read_pc(thread);
}
void if_icmple(u1 *code, Thread *thread, Frame *frame) {}
void if_acmpeq(u1 *code, Thread *thread, Frame *frame) {}
void if_acmpne(u1 *code, Thread *thread, Frame *frame) {}
void j_goto(u1 *code, Thread *thread, Frame *frame) {
    u1 branch1 = step_pc1_and_read_code(code, thread);
    u1 branch2 = step_pc1_and_read_code(code, thread);
    thread->pc = step_pc_and_read_pc(thread, (short)((branch1 << 8) | branch2));
}
void jsr(u1 *code, Thread *thread, Frame *frame) {}
void ret(u1 *code, Thread *thread, Frame *frame) {}
void tableswitch(u1 *code, Thread *thread, Frame *frame) {}
void lookupswitch(u1 *code, Thread *thread, Frame *frame) {}
void ireturn(u1 *code, Thread *thread, Frame *frame) {}
void lreturn(u1 *code, Thread *thread, Frame *frame) {}
void freturn(u1 *code, Thread *thread, Frame *frame) {}
void dreturn(u1 *code, Thread *thread, Frame *frame) {}
void areturn(u1 *code, Thread *thread, Frame *frame) {}
void j_return(u1 *code, Thread *thread, Frame *frame) {
    printf("SUM: %d", frame->local_variables[1]);
}
void getstatic(u1 *code, Thread *thread, Frame *frame) {}
void putstatic(u1 *code, Thread *thread, Frame *frame) {}
void getfield(u1 *code, Thread *thread, Frame *frame) {}
void putfield(u1 *code, Thread *thread, Frame *frame) {}
void invokevirtual(u1 *code, Thread *thread, Frame *frame) {}
void invokespecial(u1 *code, Thread *thread, Frame *frame) {}
void invokestatic(u1 *code, Thread *thread, Frame *frame) {}
void invokeinterface(u1 *code, Thread *thread, Frame *frame) {}
void invokedynamic(u1 *code, Thread *thread, Frame *frame) {}
void new(u1 *code, Thread *thread, Frame *frame) {}
void newarray(u1 *code, Thread *thread, Frame *frame) {}
void anewarray(u1 *code, Thread *thread, Frame *frame) {}
void arraylength(u1 *code, Thread *thread, Frame *frame) {}
void athrow(u1 *code, Thread *thread, Frame *frame) {}
void checkcast(u1 *code, Thread *thread, Frame *frame) {}
void instanceof(u1 *code, Thread *thread, Frame *frame) {}
void monitorenter(u1 *code, Thread *thread, Frame *frame) {}
void monitorexit(u1 *code, Thread *thread, Frame *frame) {}
void wide(u1 *code, Thread *thread, Frame *frame) {}
void multianewarray(u1 *code, Thread *thread, Frame *frame) {}
void ifnull(u1 *code, Thread *thread, Frame *frame) {}
void ifnonnull(u1 *code, Thread *thread, Frame *frame) {}
void goto_w(u1 *code, Thread *thread, Frame *frame) {}
void jsr_w(u1 *code, Thread *thread, Frame *frame) {}
void breakpoint(u1 *code, Thread *thread, Frame *frame) {}
void impdep1(u1 *code, Thread *thread, Frame *frame) {}
void impdep2(u1 *code, Thread *thread, Frame *frame) {}

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
    instructions[0x73] = drem;
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

void exec(Operator operator, u1 *code, Thread *thread, Frame *param)
{
    operator(code, thread, param);
}

void invoke_method(MethodInfo method)
{
    CodeAttribute code = get_method_code(method);
    Thread thread = create_thread(100, 100);
    Frame *frame = create_vm_frame(method.name_index, code.max_locals, code.max_stack);
    push_stack(thread.vm_stack, frame);
    do {
        printf("%#x\n", read_code(code.code, &thread));
        exec(instructions[read_code(code.code, &thread)], code.code, &thread, frame);
    } while (thread.pc <= 20);
}