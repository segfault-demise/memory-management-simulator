#include "vmm/VirtualMemoryManager.h"
#include <iostream>

VirtualMemoryManager::VirtualMemoryManager(int pageSize,
                                           int numVirtualPages,
                                           int numPhysicalFrames)
{
    this->pageSize = pageSize;
    this->numVirtualPages = numVirtualPages;
    this->numPhysicalFrames = numPhysicalFrames;

    pageTable.resize(numVirtualPages);
    for (int i = 0; i < numVirtualPages; i++) {
        pageTable[i].valid = false;
    }

    frameToPage.resize(numPhysicalFrames, -1);

    pageFaults = 0;
    memoryAccesses = 0;
}

void VirtualMemoryManager::handlePageFault(int pageNumber) {

    pageFaults++;

    int frame = -1;

    // Case 1: Free frame exists
    for (int i = 0; i < numPhysicalFrames; i++) {
        if (frameToPage[i] == -1) {
            frame = i;
            break;
        }
    }

    // Case 2: No free frame → evict LRU page
    if (frame == -1) {
        int victimPage = lruPages.back();
        lruPages.pop_back();

        frame = pageTable[victimPage].frameNumber;

        pageTable[victimPage].valid = false;
    }

    // Load new page into frame
    pageTable[pageNumber].frameNumber = frame;
    pageTable[pageNumber].valid = true;

    frameToPage[frame] = pageNumber;

    // Update LRU
    lruPages.push_front(pageNumber);
}

int VirtualMemoryManager::translate(int virtualAddress) {

    memoryAccesses++;

    int pageNumber = virtualAddress / pageSize;
    int offset = virtualAddress % pageSize;

    if (!pageTable[pageNumber].valid) {
        handlePageFault(pageNumber);
    }

    // Update LRU (page was just used)
    lruPages.remove(pageNumber);
    lruPages.push_front(pageNumber);

    int frame = pageTable[pageNumber].frameNumber;
    int physicalAddress = frame * pageSize + offset;

    return physicalAddress;
}

int VirtualMemoryManager::getPageFaults() const {
    return pageFaults;
}

int VirtualMemoryManager::getMemoryAccesses() const {
    return memoryAccesses;
}

double VirtualMemoryManager::getPageFaultRate() const {
    if (memoryAccesses == 0) return 0.0;
    return (double)pageFaults / memoryAccesses;
}
