cmake_minimum_required(VERSION 3.16)
project(discjvm C)

set(CMAKE_C_STANDARD 99)

add_executable(discjvm main.c util/endian.c runtime/class_loader.c runtime/class_loader.h model/base_type.h model/class.h model/constant_class.h util/endian.h runtime/opcode.c runtime/opcode.h model/thread.h model/stack.h share/gc/serial/serial_heap.c share/gc/serial/serial_heap.h model/hash_map.h util/string_util.h runtime/jmod.h runtime/bootstrap.c runtime/bootstrap.h)
TARGET_LINK_LIBRARIES(discjvm libzip.so)