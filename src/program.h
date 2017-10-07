#ifndef __BFI_LOAD_H_
#define __BFI_LOAD_H_

#include <stdint.h>
#include <stdlib.h>

struct program
{
    uint8_t *src;
    int len;
};

struct program* load_program(const char *path);
void deallocate_program(struct program **prog);

#endif /* __BFI_LOAD_H_ */
