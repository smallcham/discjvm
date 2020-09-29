#include <zconf.h>
#include "runtime/bootstrap.h"

int main(int argc, char *argv[]) {
    char buf[101];
    char path[200];
    getcwd(buf, sizeof(buf));

    sprintf(path, "%s/../test/class/Hello.class", buf);
    start_vm(path);

//    float a = 84.0f;
//    printf("%f", a);

//Array *ref = malloc(sizeof(Array));
//printf("%p, %p, %p, %p\n", ref, &ref->class, &ref->length, &ref->objects);

//    printf("%d\n",sizeof(struct test));

//
//    struct test a = {2, NULL};
//    printf("%d  , %p\n", sizeof(struct test), &a.b);

//    char *b = "12312";
//    char *c = "ddd";
    //todo: 转 指针类型, 实际赋值是 8个字节
//    long *p = (char*)&a + 8;
    // 给 *p 一个8位地址就可以了
//    *p = c;

//  printf("%p, %p,  %s\n", &a, p, a.b );
    printf_succ("\t\t\t************RUN SUCCESS!**************");
    return 0;
}