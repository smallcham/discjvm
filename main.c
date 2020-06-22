#include <stdio.h>
#include <zconf.h>
#include "class/class_loader.h"

int main() {
    char buf[80];
    char path[200];
    getcwd(buf, sizeof(buf));

    sprintf(path, "%s/../test/class/Hello.class", buf);
    load_class(path);
    return 0;
}
