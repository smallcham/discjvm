#include <zconf.h>
#include "runtime/bootstrap.h"

int main(int argc, char *argv[]) {
    char buf[101];
    char path[200];
    getcwd(buf, sizeof(buf));

    sprintf(path, "%s/../test/class/Hello.class", buf);
    start_vm(path);

//    start_vm("java/lang/Object.class");
    return 0;
}