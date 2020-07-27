//
// Created by wangzhanzhi on 2020/7/16.
//

#ifndef DISCJVM_OBJECT_H
#define DISCJVM_OBJECT_H

#include "class.h"

typedef struct {
    ClassFile *class;
    u4 length;
    Field *fields;
} Object;

#endif //DISCJVM_OBJECT_H
