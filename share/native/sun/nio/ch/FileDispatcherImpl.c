//
// Created by wangzhanzhi on 2020/10/11.
//

#include "FileDispatcherImpl.h"

static int pre_close_fd = -1;

void sun_nio_ch_FileDispatcherImpl_init_90V(Thread *thread, SerialHeap *heap, Frame *frame)
{
    int sp[2];
    if (socketpair(PF_UNIX, SOCK_STREAM, 0, sp) < 0) {
        printf_err("socketpair failed");
        exit(-1);
    }
    pre_close_fd = sp[0];
    close(sp[1]);
}