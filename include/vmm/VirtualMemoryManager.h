#ifndef VIRTUAL_MEMORY_MANAGER_H
#define VIRTUAL_MEMORY_MANAGER_H

#include <vector>
#include <list>

class VirtualMemoryManager {
private:
    int pageSize;
    int numVirtualPages;
    int numPhysicalFrames;

    // Page table
    struct PageTableEntry {
        int frameNumber;
        bool valid;
    };

    std::vector<PageTableEntry> pageTable;

    // Frame table
    std::vector<int> frameToPage;

    // LRU metadata (pages in RAM)
    std::list<int> lruPages;

    // Metrics
    int pageFaults;
    int memoryAccesses;

    void handlePageFault(int pageNumber);

public:
    VirtualMemoryManager(int pageSize,
                         int numVirtualPages,
                         int numPhysicalFrames);

    // Translate virtual → physical
    int translate(int virtualAddress);

    // Metrics
    int getPageFaults() const;
    int getMemoryAccesses() const;
    double getPageFaultRate() const;
};

#endif
