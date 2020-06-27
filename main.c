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
    invoke_method(get_main_method(class));
//    print_class_info(class);

//    printf("1: %s\n", argv[0]);
//    printf("2: %s", argv[1]);

//    sprintf(path, "%s/../../%s", argv[0], argv[1]);
//    printf("%s", path);
//    print_class_info(load_class(path));

//    Stack stack = {0, 2, NULL, NULL};
//    push(&stack, 1);
//    push(&stack, 2);
//    printf("%d\t", pop(&stack));
//    printf("%d\t", pop(&stack));
//    push(&stack, 3);
//    push(&stack, 5);
//    printf("%d\t", pop(&stack));
//    printf("%d\t", pop(&stack));
//    push(&stack, 7);
//    push(&stack, 4);
//    printf("%d\t", pop(&stack));
//    printf("%d\t", pop(&stack));

//    Frame frame = create_frame(9, 9);
//    frame.local_variables[0].value = 100;
//    frame.local_variables[1].value = -100;
//    frame.local_variables[2].value = 11;
//    frame.local_variables[9].value = (u4) NULL;
//
//    push_int(&frame.operand_stack, 100);
//    push_int(&frame.operand_stack, -100);
//    push_float(&frame.operand_stack, 102.32f);
//
//    printf("%f\n", pop_float(&frame.operand_stack));
//    printf("%d\n", pop_int(&frame.operand_stack));
//    printf("%d\n", pop_int(&frame.operand_stack));
    return 0;
}
