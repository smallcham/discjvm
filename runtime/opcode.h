//
// Created by wangzhanzhi on 2020/6/25.
//

#ifndef DISCJVM_OPCODE_H
#define DISCJVM_OPCODE_H

#include "../model/class.h"

void init_instructions();
_Noreturn void invoke_method(MethodInfo method);

#endif //DISCJVM_OPCODE_H
