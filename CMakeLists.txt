cmake_minimum_required(VERSION 3.16)
project(discjvm C)

set(CMAKE_C_STANDARD 99)

add_executable(discjvm main.c util/endian.c class/class_loader.c class/class_loader.h model/base_type.h model/class.h model/constant_class.h util/endian.h)