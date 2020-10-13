//
// Created by wangzhanzhi on 2020/8/13.
//

#include "Unsafe.h"

void conjoint_jshorts_atomic(short* from, short* to, size_t count);
void conjoint_jints_atomic(int* from, int* to, size_t count);
void conjoint_jlongs_atomic(long* from, long* to, size_t count);
void atomic_copy64(const long *from, long *to);
void *index_oop_from_field_offset_long(void *p, long field_offset);

void jdk_internal_misc_Unsafe_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void jdk_internal_misc_Unsafe_arrayBaseOffset0_9java_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *ref = frame->local_variables[1]->object_value;
    if (!is_array_by_raw(ref)) {
        printf_err("Invalid Class, [%s] Not A Array", ref->class->class_name);
        exit(-1);
    } else if (is_array_by_raw(ref)) {
        push_int(frame->operand_stack, offsetof(Array, objects));
    } else {
        //ShouldNotReachHere
        printf_err("ShouldNotReachHere");
    }
}

/**
 * Reports the scale factor for addressing elements in the storage
 * allocation of a given array class.  However, arrays of "narrow" types
 * will generally not work properly with accessors like {@link
 * #getByte(Object, long)}, so the scale factor for such classes is reported
 * as zero.
 */
void jdk_internal_misc_Unsafe_arrayIndexScale0_9Ljava_lang_Class10I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_ref_localvar(frame, 1);
    int type_size;
    switch (object->raw_class->class_name[1]) {
        case 'Z': case 'C': case 'B':
            type_size = sizeof(char);
            break;
        case 'F':
            type_size = sizeof(float);
            break;
        case 'D':
            type_size = sizeof(double);
            break;
        case 'S':
            type_size = sizeof(short);
            break;
        case 'I':
            type_size = sizeof(int);
            break;
        case 'J':
            type_size = sizeof(long);
            break;
        default:
            type_size = sizeof(Object*);
            break;
    }
    push_int(frame->operand_stack, type_size);
}

/**
 * Reports the size in bytes of a native pointer, as stored via {@link
 * #putAddress}.  This value will be either 4 or 8.  Note that the sizes of
 * other primitive types (as stored in native memory blocks) is determined
 * fully by their information content.
 */
void jdk_internal_misc_Unsafe_addressSize0_90I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 8);
}

void jdk_internal_misc_Unsafe_isBigEndian0_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 1);
}

/**
 * Returns true if this platform is capable of performing
 * accesses at addresses which are not aligned for the type of the
 * primitive type being accessed, false otherwise.
 */
void jdk_internal_misc_Unsafe_unalignedAccess0_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 1);
}

void jdk_internal_misc_Unsafe_objectFieldOffset1_9Ljava_lang_Class1Ljava_lang_String10J(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_ref_localvar(frame, 1);
    Object *string = get_ref_localvar(frame, 2);
    char *name = get_str_field_value_by_object(string);
    FieldInfo *field = get_field_by_name(object->raw_class, name);
    free(name);
    push_long(frame->operand_stack, field->offset);

//    Object *object = get_ref_localvar(frame, 1);
//    Object *string = get_ref_localvar(frame, 2);
//    char *name = get_str_field_value_by_object(string);
//    FieldInfo *field = get_field_by_name(object->raw_class, name);
//    free(name);
//    push_long(frame->operand_stack, offsetof(Object, fields) + field->offset * sizeof(char*));
}

void jdk_internal_misc_Unsafe_storeFence_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO src/hotspot/share/prims/unsafe.cpp call OrderAccess::release();
}

void jdk_internal_misc_Unsafe_compareAndSetInt_9Ljava_lang_Object1JII0Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *ref = get_ref_localvar(frame, 1);
    u8 offset = get_long_localvar(frame, 2);
    Slot *slot = &ref->fields[offset];
    u8 e = get_localvar(frame, 4);
    u8 x = get_localvar(frame, 5);
//    if (e == slot->value) {
        slot->value = x;
        push_int(frame->operand_stack, 1);
//    } else {
//        push_int(frame->operand_stack, 0);
//    }
}

void jdk_internal_misc_Unsafe_compareAndSetObject_9Ljava_lang_Object1JLjava_lang_Object1Ljava_lang_Object10Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    u8 offset = get_long_localvar(frame, 2);
    Object *e = get_ref_localvar(frame, 4);
    Object *x = get_ref_localvar(frame, 5);
    void *object = get_ref_localvar(frame, 1);
    if (is_array(object)) {
        long *p = object + offset;
        *p = x;
    } else {
        Object *o = object;
        o->fields[offset].object_value = x;
    }
    push_int(frame->operand_stack, 1);

