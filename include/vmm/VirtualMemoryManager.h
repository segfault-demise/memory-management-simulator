#ifndef VIRTUAL_MEMORY_MANAGER_H
#define VIRTUAL_MEMORY_MANAGER_H

#include <vector>
#include <list>

using namespace std;

struct PageTableEntry {
    bool valid;
    int frameNumber;

    PageTableEntry() {
        valid = false;
        frameNumber = -1;
    }
};

class VirtualMemoryManager {
private:
    int pageSize;
    int numVirtualPages;
    int numPhysicalFrames;

    vector<PageTableEntry> pageTable;
    vector<int> frameToPage;

    list<int> lruPages;   // MRU at front, LRU at back

    int pageFaults;
    int memoryAccesses;

    void handlePageFault(int pageNumber);

public:
    VirtualMemoryManager(int pageSize,
                         int numVirtualPages,
                         int numPhysicalFrames);

    int translate(int virtualAddress);

    int getPageFaults() const;
    int getMemoryAccesses() const;
    double getPageFaultRate() const;
};

#endif
