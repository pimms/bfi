#include "state.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void dealloc_state(struct state *state)
{
    free(state->mem);
    free(state);
}

struct state* alloc_state(int size)
{
    struct state *state = (struct state*)malloc(sizeof(struct state));
    memset(state, 0, sizeof(struct state));
    state->mem = (uint8_t*)malloc(sizeof(uint8_t) * size);
    memset(state->mem, 0, sizeof(uint8_t) * size);
    state->size = size;
    return state;
}

void resize_memory(struct state *state, int nsize)
{
    const int psize = state->size;

    state->size = nsize;
    state->mem = (uint8_t*)realloc(state->mem, nsize);

    if (nsize > psize) {
        const int diff = nsize - psize;
        memset(state->mem + psize, 0, sizeof(uint8_t) * diff);
    }
}
