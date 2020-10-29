//
// Created by wangzhanzhi on 2020/9/25.
//

#include "Signal.h"

/* Find the signal number, given a name. Returns -1 for unknown signals. */
/* kill -l 获取信号列表 */
void jdk_internal_misc_Signal_findSignal0_9Ljava_lang_String10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *name_obj = get_ref_localvar(frame, 0);
    char *name = get_str_field_value_by_object(name_obj);
    if (NULL == name) {
        throw_exception_by_name_and_msg(thread, heap, "java/lang/IllegalArgumentException", "name is null");
        return;
    }
    int sig = -1;
    if (str_end_with(name, "HUP")) sig = 1;
    else if (str_end_with(name, "INT")) sig = 2;
    else if (str_end_with(name, "QUIT")) sig = 3;
    else if (str_end_with(name, "ILL")) sig = 4;
    else if (str_end_with(name, "TRAP")) sig = 5;
    else if (str_end_with(name, "ABRT")) sig = 6;
    else if (str_end_with(name, "BUS")) sig = 7;
    else if (str_end_with(name, "FPE")) sig = 8;
    else if (str_end_with(name, "KILL")) sig = 9;
    else if (str_end_with(name, "USR1")) sig = 10;
    else if (str_end_with(name, "SEGV")) sig = 11;
    else if (str_end_with(name, "USR2")) sig = 12;
    else if (str_end_with(name, "PIPE")) sig = 13;
    else if (str_end_with(name, "ALRM")) sig = 14;
    else if (str_end_with(name, "TERM")) sig = 15;
    else if (str_end_with(name, "STKFLT")) sig = 16;
    else if (str_end_with(name, "CHLD")) sig = 17;
    else if (str_end_with(name, "CONT")) sig = 18;
    else if (str_end_with(name, "STOP")) sig = 19;
    else if (str_end_with(name, "TSTP")) sig = 20;
    else if (str_end_with(name, "TTIN")) sig = 21;
    else if (str_end_with(name, "TTOU")) sig = 22;
    else if (str_end_with(name, "URG")) sig = 23;
    else if (str_end_with(name, "XCPU")) sig = 24;
    else if (str_end_with(name, "XFSZ")) sig = 25;
    else if (str_end_with(name, "VTALRM")) sig = 26;
    else if (str_end_with(name, "PROF")) sig = 27;
    else if (str_end_with(name, "WINCH")) sig = 28;
    else if (str_end_with(name, "IO")) sig = 29;
    else if (str_end_with(name, "PWR")) sig = 30;
    else if (str_end_with(name, "SYS")) sig = 31;
    else if (str_end_with(name, "RTMIN")) sig = 34;
    else if (str_end_with(name, "RTMIN+1")) sig = 35;
    else if (str_end_with(name, "RTMIN+2")) sig = 36;
    else if (str_end_with(name, "RTMIN+3")) sig = 37;
    else if (str_end_with(name, "RTMIN+4")) sig = 38;
    else if (str_end_with(name, "RTMIN+5")) sig = 39;
    else if (str_end_with(name, "RTMIN+6")) sig = 40;
    else if (str_end_with(name, "RTMIN+7")) sig = 41;
    else if (str_end_with(name, "RTMIN+8")) sig = 42;
    else if (str_end_with(name, "RTMIN+9")) sig = 43;
    else if (str_end_with(name, "RTMIN+10")) sig = 44;
    else if (str_end_with(name, "RTMIN+11")) sig = 45;
    else if (str_end_with(name, "RTMIN+12")) sig = 46;
    else if (str_end_with(name, "RTMIN+13")) sig = 47;
    else if (str_end_with(name, "RTMIN+14")) sig = 48;
    else if (str_end_with(name, "RTMIN+15")) sig = 49;
    else if (str_end_with(name, "RTMAX-14")) sig = 50;
    else if (str_end_with(name, "RTMAX-13")) sig = 51;
    else if (str_end_with(name, "RTMAX-12")) sig = 52;
    else if (str_end_with(name, "RTMAX-11")) sig = 53;
    else if (str_end_with(name, "RTMAX-10")) sig = 54;
    else if (str_end_with(name, "RTMAX-9")) sig = 55;
    else if (str_end_with(name, "RTMAX-8")) sig = 56;
    else if (str_end_with(name, "RTMAX-7")) sig = 57;
    else if (str_end_with(name, "RTMAX-6")) sig = 58;
    else if (str_end_with(name, "RTMAX-5")) sig = 59;
    else if (str_end_with(name, "RTMAX-4")) sig = 60;
    else if (str_end_with(name, "RTMAX-3")) sig = 61;
    else if (str_end_with(name, "RTMAX-2")) sig = 62;
    else if (str_end_with(name, "RTMAX-1")) sig = 63;
    else if (str_end_with(name, "RTMAX")) sig = 64;
    push_int(frame->operand_stack, sig);
}

/* Registers a native signal handler, and returns the old handler.
     * Handler values:
     *   0     default handler
     *   1     ignore the signal
     *   2     call back to Signal.dispatch
     *   other arbitrary native signal handlers
     */
void jdk_internal_misc_Signal_handle0_9IJ0J(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO being complete
    int sig = get_localvar(frame, 0);
    long handler = get_localvar(frame, 1);
    push_long(frame->operand_stack, handler);
}