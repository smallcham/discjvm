//
// Created by wangzhanzhi on 2020/8/6.
//

#include "Class.h"

void java_lang_Class_registerNatives_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
}

void java_lang_Class_getPrimitiveClass_9Ljava_lang_String10Ljava_lang_Class(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_localvar_this(frame);
    ClassFile *class = load_primitive_class_by_str_array(thread, heap, get_str_field_array_value_by_object(object));
    push_object(frame->operand_stack, class->class_object);
}

void java_lang_Class_desiredAssertionStatus0_9Ljava_lang_Class10Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    push_int(frame->operand_stack, 0);
}

void java_lang_Class_isArray_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *object = get_localvar_this(frame);
    push_int(frame->operand_stack, is_array_by_name(object->raw_class->class_name));
}

void java_lang_Class_initClassName_90Ljava_lang_String1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    push_slot(frame->operand_stack, create_str_slot_set_str(thread, heap, this->raw_class->class_name));
}

void java_lang_Class_forName0_9Ljava_lang_String1ZLjava_lang_ClassLoader1Ljava_lang_Class10Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    char *name = get_str_field_value_by_object(get_ref_localvar(frame, 0));
    format_class_name(name);
    int initialize = get_localvar(frame, 1);
    ClassFile *class = load_class(thread, heap, name);
    if (initialize && class_is_not_init(class)) {

        ensure_inited_class(thread, heap, class);
        /*Thread *new_thread = create_thread_with_jthread(VM_STACK_SIZE, C_STACK_SIZE, thread->jthread);
        new_thread->pthread = thread->pthread;
        clinit_class_and_exec(new_thread, heap, class);*/

//        Frame *current = get_stack(thread->vm_stack);
//        push_slot(current->operand_stack, get_slot_localvar(frame, 0));
//        push_slot(current->operand_stack, get_slot_localvar(frame, 1));
//        push_slot(current->operand_stack, get_slot_localvar(frame, 2));
//        push_slot(current->operand_stack, get_slot_localvar(frame, 3));
//        back_pc(current, 3);
//        init_class(thread, heap, class);
    } else {
        push_object(frame->operand_stack, class->class_object);
    }
}

void java_lang_Class_isPrimitive_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    push_int(frame->operand_stack, is_full_primitive_desc(this->raw_class->class_name));
}

/**
 * Returns an array containing {@code Method} objects reflecting all the
 * declared methods of the class or interface represented by this {@code
 * Class} object, including public, protected, default (package)
 * access, and private methods, but excluding inherited methods.
 *
 * <p> If this {@code Class} object represents a type that has multiple
 * declared methods with the same name and parameter types, but different
 * return types, then the returned array has a {@code Method} object for
 * each such method.
 *
 * <p> If this {@code Class} object represents a type that has a class
 * initialization method {@code <clinit>}, then the returned array does
 * <em>not</em> have a corresponding {@code Method} object.
 *
 * <p> If this {@code Class} object represents a class or interface with no
 * declared methods, then the returned array has length 0.
 *
 * <p> If this {@code Class} object represents an array type, a primitive
 * type, or void, then the returned array has length 0.
 *
 * <p> The elements in the returned array are not sorted and are not in any
 * particular order.
 *
 * @return  the array of {@code Method} objects representing all the
 *          declared methods of this class
 * @throws  SecurityException
 *          If a security manager, <i>s</i>, is present and any of the
 *          following conditions is met:
 *
 *          <ul>
 *
 *          <li> the caller's class loader is not the same as the
 *          class loader of this class and invocation of
 *          {@link SecurityManager#checkPermission
 *          s.checkPermission} method with
 *          {@code RuntimePermission("accessDeclaredMembers")}
 *          denies access to the declared methods within this class
 *
 *          <li> the caller's class loader is not the same as or an
 *          ancestor of the class loader for the current class and
 *          invocation of {@link SecurityManager#checkPackageAccess
 *          s.checkPackageAccess()} denies access to the package
 *          of this class
 *
 *          </ul>
 *
 * @jls 8.2 Class Members
 * @jls 8.4 Method Declarations
 * @since 1.1
 */
void java_lang_Class_getDeclaredMethods0_9Z0sLjava_lang_reflect_Method1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    int public_only = get_localvar(frame, 1);
    ClassFile *array_class = load_class(thread, heap, "[Ljava/lang/reflect/Method");
    if (is_primitive_desc(this->class->class_name)) {
        push_object(frame->operand_stack, malloc_array(thread, heap, array_class, 0));
    } else {
        Stack *stack = create_stack(this->class->methods_count);
        ClassFile *class = load_class(thread, heap, "java/lang/reflect/Method");
        if (class_is_not_init(class)) {
            ensure_inited_class(thread, heap, class);
        }
        for (int i = 0; i < this->class->methods_count; i++) {
            if (strcmp(this->class->methods[i].name, "<init>") == 0 || strcmp(this->class->methods[i].name, "<clinit>") == 0) continue;
            if (public_only && !is_public(this->class->methods[i].access_flags)) continue;
            Object *object = malloc_object(thread, heap, class);
            Stack *params = create_stack(12);
            char **param_types_name = parse_param_types(thread, heap, this->class->methods[i].desc, this->class->methods[i].params_count);
            if (NULL == param_types_name) {

            } else {

            }
            push_object(params, object);//this
            push_object(params, this->class->class_object);//declaringClass
            push_slot(params, create_str_slot_set_str(thread, heap, this->class->methods[i].name));//name
            push_slot(params, NULL);//parameterTypes
            push_object(params, load_class(thread, heap, return_type_name(class->methods[i].desc))->class_object);//returnType
            push_slot(params, NULL);//checkedExceptions
            push_int(params, this->class->methods[i].access_flags);//modifiers
            push_int(params, i);//slot
            push_slot(params, NULL);//signature
            push_slot(params, NULL);//annotations
            push_slot(params, NULL);//parameterAnnotations
            push_slot(params, NULL);//annotationDefault
            single_invoke(heap, class, "<init>", "(Ljava/lang/Class;Ljava/lang/String;[Ljava/lang/Class;Ljava/lang/Class;[Ljava/lang/Class;IILjava/lang/String;[B[B[B)V", params);
        }
        if (stack->size > 0) {
            Array *array = malloc_array(thread, heap, array_class, stack->size);
            int size = stack->size;
            for (int i = 0; i < size; i++) {
                array->objects[i] = pop_slot(stack)->object_value;
            }
            push_object(frame->operand_stack, array);
        } else {
            push_object(frame->operand_stack, malloc_array(thread, heap, array_class, 0));
        }
    }
}