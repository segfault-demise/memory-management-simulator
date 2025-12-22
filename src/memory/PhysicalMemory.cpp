#include "memory/PhysicalMemory.h"
#include <iostream>

// Constructor: runs when we create a PhysicalMemory object
PhysicalMemory::PhysicalMemory(size_t size) {
    // Store total memory size
    totalSize = size;

    // At the start, all memory is free
    // One block starting at address 0, of full size
    MemoryBlock initialBlock(0, size, true);

    // Add this block to the list of blocks
    blocks.push_back(initialBlock);
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
