//
// Created by wangzhanzhi on 2020/9/24.
//

#include "FileInputStream.h"

/* id for jobject 'fd' in java.io.FileInputStream */
u2 fis_fd;

void java_io_FileInputStream_initIDs_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    FieldInfo *field = get_field_by_name_and_desc(load_class(thread, heap, "java/io/FileInputStream"), "fd", "Ljava/io/FileDescriptor;");
    fis_fd = field->offset;
}

