//
// Created by wangzhanzhi on 2020/6/22.
//

#ifndef DISCJVM_CLASS_LOADER_H
#define DISCJVM_CLASS_LOADER_H
#include "../model/class.h"

ClassFile load_class(char *path);
void print_class_info(ClassFile class);
CodeAttribute get_method_code(MethodInfo method);
MethodInfo get_main_method(ClassFile class);

#endif //DISCJVM_CLASS_LOADER_H
