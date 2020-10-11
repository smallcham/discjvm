//
// Created by wangzhanzhi on 2020/10/11.
//

#include "FileChannelImpl.h"

static long chan_fd;

void sun_nio_ch_FileChannelImpl_initIDs_90J(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *class = load_class(thread, heap, "sun/nio/ch/FileChannelImpl")->class_object;
    long page_size = sysconf(_SC_PAGESIZE);
    chan_fd = get_field_value_by_name_and_desc(class, "fd", "Ljava/io/FileDescriptor;");
    push_long(frame->operand_stack, page_size);
}