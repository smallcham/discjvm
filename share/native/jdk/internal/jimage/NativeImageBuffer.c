//
// Created by wangzhanzhi on 2020/10/10.
//

#include "NativeImageBuffer.h"

/**
 * @implNote This class needs to maintain JDK 8 source compatibility.
 *
 * It is used internally in the JDK to implement jimage/jrtfs access,
 * but also compiled and delivered as part of the jrtfs.jar to support access
 * to the jimage file provided by the shipped JDK by tools running on JDK 8.
 */

void jdk_internal_jimage_NativeImageBuffer_getNativeMap_9Ljava_lang_String10Ljava_nio_ByteBuffer1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    char *image_path = get_str_field_value_by_object(get_ref_localvar(frame, 0));
    ImageFile *image = read_image(image_path);
    if (NULL != image) {
        ClassFile *class = load_class(thread, heap, "java/nio/DirectByteBuffer");
        if (class_is_not_init(class)) {
            Thread *new_thread = create_thread_with_jthread(VM_STACK_SIZE, C_STACK_SIZE, thread->jthread);
            new_thread->pthread = thread->pthread;
            clinit_class_and_exec(new_thread, heap, class);
        }
        Object *byte_buffer = malloc_object(thread, heap, class);
        put_field_by_name_and_desc(byte_buffer, "address", "J", create_slot_set_value((u8) image->_index_data));
        put_field_by_name_and_desc(byte_buffer, "capacity", "I", create_slot_set_value(image->_file_size));
        push_object(frame->operand_stack, byte_buffer);
    } else {
        push_slot(frame->operand_stack, NULL_SLOT);
    }
}