#include <stdio.h>
#include <zconf.h>
#include "runtime/class_loader.h"
#include "runtime/opcode.h"
#include <dlfcn.h>
#include <assert.h>
#include <fcntl.h>
#include "model/zip_entry.h"
#include "stdlib.h"
#include "util/endian.h"
#include "zip.h"


int main(int argc, char *argv[]) {
    char buf[101];
    char path[200];
    getcwd(buf, sizeof(buf));
    init_instructions();

//    void* handle = dlopen("/usr/lib/jvm/java-11-openjdk-amd64/lib/libattach.so", RTLD_LAZY);
//    u1 (*defineModules)(char *name);
//    defineModules = dlsym(handle, "defineModules");
//    defineModules("java/lang/Object");

//    for (int i = 0; i < argc; i++) {
//        printf("%s", argv[i]);
//    }
//    sprintf(path, "%s/../test/class/Hello.class", buf);
//    ClassFile class = load_class(path);
//    invoke_method(&class, find_method(class, "main"));

//    gzFile infile = gzopen("/home/wangzhanzhi/winshare/java.base.jmod", "rb");
//    FILE *outfile = fopen("/home/wangzhanzhi/test1/111", "wb");
//    if (!infile || !outfile) return -1;
//
//    char buffer[128];
//    int num_read = 0;
//    gzseek(infile, 32, SEEK_SET);
//    while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0) {
//        for (int i = 0; i < sizeof(buffer); i++) {
//          printf("%c", buffer[i]);
//        }
//        return 0;
//    }
//    gzclose(infile);
//    fclose(outfile);
//    FILE *infile = fopen("/home/wangzhanzhi/work_temp/DedeCMS-V5.7-UTF8-SP2/uploads/include/data/base_dic_full.zip", "rb");
//    FILE *infile = fopen("/usr/lib/jvm/java-1.11.0-openjdk-amd64/jmods/java.base.jmod", "rb");
////    FILE *infile = fopen("/usr/lib/jvm/java-11-openjdk-amd64/jmods/java.base.jmod", "rb");
//    ZipHead zip_head = *(ZipHead*)malloc(sizeof(ZipHead));
//    int offset = 4;
//    fseek(infile, offset, SEEK_SET);
//    int head_size = 30;
//    for (int i = 0; i < 1; i++) {
//        fread(&zip_head, head_size, 1, infile);
//        printf("Magic: %X\n", zip_head.magic);
//        printf("CreateVersion: %d\n", zip_head.create_version);
//        printf("VersionLimit: %d\n", zip_head.reader_version);
//        printf("BitFlag: %d\n", zip_head.general_flag);
//        printf("CompressMethod: %X\n", zip_head.compress_method);
//        printf("LastMTime: %d\n", zip_head.last_m_time);
//        printf("LastMDate: %d\n", zip_head.last_m_date);
//        printf("Crc32: %d\n", zip_head.entry.crc_32);
//        printf("CSize: %d\n", zip_head.entry.compressed_size);
//        printf("UCSize: %d\n", zip_head.entry.uncompress_size);
//        printf("FileNameLen: %d\n", zip_head.entry.file_name_len);
//        printf("ExtraLen: %x\n", zip_head.entry.extra_len);
//        zip_head.entry.file_name = (u1*)malloc((sizeof(u1) * zip_head.entry.file_name_len) + 1);
//        offset += head_size;
//        fseek(infile, offset, SEEK_SET);
//        fread(zip_head.entry.file_name, zip_head.entry.file_name_len, 1, infile);
//        zip_head.entry.file_name[zip_head.entry.file_name_len] = '\0';
//        printf("FileName: %s\n", zip_head.entry.file_name);
//        offset += zip_head.entry.file_name_len;
//        printf("--------------------\n");
//    }
//    fclose(infile);


//    FILE *fp = fopen("/usr/lib/jvm/java-1.11.0-openjdk-amd64/jmods/java.base.jmod", "rb");
//    fseek(fp, 0, SEEK_END);
//    long f_size = ftell(fp);
//    int offset = 4;
//    u1 *data = (u1*)malloc((f_size - offset) * sizeof(u1));
//    rewind(fp);
//    fseek(fp, offset, SEEK_SET);
//    fread(data, (f_size - offset), 1, fp);
//    fclose(fp);
//    for (int i = 0; i < 1; i++) {
//        printf("Magic: %X\n", *(u4*) data);
//        data += sizeof(u4);
//        printf("CreateVersion: %d\n", *(u2*) data);
//        data += sizeof(u2);
//        printf("VersionLimit: %d\n", *(u2*) data);
//        data += sizeof(u2);
//        printf("BitFlag: %d\n", *(u2*) data);
//        data += sizeof(u2);
//        printf("CompressMethod: %X\n", *(u2*) data);
//        data += sizeof(u2);
//        printf("LastMTime: %d\n", *(u2*) data);
//        data += sizeof(u2);
//        printf("LastMDate: %d\n", *(u2*) data);
//        data += sizeof(u2);
//        printf("Crc32: %d\n", *(u2*) data);
//        data += sizeof(u4);
//        printf("CSize: %d\n", *(u4*) data);
//        data += sizeof(u4);
//        printf("UCSize: %d\n", *(u4*) data);
//        data += sizeof(u4);
//        u1 file_name_len = *(u4*) data;
//        printf("FileNameLen: %d\n", file_name_len);
//        data += sizeof(u2);
//        printf("ExtraLen: %x\n", *(u4*) data);
//        data += sizeof(u2);
//        u1 *file_name = (u1*)malloc((sizeof(u1) * file_name_len) + 1);
//        file_name[file_name_len] = '\0';
//        printf("FileName: %s\n", file_name);
//        printf("--------------------\n");
//    }


//    char *path1 = "/usr/lib/jvm/java-1.11.0-openjdk-amd64/jmods/java.base.jmod";
//    FILE *fp = fopen(path1, "rb");
//    fseek(fp, 0, SEEK_END);
//    long f_size = ftell(fp);
//    fclose(fp);
//    zip_error_t error;
//    zip_source_t *source = zip_source_file_create(path1, 4, f_size - 4, &error);
//    zip_t *zip_file = zip_open_from_source(source, ZIP_RDONLY, &error);
//    int index = zip_name_locate(zip_file, "AESWrapCipher.class", ZIP_FL_NODIR);
//    zip_file_t *f = zip_fopen_index(zip_file, index, 0);
//    zip_fread(f, buf, 100);
//    buf[100] = '\0';
//    printf("%d\n", index);
//    printf("%s\n", buf);

    int err = 0;
    zip_t *z = zip_open("/home/wangzhanzhi/work_temp/foo.zip", 0, &err);

    //Search for the file of given name
    const char *name = "file.txt";
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    //Alloc memory for its uncompressed contents
    char *contents = malloc(st.size);

    //Read the compressed file
    zip_file_t *f = zip_fopen(z, "file.txt", 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    //And close the archive
    zip_close(z);
    printf("%s\n", contents);

//    print_class_info(class);

//    printf("1: %s\n", argv[0]);
//    printf("2: %s", argv[1]);

//    sprintf(path, "%s/../../%s", argv[0], argv[1]);
//    printf("%s", path);
//    print_class_info(load_class(path));
    return 0;
}