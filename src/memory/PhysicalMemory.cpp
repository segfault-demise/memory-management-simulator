#include "../../include/memory/PhysicalMemory.h"
#include <iostream>

using namespace std;

// Constructor
PhysicalMemory::PhysicalMemory(size_t size, AllocationStrategy strat) {
    totalSize = size;
    strategy = strat;
    totalRequests = 0;
    successfulRequests = 0;

    // Initially one large free block
    blocks.push_back(MemoryBlock(0, size, true));
}

// Print memory layout
void PhysicalMemory::dumpMemory() const {
    cout << "Memory Layout:\n";

    for (const MemoryBlock& block : blocks) {
        cout << "[Start: " << block.start << ", Size: " << block.size << ", "
             << (block.isFree ? "Free" : "Allocated") << "]\n";
    }
}

// Allocate memory
int PhysicalMemory::allocate(size_t size) {
    totalRequests++;
    int index = -1;

    // FIRST FIT
    if (strategy == FIRST_FIT) {
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].isFree && blocks[i].size >= size) {
                index = i;
                break;
            }
        }
    }

    // BEST FIT
    else if (strategy == BEST_FIT) {
        size_t bestSize = SIZE_MAX;
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].isFree && blocks[i].size >= size &&
                blocks[i].size < bestSize) {
                bestSize = blocks[i].size;
                index = i;
            }
        }
    }

    // WORST FIT
    else if (strategy == WORST_FIT) {
        size_t worstSize = 0;
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].isFree && blocks[i].size >= size &&
                blocks[i].size > worstSize) {
                worstSize = blocks[i].size;
                index = i;
            }
        }
    }

    // No suitable block
    if (index == -1) {
        return -1;
    }

    size_t startAddress = blocks[index].start;
    size_t remaining = blocks[index].size - size;

    // Allocate block
    blocks[index].size = size;
    blocks[index].isFree = false;

    // Split if space remains
    if (remaining > 0) {
        MemoryBlock newBlock(startAddress + size, remaining, true);
        blocks.insert(blocks.begin() + index + 1, newBlock);
    }

    successfulRequests++;
    return (int)startAddress;
}

// Free memory block
void PhysicalMemory::freeBlock(size_t startAddress) {
    for (size_t i = 0; i < blocks.size(); i++) {
        if (blocks[i].start == startAddress) {
            blocks[i].isFree = true;

            // Merge with next
            if (i + 1 < blocks.size() && blocks[i + 1].isFree) {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }

            // Merge with previous
            if (i > 0 && blocks[i - 1].isFree) {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
            }
            return;
        }
    }
}

// Total free memory
size_t PhysicalMemory::getTotalFreeMemory() const {
    size_t freeMem = 0;
    for (const MemoryBlock& block : blocks) {
        if (block.isFree) {
            freeMem += block.size;
        }
    }
    return freeMem;
}

// Largest free block
size_t PhysicalMemory::getLargestFreeBlock() const {
    size_t largest = 0;
    for (const MemoryBlock& block : blocks) {
        if (block.isFree && block.size > largest) {
            largest = block.size;
        }
    }
    return largest;
}

// External fragmentation
double PhysicalMemory::getExternalFragmentation() const {
    size_t totalFree = getTotalFreeMemory();
    if (totalFree == 0)
        return 0.0;

    size_t largestFree = getLargestFreeBlock();
    return 1.0 - (double)largestFree / totalFree;
}

// Memory utilization
double PhysicalMemory::getMemoryUtilization() const {
    size_t allocated = 0;
    for (const MemoryBlock& block : blocks) {
        if (!block.isFree) {
            allocated += block.size;
        }
    }
    return (double)allocated / totalSize;
}

// Allocation success rate
double PhysicalMemory::getAllocationSuccessRate() const {
    if (totalRequests == 0)
        return 0.0;
    return (double)successfulRequests / totalRequests;
}
