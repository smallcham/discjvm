//
// Created by wangzhanzhi on 2020/9/25.
//

#include "FileDescriptor.h"

/* field id for jint 'fd' in java.io.FileDescriptor */
u2 io_fd_id;

/* field id for jboolean 'append' in java.io.FileDescriptor */
u2 io_append_fd_id;

void java_io_FileDescriptor_initIDs_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    ClassFile *class = load_class(thread, heap, "java/io/FileDescriptor");
    FieldInfo *io_fd_field = get_field_by_name_and_desc(class, "fd", "I");
    FieldInfo *io_fd_append_field = get_field_by_name_and_desc(class, "append", "Z");
    io_fd_id = io_fd_field->offset;
    io_append_fd_id = io_fd_append_field->offset;
}

void java_io_FileDescriptor_getHandle_9I0J(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_long(frame->operand_stack, -1);
}

void java_io_FileDescriptor_getAppend_9I0Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    int flags = fcntl(get_localvar(frame, 0), F_GETFL);
    push_int(frame->operand_stack, ((flags & O_APPEND) == 0) ? 1 : 0);
}