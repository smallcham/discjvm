//
// Created by wangzhanzhi on 2020/10/11.
//

#include "IOUtil.h"

static int fd_fdid;

void sun_nio_ch_IOUtil_initIDs_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object* class = load_class(thread, heap, "java/io/FileDescriptor")->class_object;
    fd_fdid = get_field_value_by_name_and_desc(class, "fd", "I");
}

void sun_nio_ch_IOUtil_iovMax_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    long iov_max = sysconf(_SC_IOV_MAX);
    push_int(frame->operand_stack, iov_max == -1 ? 16 : (int)iov_max);
}