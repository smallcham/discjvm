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

/**
 * Writes a sub array as a sequence of bytes.
 * @param b the data to be written
 * @param off the start offset in the data
 * @param len the number of bytes that are written
 * @param append {@code true} to first advance the position to the
 *     end of file
 * @exception IOException If an I/O error has occurred.
 */
void java_io_FileOutputStream_writeBytes_9BsIIZ0V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    int n = -1;
    Object *this = get_localvar_this(frame);
    Array *bytes = get_ref_localvar(frame, 1);
    int off = get_localvar(frame, 2);
    int len = get_localvar(frame, 3);
    int append = get_localvar(frame, 4);
    char stack_buf[BUFSIZ];
    char *buf;

    if (off < 0 || len < 0 || bytes->length - off < len ) {
        throw_exception_by_name(thread, heap, "java/lang/IndexOutOfBoundsException");
        return;
    }

    if (len == 0) return;
    if (len > BUFSIZ) {
        buf = malloc(len);
    } else {
        buf = stack_buf;
    }

    memcpy(buf, bytes->objects + off, len);
    Object *fd_object = get_field_object_value_by_name_and_desc(this, "fd", "Ljava/io/FileDescriptor;");
    while (len > 0) {
        int fd = get_field_value_by_name_and_desc(fd_object, "fd", "I");
        if (fd == -1) {
            throw_exception_by_name_and_msg(thread, heap, "java/lang/RuntimeException", "Stream Closed");
            return;
        }
        n = write(fd, buf + off, len);
        if (n == -1) {
            throw_exception_by_name_and_msg(thread, heap, "java/lang/RuntimeException", "Write Error");
            return;
        }
        off += n;
        len -= n;
    }
    if (buf != stack_buf) {
        free(buf);
    }
}