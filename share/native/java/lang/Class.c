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
    push_slot(frame->operand_stack, create_str_slot_set_str(thread, heap, this->raw_class->standard_class_name));
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
    }
    push_object(frame->operand_stack, class->class_object);
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
    //TODO
    Object *this = get_localvar_this(frame);
    int public_only = get_localvar(frame, 1);
    ClassFile *array_class = load_class(thread, heap, "[Ljava/lang/reflect/Method");
    ClassFile *class_class = load_class(thread, heap, "java/lang/Class");
    if (is_primitive_desc(this->raw_class->class_name)) {
        push_object(frame->operand_stack, malloc_array(thread, heap, array_class, 0));
    } else {
        Stack *stack = create_stack(this->raw_class->methods_count);
        ClassFile *method_class = load_class(thread, heap, "java/lang/reflect/Method");
        if (class_is_not_init(method_class)) {
            ensure_inited_class(thread, heap, method_class);
        }
        for (int i = 0; i < this->raw_class->methods_count; i++) {
            if (strcmp(this->raw_class->methods[i].name, "<init>") == 0 || strcmp(this->raw_class->methods[i].name, "<clinit>") == 0) continue;
            if (public_only && !is_public(this->raw_class->methods[i].access_flags)) continue;
            Object *method_object = malloc_object(thread, heap, method_class);
            Stack *params = create_stack(12);
            char **param_types_name = parse_param_types(thread, heap, this->raw_class->methods[i].desc, this->raw_class->methods[i].real_params_count);
            Array *parameter_types = malloc_array(thread, heap, class_class, this->raw_class->methods[i].real_params_count);
            if (NULL != param_types_name) {
                for (int j = 0; j < this->raw_class->methods[i].real_params_count; j++) {
                    parameter_types->objects[j] = load_class(thread, heap, param_types_name[j])->class_object;
                }
            }
            push_object(params, method_object);//this

            push_object(params, this->raw_class->class_object);//declaringClass
            push_slot(params, create_str_slot_set_str(thread, heap, this->raw_class->methods[i].name));//name
            push_object(params, parameter_types);//parameterTypes
            push_object(params, load_class(thread, heap, return_type_name(this->raw_class->methods[i].desc))->class_object);//returnType
            push_slot(params, NULL_SLOT);//checkedExceptions
            push_int(params, this->raw_class->methods[i].access_flags);//modifiers
            push_int(params, i);//slot
            push_slot(params, create_str_slot_set_str(thread, heap, this->raw_class->methods[i].signature));//signature
            push_slot(params, NULL_SLOT);//annotations
            push_slot(params, NULL_SLOT);//parameterAnnotations
            push_slot(params, NULL_SLOT);//annotationDefault
            single_invoke(thread, heap, method_class, "<init>", "(Ljava/lang/Class;Ljava/lang/String;[Ljava/lang/Class;Ljava/lang/Class;[Ljava/lang/Class;IILjava/lang/String;[B[B[B)V", params, NULL);
            push_object(stack, method_object);
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

void java_lang_Class_getSuperclass_90Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    ClassFile *super_class = this->raw_class->super_class;
    if (NULL != super_class && NULL != super_class->class_object) {
        push_object(frame->operand_stack, super_class->class_object);
    } else {
        push_slot(frame->operand_stack, NULL_SLOT);
    };
}

void java_lang_Class_getInterfaces0_90sLjava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    Array *array = malloc_array(thread, heap, load_primitive_class(thread, heap, "[Ljava/lang/Class"), this->raw_class->interfaces_count);
    for (int i = 0; i < this->raw_class->interfaces_count; i++) {
        ClassFile *interface = this->raw_class->interfaces_info[i].class;
        ensure_inited_class(thread, heap, interface);
        array->objects[i] = interface->class_object;
    }
    push_object(frame->operand_stack, array);
}

void java_lang_Class_getConstantPool_90Ljdk_internal_reflect_ConstantPool1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    if (is_primitive_desc(this->raw_class->class_name)) {
        push_slot(frame->operand_stack, NULL_SLOT);
    } else {
        ClassFile *pool_class = load_class(thread, heap, "jdk/internal/reflect/ConstantPool");
        ensure_inited_class(thread, heap, pool_class);
        push_object(frame->operand_stack, pool_class->class_object);
    }
}

/**
 * Determines if the class or interface represented by this
 * {@code Class} object is either the same as, or is a superclass or
 * superinterface of, the class or interface represented by the specified
 * {@code Class} parameter. It returns {@code true} if so;
 * otherwise it returns {@code false}. If this {@code Class}
 * object represents a primitive type, this method returns
 * {@code true} if the specified {@code Class} parameter is
 * exactly this {@code Class} object; otherwise it returns
 * {@code false}.
 *
 * <p> Specifically, this method tests whether the type represented by the
 * specified {@code Class} parameter can be converted to the type
 * represented by this {@code Class} object via an identity conversion
 * or via a widening reference conversion. See <em>The Java Language
 * Specification</em>, sections 5.1.1 and 5.1.4 , for details.
 *
 * @param cls the {@code Class} object to be checked
 * @return the {@code boolean} value indicating whether objects of the
 * type {@code cls} can be assigned to objects of this class
 * @exception NullPointerException if the specified Class parameter is
 *            null.
 * @since 1.1
 */
void java_lang_Class_isAssignableFrom_9Ljava_lang_Class10Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    Object *cls = get_ref_localvar(frame, 1);
    if (this->class == cls->raw_class || is_parent(this->raw_class, cls->raw_class) || is_instance_of(this->raw_class, cls->raw_class)) {
        push_int(frame->operand_stack, 1);
    } else {
        push_int(frame->operand_stack, 0);
    }
}

void java_lang_Class_isInterface_90Z(Thread *thread, SerialHeap *heap, Frame *frame)
{
    Object *this = get_localvar_this(frame);
    push_int(frame->operand_stack, is_interface(this->raw_class));
}

void java_lang_Class_getEnclosingMethod0_90sLjava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    Object *this = get_localvar_this(frame);
    if (is_full_primitive_desc(this->raw_class->class_name)) {
        push_slot(frame->operand_stack, NULL_SLOT);
    } else {
        push_slot(frame->operand_stack, NULL_SLOT);
    }
}

void java_lang_Class_getDeclaringClass0_90Ljava_lang_Class1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO
    Object *this = get_localvar_this(frame);
    if (is_full_primitive_desc(this->raw_class->class_name) || strcmp(this->class->class_name, "java/lang/Class") != 0) {
        push_slot(frame->operand_stack, NULL_SLOT);
    } else {
        push_slot(frame->operand_stack, NULL_SLOT);
    }
}