//
// Created by wangzhanzhi on 2020/10/2.
//

#include "UnixNativeDispatcher.h"

static int attrs_st_mode;
static long attrs_st_ino;
static long attrs_st_dev;
static long attrs_st_rdev;
static int attrs_st_nlink;
static int attrs_st_uid;
static int attrs_st_gid;
static long attrs_st_size;
static long attrs_st_atime_sec;
static long attrs_st_atime_nsec;
static long attrs_st_mtime_sec;
static long attrs_st_mtime_nsec;
static long attrs_st_ctime_sec;
static long attrs_st_ctime_nsec;

static long attrs_f_frsize;
static long attrs_f_blocks;
static long attrs_f_bfree;
static long attrs_f_bavail;

static char *entry_name;
static char *entry_dir;
static char *entry_fstype;
static char *entry_options;
static long entry_dev;


void sun_nio_fs_UnixNativeDispatcher_init_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    Object *class_object = load_class(thread, heap, "sun/nio/fs/UnixFileAttributes")->class_object;
    attrs_st_mode = get_field_value_by_name_and_desc(class_object, "st_mode", "I");
    attrs_st_ino = get_field_value_by_name_and_desc(class_object, "st_ino", "J");
    attrs_st_dev = get_field_value_by_name_and_desc(class_object, "st_dev", "J");
    attrs_st_rdev = get_field_value_by_name_and_desc(class_object, "st_rdev", "J");
    attrs_st_nlink = get_field_value_by_name_and_desc(class_object, "st_nlink", "I");
    attrs_st_uid = get_field_value_by_name_and_desc(class_object, "st_uid", "I");
    attrs_st_gid = get_field_value_by_name_and_desc(class_object, "st_gid", "I");
    attrs_st_size = get_field_value_by_name_and_desc(class_object, "st_size", "J");
    attrs_st_atime_sec = get_field_value_by_name_and_desc(class_object, "st_atime_sec", "J");
    attrs_st_atime_nsec = get_field_value_by_name_and_desc(class_object, "st_atime_nsec", "J");
    attrs_st_mtime_sec = get_field_value_by_name_and_desc(class_object, "st_mtime_sec", "J");
    attrs_st_mtime_nsec = get_field_value_by_name_and_desc(class_object, "st_mtime_nsec", "J");
    attrs_st_ctime_sec = get_field_value_by_name_and_desc(class_object, "st_ctime_sec", "J");
    attrs_st_ctime_nsec = get_field_value_by_name_and_desc(class_object, "st_ctime_nsec", "J");

    class_object = load_class(thread, heap, "sun/nio/fs/UnixFileStoreAttributes")->class_object;
    attrs_f_frsize = get_field_value_by_name_and_desc(class_object, "f_frsize", "J");
    attrs_f_blocks = get_field_value_by_name_and_desc(class_object, "f_blocks", "J");
    attrs_f_bfree = get_field_value_by_name_and_desc(class_object, "f_bfree", "J");
    attrs_f_bavail = get_field_value_by_name_and_desc(class_object, "f_bavail", "J");

    class_object = load_class(thread, heap, "sun/nio/fs/UnixMountEntry")->class_object;
    entry_name = get_str_field_value_by_object_and_name(class_object, "name");
    entry_dir = get_str_field_value_by_object_and_name(class_object, "dir");
    entry_fstype = get_str_field_value_by_object_and_name(class_object, "fstype");
    entry_options = get_str_field_value_by_object_and_name(class_object, "opts");
    entry_dev = get_field_value_by_name_and_desc(class_object, "dev", "J");
    push_int(frame->operand_stack, 6);
}

void sun_nio_fs_UnixNativeDispatcher_getcwd_90Bs(Thread *thread, SerialHeap *heap, Frame *frame)
{
    char buf[PATH_MAX + 1];
    char *cwd = getcwd(buf, sizeof(buf));
    if (NULL == cwd) {
        printf_err("throwUnixException");
        exit(-1);
    } else {
        Array *array = malloc_array_by_type_size(thread, heap, load_primitive_class(thread, heap, "[B"), strlen(buf), sizeof(char));
        char *str = (char *) array->objects;
        for (int i = 0; i < array->length; i++) {
            str[i] = buf[i];
        }
        push_object(frame->operand_stack, array);
    }
}

void sun_nio_fs_UnixNativeDispatcher_stat1_9J0I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    long path_address = get_long_localvar(frame, 0);
    struct stat s_buf;
    int errno = stat((const char *) path_address, &s_buf);
    int rv;
    if (errno != 0) {
        rv = 0;
    } else {
        rv = s_buf.st_mode;
    }
    push_int(frame->operand_stack, rv);
}

/**
* int open(const char* path, int oflag, mode_t mode)
*/
void sun_nio_fs_UnixNativeDispatcher_open0_9JII0I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    char* path = (char*)get_long_localvar(frame, 0);
    int flags = get_localvar(frame, 2);
    int mode = get_localvar(frame, 3);
    int fd = open(path, flags, mode);
    push_int(frame->operand_stack, fd);
}

void sun_nio_fs_UnixNativeDispatcher_stat0_9JLsun_nio_fs_UnixFileAttributes10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    const char * path_address = (const char *)get_long_localvar(frame, 0);
    Object* attrs = get_ref_localvar(frame, 2);
    struct stat s_buf;
    int errno = stat((const char *) path_address, &s_buf);
    if (errno == -1) {
        printf_err("throwUnixException %d", errno);
        exit(-1);
    } else {
        put_value_field_by_name_and_desc(attrs, "st_mode", "I", s_buf.st_mode);
        put_value_field_by_name_and_desc(attrs, "st_ino", "J", s_buf.st_ino);
        put_value_field_by_name_and_desc(attrs, "st_dev", "J", s_buf.st_dev);
        put_value_field_by_name_and_desc(attrs, "st_rdev", "J", s_buf.st_rdev);
        put_value_field_by_name_and_desc(attrs, "st_nlink", "I", s_buf.st_nlink);
        put_value_field_by_name_and_desc(attrs, "st_uid", "I", s_buf.st_uid);
        put_value_field_by_name_and_desc(attrs, "st_gid", "I", s_buf.st_gid);
        put_value_field_by_name_and_desc(attrs, "st_size", "J", s_buf.st_size);
        put_value_field_by_name_and_desc(attrs, "st_atime_sec", "J", s_buf.st_atim.tv_sec);
        put_value_field_by_name_and_desc(attrs, "st_mtime_sec", "J", s_buf.st_mtim.tv_sec);
        put_value_field_by_name_and_desc(attrs, "st_ctime_sec", "J", s_buf.st_ctim.tv_sec);
        put_value_field_by_name_and_desc(attrs, "st_atime_nsec", "J", s_buf.st_atim.tv_nsec);
        put_value_field_by_name_and_desc(attrs, "st_mtime_nsec", "J", s_buf.st_mtim.tv_nsec);
        put_value_field_by_name_and_desc(attrs, "st_ctime_nsec", "J", s_buf.st_ctim.tv_nsec);
//        put_value_field_by_name_and_desc(attrs, "st_birthtime_sec", "J", );
    }
}