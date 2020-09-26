//
// Created by wangzhanzhi on 2020/7/6.
//

#ifndef DISCJVM_JMOD_H
#define DISCJVM_JMOD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/base_type.h"
#include "zip.h"

#define JNI_LIB_PREFIX "lib"
#define JNI_LIB_SUFFIX ".so"

extern char *JAVA_HOME;


u1 *load_from_jmod(char *jmod_name, char *name);

#endif //DISCJVM_JMOD_H
