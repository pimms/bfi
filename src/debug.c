#include "debug.h"

#include "state.h"
#include "program.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOV_UP "\033[A\r"
#define CL_END "\033[2K"

static void print_box_header(int width, const char *title)
{
    printf("+");
    int i=0;

    for (; i<2; i++)
        printf("-");

    for (int j=0; title && j < (int)strlen(title); j++, i++)
        printf("%c", title[j]);

    for (; i<width; i++)
        printf("-");
    printf("+\n");
}

static void print_program(const struct state *state, int term_width)
{
    const int num_cols = term_width / 5;


    const int src_off = state->iptr - num_cols / 2;

    print_box_header(term_width, "PROGRAM");
    printf("|");
    for (int i=0; i<num_cols; i++) {
        int index = i + src_off;
        if (index >= 0 && index < state->program->len) {
            printf(" %03d ", index);
        } else {
            printf("     ");
        }
    }
    printf("|\n");

    printf("|");
    for (int i=0; i<num_cols; i++) {
        int instr = i + src_off;
        if (instr >= 0 && instr < state->program->len) {
            printf("  %c  ", state->program->src[instr]);
        } else {
            printf("     ");
        }
    }
    printf("|\n");

    printf("|");
    for (int i=0; i<num_cols/2; i++)
        printf("     ");
    printf("  ^  ");
    for (int i=0; i<num_cols/2-1; i++)
        printf("     ");
    printf("|\n");
    print_box_header(term_width, NULL);
}

static void print_memory(const struct state *state, int term_width)
{
    const int num_cols = term_width / 4;

    const int mem_off = state->mptr - num_cols / 2;

    print_box_header(term_width, "MEMORY");

    printf("| numer  ");
    for (int i=2; i<num_cols; i++) {
        int addr = i + mem_off;
        if (addr >= 0 && addr < state->size) {
            printf("%03d ", (int)state->mem[addr]);
        } else {
            printf("    ");
        }
    }
    printf("|\n");

    printf("| char   ");
    for (int i=2; i<num_cols; i++) {
        int addr = i + mem_off;
        if (addr >= 0 && addr < state->size) {

            char ch = (char)state->mem[addr];
            if (!isgraph(ch))
                ch = '?';
            printf(" %c  ", ch);
        } else {
            printf("    ");
        }
    }
    printf("|\n");

    printf("| addr   ");
    for (int i=2; i<num_cols; i++) {
        int index = i + mem_off;
        if (index >= 0 && index < state->size) {
            printf("%03d ", index);
        } else {
            printf("    ");
        }
    }
    printf("|\n");


    printf("|");
    for (int i=0; i<num_cols/2; i++)
        printf("    ");
    printf(" ^  ");
    for (int i=0; i<num_cols/2-1; i++)
        printf("    ");
    printf("|\n");
    print_box_header(term_width, NULL);
}

void print_overview(const struct state *state)
{
    static int num_calls = 0;

    if (num_calls++ != 0) {
        // Clear existing output
        printf(MOV_UP CL_END
               MOV_UP CL_END
               MOV_UP CL_END
               MOV_UP CL_END
               MOV_UP CL_END

               MOV_UP CL_END
               MOV_UP CL_END
               MOV_UP CL_END
               MOV_UP CL_END
               MOV_UP CL_END
               MOV_UP CL_END
               MOV_UP CL_END

               "\r");
    }

    const int term_width = 80;
    print_program(state, term_width);
    print_memory(state, term_width);
    getchar();
}
