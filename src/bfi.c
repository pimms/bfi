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
    struct program *program;
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
    state->size = nsize;
    state->mem = (uint8_t*)realloc(state->mem, nsize);
}


void execute(struct state *state)
{
    while (state->iptr != (int)state->size) {

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

    return 0;
}
