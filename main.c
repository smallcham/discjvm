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

    FILE *infile = fopen("/home/wangzhanzhi/winshare/java.base.jmod", "rb");

    ZipFile zip_file = *(ZipFile*)malloc(sizeof(ZipFile));
    fread(&zip_file, sizeof(zip_file), 1, infile);
    printf("%#x\n", l2b_4(zip_file.head));
    printf("%#x\n", l2b_4(zip_file.magic));
    return 0;

//    print_class_info(class);

//    printf("1: %s\n", argv[0]);
//    printf("2: %s", argv[1]);

//    sprintf(path, "%s/../../%s", argv[0], argv[1]);
//    printf("%s", path);
//    print_class_info(load_class(path));
    return 0;
}