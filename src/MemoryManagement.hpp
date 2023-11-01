#pragma once

#include <cstddef>
#include <unistd.h>

#include "MemoryBlock.hpp"
#include "FirstFit.hpp"
#include "NextFit.hpp"

class MemoryManagement
{
public:
    static void *allocate(const std::size_t size)
    {
        const auto alignedSize = align(size);

        if (auto mb = findBlock(alignedSize))
        {
            return getUserMemoryField(mb);
        }

        MemoryBlock *mb = requestFromOS(alignedSize);

        if (not mb)
        {
            return nullptr;
        }

        mb->size_ = alignedSize;
        mb->inUse_ = true;

        /*Update linked list*/
        if (not MemoryBlock::heapStart_)
        {
            MemoryBlock::heapStart_ = mb;
            MemoryBlock::nextFit_ = mb;
        }
        if (MemoryBlock::heapEnd_)
        {
            MemoryBlock::heapEnd_->next_ = (MemoryBlock *)mb; // sucpicious
        }
        MemoryBlock::heapEnd_ = mb;

        return getUserMemoryField(mb);
    }

    static void free(void *dataField)
    {
        auto *memoryBlock = getBlock(dataField);
        memoryBlock->inUse_ = false;
    }

    static MemoryBlock *getBlock(void *dataFiled)
    {

        return reinterpret_cast<MemoryBlock *>((static_cast<char *>(dataFiled) - sizeof(MemoryBlock)));
    }

private:
    static MemoryBlock *requestFromOS(const std::size_t size)
    {
        auto memoryBlock = (MemoryBlock *)sbrk(0);

        if (sbrk(size + sizeof(MemoryBlock)) == (void *)-1)
        {
            return nullptr;
        }

        return memoryBlock;
    }

    static std::size_t align(const std::size_t size)
    {
        return size + (sizeof(void *) - 1) & ~(sizeof(void *) - 1);
    }

    static MemoryBlock *findBlock(const std::size_t size)
    {
        return MemoryBlockSearch::nextFit(size, MemoryBlock::heapStart_);
    }

    static void *getUserMemoryField(MemoryBlock *memoryBlock)
    {
        return static_cast<void *>(reinterpret_cast<char *>(&(memoryBlock->next_)) + sizeof(void *));
    }
};
