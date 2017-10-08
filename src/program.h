#ifndef __BFI_PROGRAM_H_
#define __BFI_PROGRAM_H_

#include <stdint.h>
#include <stdlib.h>

struct program
{
    uint8_t *src;
    int len;
};

struct program* load_program(const char *path);
void deallocate_program(struct program *prog);

int find_matching_brace(const struct program *p, int at);

#endif /* __BFI_PROGRAM_H_ */
