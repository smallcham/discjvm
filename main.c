#include <stdio.h>
#include <zconf.h>
#include "runtime/class_loader.h"
#include "runtime/opcode.h"

int main(int argc, char *argv[]) {
    char buf[80];
    char path[200];
    getcwd(buf, sizeof(buf));
    init_instructions();

//    for (int i = 0; i < argc; i++) {
//        printf("%s", argv[i]);
//    }
    sprintf(path, "%s/../test/class/Hello.class", buf);
    ClassFile class = load_class(path);
    invoke_method(&class, find_method(class, "main"));
//    print_class_info(class);

//    printf("1: %s\n", argv[0]);
//    printf("2: %s", argv[1]);

//    sprintf(path, "%s/../../%s", argv[0], argv[1]);
//    printf("%s", path);
//    print_class_info(load_class(path));
    return 0;
}
