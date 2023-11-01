#include "MemoryBlock.hpp"

#include <iostream>
#include <cassert>

int main()
{
    std::size_t allocationSize = 100;
    auto allocationForData = MemoryBlock::allocate(100);

    auto memoryHeader = MemoryBlock::getBlock(allocationForData);

    assert(memoryHeader->size() == ((allocationSize + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1)));
    assert(not memoryHeader->free());

    MemoryBlock::free(allocationForData);
    assert(memoryHeader->free());
}
