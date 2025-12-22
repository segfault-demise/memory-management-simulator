#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include <cstddef>

struct MemoryBlock {
    size_t start;     // starting address
    size_t size;      // size of the block
    bool isFree;      // free or allocated

    MemoryBlock(size_t start, size_t size, bool isFree)
        : start(start), size(size), isFree(isFree) {}
};

#endif
