//
// Created by wangzhanzhi on 2020/8/15.
//

#include "AccessController.h"

void java_security_AccessController_getStackAccessControlContext_90Ljava_security_AccessControlContext1(Thread *thread, SerialHeap *heap, Frame *frame)
{
    //TODO in jdk11 source "src/java.base/share/native/libjava/AccessController.c" JVM_GetStackAccessControlContext
   push_slot(frame->operand_stack, NULL_SLOT);
}

/**
  * Performs the specified {@code PrivilegedAction} with privileges
  * enabled. The action is performed with <i>all</i> of the permissions
  * possessed by the caller's protection domain.
  *
  * <p> If the action's {@code run} method throws an (unchecked)
  * exception, it will propagate through this method.
  *
  * <p> Note that any DomainCombiner associated with the current
  * AccessControlContext will be ignored while the action is performed.
  *
  * @param <T> the type of the value returned by the PrivilegedAction's
  *                  {@code run} method.
  *
  * @param action the action to be performed.
  *
  * @return the value returned by the action's {@code run} method.
  *
  * @exception NullPointerException if the action is {@code null}
  *
  * @see #doPrivileged(PrivilegedAction,AccessControlContext)
  * @see #doPrivileged(PrivilegedExceptionAction)
  * @see #doPrivilegedWithCombiner(PrivilegedAction)
  * @see java.security.DomainCombiner
  */
void java_security_AccessController_doPrivileged_9Ljava_security_PrivilegedAction10Ljava_lang_Object1(Thread *thread, SerialHeap *heap, Frame *frame)
{
   Object *action = get_ref_localvar(frame, 0);
   ClassFile *class = action->raw_class;

   push_object(frame->operand_stack, action);
   MethodInfo *method = find_method_with_desc(thread, heap, class, "run", "()Ljava/lang/Object;");
   create_vm_frame_by_method_add_params_plus1(thread, class, frame, method, get_method_code(class->constant_pool, *method));

//    Stack *stack = create_unlimit_stack();
//    push_object(stack, action);
//    single_invoke(heap, class, "run", "()Ljava/lang/Object;", stack);
}