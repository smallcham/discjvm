#include <stdio.h>
#include <zconf.h>
#include "class/class_loader.h"

int main() {
    char buf[80];
    char path[200];
    getcwd(buf, sizeof(buf));

    sprintf(path, "%s/../test/class/Hello.class", buf);
    load_class(path);

//    FILE *fp = fopen(path, "rb");
//    char dat[50];
//    fread(&dat, sizeof(char)*50, 1, fp);
//    long long d;
//    memcpy(&d, dat, 8);
//    printf("%x", d);
    return 0;
}
