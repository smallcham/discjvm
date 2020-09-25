//
// Created by wangzhanzhi on 2020/9/25.
//

#include "FileOutputStream.h"

u2 fos_fd;

void java_io_FileOutputStream_initIDs_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    FieldInfo *field = get_field_by_name_and_desc(load_class(thread, heap, "java/io/FileOutputStream"), "fd", "Ljava/io/FileDescriptor;");
    fos_fd = field->offset;
}

