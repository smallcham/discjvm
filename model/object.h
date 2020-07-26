//
// Created by wangzhanzhi on 2020/7/16.
//

#ifndef DISCJVM_OBJECT_H
#define DISCJVM_OBJECT_H

#include "class.h"

typedef struct {
    ClassFile *class;
} Object;

typedef struct {
    u4 length;
    Object *objects;
} Array;

#endif //DISCJVM_OBJECT_H
