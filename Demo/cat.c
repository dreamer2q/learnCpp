#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define CMP(a, op, b) (strcmp(a, b) op 0)

int show_line = 0;
void do_putline(char* buf) {
    static unsigned long num_line = 1;
    if (show_line) {
        printf("%6d  ", num_line++);
    }
    fputs(buf, stdout);
}

void do_output(FILE* in) {
    char buf[0xFF];
    while (1) {
        fgets(buf, sizeof(buf), in);
        if (ferror(in)) {
            perror("Read file");
            break;
        }
        if (feof(in)) {
            break;
        }
        do_putline(buf);
    }
}

const char* my_sprintf(const char* fmt, ...) {
    static char buf[0xFF];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    return buf;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        do_output(stdin);
    } else {
        for (int i = 1; i < argc; i++) {
            if (!show_line && CMP(argv[i], ==, "-n")) {
                show_line = 1;
                continue;
            }
            FILE* in;
            if (CMP(argv[i], ==, "-")) {
                in = stdin;
            } else {
                in = fopen(argv[i], "r");
                if (in == NULL) {
                    perror(my_sprintf("Open %s", argv[i]));
                    continue;
                }
            }
            do_output(in);
            fclose(in);
        }
    }
    return 0;
}
