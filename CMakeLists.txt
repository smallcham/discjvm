cmake_minimum_required(VERSION 3.16)
project(discjvm C)

set(CMAKE_C_STANDARD 99)

add_executable(discjvm main.c util/endian.c runtime/class_loader.c runtime/class_loader.h model/base_type.h model/class.h model/constant_class.h util/endian.h runtime/opcode.c runtime/opcode.h model/thread.h model/gc.h model/data_struct.h)