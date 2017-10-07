#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "program.h"


struct state
{
    int mptr;
    int iptr;
    uint8_t *mem;
    int size;
    const struct program *program;
};

void dealloc_state(struct state **state)
{
    free((*state)->mem);
    free(*state);
    *state = NULL;
}

struct state* alloc_state(int size)
{
    struct state *state = (struct state*)malloc(sizeof(state));
    state->mptr = 0;
    state->iptr = 0;
    state->mem = (uint8_t*)malloc(sizeof(uint8_t) * size);
    state->size = size;
    state->program = NULL;
    return state;
}

void resize_memory(struct state *state, int nsize)
{
    printf("[Resizing memory to %d bytes]\n", nsize);
    state->size = nsize;
    state->mem = (uint8_t*)realloc(state->mem, nsize);
}


void execute(struct state *state)
{
    while (state->iptr != (int)state->program->len) {
        uint8_t instr = state->program->src[state->iptr];
        printf("[instr %c]\n", instr);

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
                if (!state->mem[state->mptr])
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

    for (int i=0; i<prog->len; i++) {
        printf("%c", prog->src[i]);
    }

    struct state *state = alloc_state(128);
    state->program = prog;

    execute(state);

    deallocate_program(&prog);
    dealloc_state(&state);

    return 0;
}
