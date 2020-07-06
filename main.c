#include <stdio.h>
#include <zconf.h>
#include "runtime/class_loader.h"
#include "runtime/opcode.h"
#include <dlfcn.h>
#include "model/zip_entry.h"
#include "stdlib.h"
#include "util/endian.h"


int main(int argc, char *argv[]) {
    char buf[80];
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
    FILE *infile = fopen("/usr/lib/jvm/java-11-openjdk-amd64/jmods/java.base.jmod", "rb");
    ZipFile zip_file = *(ZipFile*)malloc(sizeof(ZipFile));
    fread(&zip_file, 18, 1, infile);
    printf("Head: %X\n", l2b_4(zip_file.head));
    printf("Magic: %X\n", l2b_4(zip_file.magic));
    printf("VersionLimit: %X\n", l2b_2(zip_file.version_limit));
    printf("BitFlag: %X\n", l2b_2(zip_file.bit_flag));
    printf("CompressMethod: %X\n", l2b_2(zip_file.compress_method));
    printf("LastMTime: %X\n", l2b_2(zip_file.last_m_time));
    printf("LastMDate: %X\n", l2b_2(zip_file.last_m_date));
    int offset = 18;
    fseek(infile, offset, SEEK_SET);
    ZipEntry entry = *(ZipEntry*)malloc(sizeof(ZipEntry));
    fread(&entry, 16, 1, infile);
    offset += 16;
    printf("Crc32: %x\n", l2b_4(entry.crc_32));
    printf("CSize: %x\n", l2b_4(entry.compressed_size));
    printf("UCSize: %x\n", l2b_4(entry.uncompress_size));
    printf("FileNameLen: %x\n", l2b_2(entry.file_name_len));
    printf("ExtraLen: %x\n", l2b_2(entry.extra_len));
    entry.file_name = (u1*)malloc((sizeof(u1) * entry.file_name_len) + 1);
    fseek(infile, offset, SEEK_SET);
    fread(entry.file_name, entry.file_name_len, 1, infile);
    entry.file_name[entry.file_name_len] = '\0';
    printf("FileName: %s\n", entry.file_name);
    return 0;

//    print_class_info(class);

//    printf("1: %s\n", argv[0]);
//    printf("2: %s", argv[1]);

//    sprintf(path, "%s/../../%s", argv[0], argv[1]);
//    printf("%s", path);
//    print_class_info(load_class(path));
    return 0;
}