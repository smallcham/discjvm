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
    ImageFile *image = find_image(image_path);
    if (NULL != image) {
        Stack *params = create_stack(3);
        push_long(params, (u8) image->_index_data);
        push_int(params, image->_file_size);
        Object *byte_buffer = new_object_by_desc(thread, heap, frame, NULL, "java/nio/DirectByteBuffer", "(JI)V", params);
        push_object(frame->operand_stack, byte_buffer);
    } else {
        push_slot(frame->operand_stack, NULL_SLOT);
    }
}