//    if (e == x) {
//        push_int(frame->operand_stack, 1);
//    } else {
//        push_int(frame->operand_stack, 0);
//    }
}

void jdk_internal_misc_Unsafe_compareAndSetLong_9Ljava_lang_Object1JJJ0Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    u8 offset = get_long_localvar(frame, 2);
    u8 e = get_localvar(frame, 4);
    u8 x = get_localvar(frame, 5);
    Object *object = get_ref_localvar(frame, 1);
    object->fields[offset].value = x;
    push_int(frame->operand_stack, 1);
//    Slot *slot = NULL;
//    if(is_array(get_ref_localvar(frame, 1))) {
//        Array *ref = get_ref_localvar(frame, 1);
//        slot = &ref->objects[0]->fields[offset];
//    } else {
//        Object *ref = get_ref_localvar(frame, 1);
//        slot = &ref->fields[offset];
//    }
//    if (e == slot->value) {
//        slot->value = x;
//        push_int(frame->operand_stack, 1);
//    } else {
//        push_int(frame->operand_stack, 0);
//    }
}

void jdk_internal_misc_Unsafe_getObjectVolatile_9Ljava_lang_Object1J0Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
//    u8 offset = get_long_localvar(frame, 2);
//    offset = 32;
    void *object = get_ref_localvar(frame, 1);
    u8 offset = get_long_localvar(frame, 2);
    Object **ref = object + offset;
    //need fix, why ref's address is poito &class
    push_object(frame->operand_stack, *ref);
//    Slot *slot = NULL;
//    if(is_array(get_ref_localvar(frame, 1))) {
//        Array *ref = get_ref_localvar(frame, 1);
//        if (NULL == ref->objects[0]) {
//            push_slot(frame->operand_stack, NULL_SLOT);
//            return;
//        } else {
//            slot = &ref->objects[0]->fields[offset];
//        }
//    } else {
//        Object *ref = get_ref_localvar(frame, 1);
//        slot = &ref->fields[offset];
//    }
//    push_slot(frame->operand_stack, slot);
}

/**
 * Stores a reference value into a given Java variable, with
 * volatile store semantics. Otherwise identical to {@link #putObject(Object, long, Object)}
 */

/**
     * #putObject
     * Stores a reference value into a given Java variable.
     * <p>
     * Unless the reference {@code x} being stored is either null
     * or matches the field type, the results are undefined.
     * If the reference {@code o} is non-null, card marks or
     * other store barriers for that object (if the VM requires them)
     * are updated.
     * @see #putInt(Object, long, int)
     */
void jdk_internal_misc_Unsafe_putObjectVolatile_9Ljava_lang_Object1JLjava_lang_Object10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
//    void *object = get_ref_localvar(frame, 1);
//    u8 offset = get_long_localvar(frame, 2);
//    Object *value = get_ref_localvar(frame, 4);
//    long *p = object + offset;
//    *p = value;

    void *object = get_ref_localvar(frame, 1);
    u8 offset = get_long_localvar(frame, 2);
    Object *value = get_ref_localvar(frame, 4);
    if (is_array(object)) {
        long *obj = (object + offset);
        *obj = value;
    } else {
        Object *obj = object;
        obj->fields[offset].object_value = value;
    }
}

void jdk_internal_misc_Unsafe_getIntVolatile_9Ljava_lang_Object1J0I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_ref_localvar(frame, 1);
    u8 offset = get_long_localvar(frame, 2);
    push_int(frame->operand_stack, this->fields[offset].value);
}

void jdk_internal_misc_Unsafe_ensureClassInitialized0_9Ljava_lang_Class10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *class = get_ref_localvar(frame, 1);
    if (NULL == class) {
        printf_err("jdk_internal_misc_Unsafe_ensureClassInitialized0_9Ljava_lang_Class10V: clazz must not be NULL");
        exit(-1);
    }
    if (!class_is_not_init(class->raw_class)) {
        init_class(thread, heap, class->raw_class);
    }
}

void jdk_internal_misc_Unsafe_allocateMemory0_9J0J(Thread *thread, SerialHeap *heap, Frame *frame)
{
    long bytes = get_long_localvar(frame, 1);
    long addr = (long) malloc(bytes);
    push_long(frame->operand_stack, addr);
}


/**
 * Fetches a reference value from a given Java variable.
 * @see #getInt(Object, long)
 * public native Object getObject(Object o, long offset);
 */
