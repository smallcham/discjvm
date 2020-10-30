#include <zconf.h>
#include "runtime/bootstrap.h"

int main(int argc, char *argv[]) {
    char buf[101];
    char path[200];
    getcwd(buf, sizeof(buf));

    int log_level = LOG_INFO;
    int param_check = 0;
    int only_show = 0;

    if (argc == 1) {
        print_help();
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--version") == 0) {
            print_version();
            return 0;
        }
        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }
        if (strcmp(argv[i], "--debug") == 0) {
            log_level = LOG_DEBUG;
        }
        if (!str_start_with(argv[i], "-")) {
            param_check = 1;
            if (argv[i][0] == '/') {
                if (str_end_with(argv[i], ".class")) {
                    sprintf(path, "%s", argv[i]);
                } else {
                    sprintf(path, "%s.class", argv[i]);
                }
            } else {
                if (str_end_with(argv[i], ".class")) {
                    sprintf(path, "%s/%s", buf, argv[i]);
                } else {
                    sprintf(path, "%s/%s.class", buf, argv[i]);
                }
            }
        }
        if (strcmp(argv[i], "--show-class") == 0) {
            only_show = 1;
        }
    }
    if (!param_check) {
        printf_err("缺少主类参数");
        return 0;
    }
    if (only_show) {
        print_class_info(path);
        return 0;
    }
    format_and_set_root_path(path);
    start_vm(path, log_level);
    printf_succ("\t\t\t************RUN SUCCESS!**************");
    return 0;
}