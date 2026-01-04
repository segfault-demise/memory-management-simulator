#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <vector>
#include <cstddef>

using namespace std;

enum AllocationStrategy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

struct MemoryBlock {
    size_t start;
    size_t size;
    bool isFree;

    MemoryBlock(size_t s, size_t sz, bool free)
        : start(s), size(sz), isFree(free) {}
};

class PhysicalMemory {
private:
    size_t totalSize;
    AllocationStrategy strategy;

    vector<MemoryBlock> blocks;

    size_t totalRequests;
    size_t successfulRequests;

public:
    PhysicalMemory(size_t size, AllocationStrategy strat);

    int allocate(size_t size);
    void freeBlock(size_t startAddress);

    void dumpMemory() const;

    size_t getTotalFreeMemory() const;
    size_t getLargestFreeBlock() const;

    double getExternalFragmentation() const;
    double getMemoryUtilization() const;
    double getAllocationSuccessRate() const;
};

#endif