void jdk_internal_misc_Unsafe_getObject_9Ljava_lang_Object1J0Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_ref_localvar(frame, 1);
    long offset = get_long_localvar(frame, 2);
    push_object(frame->operand_stack, object->fields[offset].object_value);

    //    Slot* slot = (Slot*)(object + offset);
//    push_object(frame->operand_stack, slot->object_value);
}

void jdk_internal_misc_Unsafe_putObject_9Ljava_lang_Object1JLjava_lang_Object10V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_ref_localvar(frame, 1);
    u8 offset = get_long_localvar(frame, 2);
    Object *value = get_ref_localvar(frame, 4);
    object->fields[offset].object_value = value;

//    void *object = get_ref_localvar(frame, 1);
//    u8 offset = get_long_localvar(frame, 2);
//    void *value = get_ref_localvar(frame, 4);
//    long *p = object + offset;
//    *p = value;
}

/**
 * Sets all bytes in a given block of memory to a copy of another
 * block.  This provides a <em>single-register</em> addressing mode,
 * as discussed in {@link #getInt(Object,long)}.
 *
 * Equivalent to {@code copyMemory(null, srcAddress, null, destAddress, bytes)}.
 */
void jdk_internal_misc_Unsafe_copyMemory0_9Ljava_lang_Object1JLjava_lang_Object1JJ0V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    void *src_base = get_ref_localvar(frame, 1);
    long src_offset = get_long_localvar(frame, 2);
    void *dest_base = get_ref_localvar(frame, 4);
    long dest_offset = get_long_localvar(frame, 5);
    long size = get_long_localvar(frame, 7);
    void *from = index_oop_from_field_offset_long(src_base, src_offset);
    long *to = index_oop_from_field_offset_long(dest_base, dest_offset);
    uintptr_t bits = (uintptr_t) from | (uintptr_t) to | (uintptr_t) size;

    if (bits % sizeof(long) == 0) {
        conjoint_jlongs_atomic((const long*) from, (long*) to, size / sizeof(long));
    } else if (bits % sizeof(int) == 0) {
        conjoint_jints_atomic((const int*) from, (int*) to, size / sizeof(int));
    } else if (bits % sizeof(short) == 0) {
        conjoint_jshorts_atomic((const short*) from, (short*) to, size / sizeof(short));
    } else {
        (void)memmove((void*)to, (const void*)from, size);
    }
}

void jdk_internal_misc_Unsafe_putByte_9Ljava_lang_Object1JB0V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    void *object = get_ref_localvar(frame, 1);
    long offset = get_long_localvar(frame, 2);
    char byte = get_localvar(frame, 4);
    char *p = object + offset;
    *p = byte;
}

void conjoint_jshorts_atomic(short* from, short* to, size_t count) {
    if (from > to) {
        short *end = from + count;
        while (from < end)
            *(to++) = *(from++);
    }
    else if (from < to) {
        short *end = from;
        from += count - 1;
        to   += count - 1;
        while (from >= end)
            *(to--) = *(from--);
    }
}
void conjoint_jints_atomic(int* from, int* to, size_t count) {
    if (from > to) {
        int *end = from + count;
        while (from < end)
            *(to++) = *(from++);
    }
    else if (from < to) {
        int *end = from;
        from += count - 1;
        to   += count - 1;
        while (from >= end)
            *(to--) = *(from--);
    }
}
void conjoint_jlongs_atomic(long* from, long* to, size_t count) {
    if (from > to) {
        long *end = from + count;
        while (from < end)
            atomic_copy64(from++, to++);
    }
    else if (from < to) {
        long *end = from;
        from += count - 1;
        to   += count - 1;
        while (from >= end)
            atomic_copy64(from--, to--);
    }
}

void atomic_copy64(const long *from, long *to)
{
    *(long *) to = *(const long *) from;
}

void *index_oop_from_field_offset_long(void *p, long field_offset)
{
    if (sizeof(char*) == sizeof(int)) {   // (this constant folds!)
        return (char*)p + (int)field_offset;
    } else {
        return (char*)p + field_offset;
    }
}

void jdk_internal_misc_Unsafe_getInt_9Ljava_lang_Object1J0I(Thread *thread, SerialHeap *heap, Frame *frame)
{
    void *object = get_ref_localvar(frame, 1);
    long offset = get_long_localvar(frame, 2);
    int value;
    if (NULL == object || is_array(object)) {
        value = *(int*)(object + offset);
    } else {
        Object *obj = object;
        value = obj->fields[offset].value;
    }
    push_int(frame->operand_stack, value);
}