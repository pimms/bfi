#ifndef __BFI_STATE_H_
#define __BFI_STATE_H_

#include <stdint.h>

struct state
{
    int mptr;
    uint8_t *mem;
    int size;

    int iptr;
    const struct program *program;
};

void dealloc_state(struct state *state);

struct state* alloc_state(int size);

void resize_memory(struct state *state, int nsize);


#endif /* __BFI_STATE_H_ */
