#include "memory/PhysicalMemory.h"
#include <iostream>

// Constructor: runs when we create a PhysicalMemory object
PhysicalMemory::PhysicalMemory(size_t size, AllocationStrategy strat) {
    totalSize = size;
    strategy = strat;

    // Initially one big free block
    blocks.push_back(MemoryBlock(0, size, true));
}


// Prints the current memory layout
void PhysicalMemory::dumpMemory() const {
    std::cout << "Memory Layout:\n";

    // Go through each memory block
    for (const MemoryBlock& block : blocks) {

        std::cout << "[Start: " << block.start
                  << ", Size: " << block.size
                  << ", ";

        // Check whether block is free or allocated
        if (block.isFree) {
            std::cout << "Free";
        } else {
            std::cout << "Allocated";
        }

        std::cout << "]\n";
    }
}

//Allocate memory

int PhysicalMemory::allocate(size_t size) {

    int required_index = -1;

    // FIRST FIT
    if (strategy == FIRST_FIT) {
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].isFree && blocks[i].size >= size) {
                required_index = i;
                break;
            }
        }
    }

    // BEST FIT
    else if (strategy == BEST_FIT) {
        size_t smallestSize = SIZE_MAX;

        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].isFree && blocks[i].size >= size) {
                if (blocks[i].size < smallestSize) {
                    smallestSize = blocks[i].size;
                    required_index = i;
                }
            }
        }
    }

    // WORST FIT
    else if (strategy == WORST_FIT) {
        size_t largestSize = 0;

        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].isFree && blocks[i].size >= size) {
                if (blocks[i].size > largestSize) {
                    largestSize = blocks[i].size;
                    required_index = i;
                }
            }
        }
    }

    // If no suitable block found
    if (required_index == -1) {
        return -1;
    }

    // Allocation & Splitting 
    size_t startAddress = blocks[required_index].start;
    size_t remainingSize = blocks[required_index].size - size;

    blocks[required_index].size = size;
    blocks[required_index].isFree = false;

    if (remainingSize > 0) {
        MemoryBlock newBlock(startAddress + size,remainingSize,true);

        blocks.insert(blocks.begin() + required_index + 1, newBlock);
    }

    return (int)startAddress;
}

// Free allocated memory
void PhysicalMemory::freeBlock(size_t startAddress) {

    // Find the block with this start address
    for (size_t i = 0; i < blocks.size(); i++) {

        if (blocks[i].start == startAddress) {

            // Mark block as free
            blocks[i].isFree = true;

            // Merge with next block if free
            if (i + 1 < blocks.size() && blocks[i + 1].isFree) {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }

            // Merge with previous block if free
            if (i > 0 && blocks[i - 1].isFree) {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
            }

            return;
        }
    }
}
