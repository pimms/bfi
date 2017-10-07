#include "program.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

bool validate(struct program *prog)
{
    int stack = 0;

    for (int i=0; i<prog->len; i++) {
        if (prog->src[i] == '[') {
            stack++;
        } else if (prog->src[i] == ']') {
            stack--;

            if (stack < 0) {
                fprintf(stderr, "Unmatched ']' character\n");
                return false;
            }
        }
    }

    if (stack != 0) {
        fprintf(stderr, "There are %d unmatched square boys", stack);
        return false;
    }

    return true;
}

struct program* load_program(const char *path)
{
    const char *allowed = "+-<>[].,";
    int nallows = strlen(allowed);

    FILE *fh = fopen(path, "r");
    if (!fh) {
        fprintf(stderr, "Failed to open file '%s'", path);
        return NULL;
    }

    struct program *prog = (struct program*)malloc(sizeof(struct program));
    prog->len = 0;
    prog->src = NULL;

    char input = 0;
    int allocated = 0;
    int read = 0;

    do {
        input = fgetc(fh);

        for (int i=0; i<nallows; i++) {
            if (allowed[i] == input) {
                read++;

                if (read >= allocated) {
                    prog->len += 128;
                    allocated = prog->len;
                    printf("Reallocating to %zd bytes\n", prog->len);
                    prog->src = (uint8_t*)realloc(prog->src, prog->len);
                }

                prog->src[read-1] = (uint8_t)input;
                break;
            }
        }
    } while (input != EOF);
    fclose(fh);

    prog->len = read;

    if (!validate(prog)) {
        deallocate_program(&prog);
        return NULL;
    }

    return prog;
}

void deallocate_program(struct program **prog)
{
    free((*prog)->src);
    free(*prog);
    *prog = NULL;
}

int find_matching_brace(const struct program *p, int at)
{
    if (at >= p->len)
        return -1;
    if (p->src[at] != '[' && p->src[at] != ']')
        return -1;

    if (p->src[at] == '[') {
        int stack = 1;

        for (int i=at+1; i<p->len; i++) {
            if (p->src[i] == '[')
                stack++;
            if (p->src[i] == ']')
                stack--;

            if (stack == 0)
                return i;
        }

        return -1;
    } else {
        int stack = 1;

        for (int i=at-1; i>=0; i--) {
            if (p->src[i] == '[')
                stack--;
            if (p->src[i] == ']')
                stack++;

            if (stack == 0)
                return i;
        }

        return -1;
    }

    return -1;
}

