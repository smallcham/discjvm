//
// Created by wangzhanzhi on 2020/9/25.
//

#include <sys/stat.h>
#include "UnixFileSystem.h"

static struct {
    u2 path;
} ids;

void java_io_UnixFileSystem_initIDs_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    FieldInfo *field = get_field_by_name_and_desc(load_class(thread, heap, "java/io/File"), "path", "Ljava/lang/String;");
    ids.path = field->offset;
}

void java_io_UnixFileSystem_getBooleanAttributes0_9Ljava_io_File10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *file = get_ref_localvar(frame, 1);
    char *path = get_str_field_value_by_object(file->fields[ids.path].object_value);
    int rv = 0;
    struct stat s_buf;
    stat(path, &s_buf);
    if (S_ISREG(s_buf.st_mode)) {
        rv |= 0x01;
    }
    if (S_ISDIR(s_buf.st_mode)) {
        rv |= 0x04;
    }
    push_int(frame->operand_stack, rv);
}

void java_io_UnixFileSystem_canonicalize0_9Ljava_lang_String10Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO 校验路径是否合法, 需要参考jdk11/ UnixFileSystem_md.c, canonicalize_md.c
    char *path = get_str_field_value_by_object(get_ref_localvar(frame, 1));
    push_slot(frame->operand_stack, create_str_slot_set_str(thread, heap, path));
}