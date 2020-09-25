//
// Created by wangzhanzhi on 2020/9/25.
//

#include "UnixFileSystem.h"

static struct {
    u2 path;
} ids;

void java_io_UnixFileSystem_initIDs_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    FieldInfo *field = get_field_by_name_and_desc(load_class(thread, heap, "java/io/File"), "path", "Ljava/lang/String;");
    ids.path = field->offset;
}