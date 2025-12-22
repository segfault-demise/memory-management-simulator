#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <vector>
#include "MemoryBlock.h"

class PhysicalMemory {
private:
    size_t totalSize;
    std::vector<MemoryBlock> blocks;

public:
    explicit PhysicalMemory(size_t size);

    void dumpMemory() const;
};

#endif
