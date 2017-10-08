#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "program.h"
#include "state.h"
#include "debug.h"


void execute(struct state *state)
{
    while (state->iptr != (int)state->program->len) {
        uint8_t instr = state->program->src[state->iptr];

        //print_overview(state);

        switch (instr) {
            case '<': {
                state->mptr--;
                if (state->mptr < 0)
                    state->mptr = 0;
            } break;

            case '>': {
                state->mptr++;
                if (state->mptr >= state->size) {
                    resize_memory(state, state->size + 128);
                }
            } break;

            case '+': {
                state->mem[state->mptr]++;
            } break;

            case '-': {
                state->mem[state->mptr]--;
            } break;

            case '[': {
                if (!state->mem[state->mptr])
                    state->iptr = find_matching_brace(state->program, state->iptr);
            } break;

            case ']': {
                if (state->mem[state->mptr])
                    state->iptr = find_matching_brace(state->program, state->iptr);
            } break;

            case ',': {
                state->mem[state->mptr] = getchar();
            } break;

            case '.': {
                printf("%c", state->mem[state->mptr]);
            } break;
        }

        state->iptr++;
    }
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./%s [brainfuck file]\n", argv[0]);
        return 1;
    }

    struct program *prog = load_program(argv[1]);
    if (!prog) {
        fprintf(stderr, "Failed to open file '%s'\n", argv[1]);
    }

    if (!prog->len) {
        fprintf(stderr, "File '%s' is not a valid brainfuck file\n", argv[1]);
        return 1;
    }

    struct state *state = alloc_state(128);
    state->program = prog;

    execute(state);

    deallocate_program(prog);
    return 0;
}
