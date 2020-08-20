#include <zconf.h>
#include "runtime/bootstrap.h"

int main(int argc, char *argv[]) {
    char buf[101];
    char path[200];
    getcwd(buf, sizeof(buf));

    sprintf(path, "%s/../test/class/Hello.class", buf);
    start_vm(path);

//    u8 a = 0xaaaaaaaaaaaaaaad;
//    u4 b = (int)a;
//    u4 c = (int)(a>>32);
    return 0;
}