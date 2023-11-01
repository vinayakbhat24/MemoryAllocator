#pragma once

#include <cstddef>
#include <iostream>

#include "MemoryBlock.hpp"

namespace MemoryBlockSearch
{
    inline MemoryBlock *nextFit(std::size_t size, MemoryBlock *head)
    {

        // static MemoryBlock *nextFit = head;  hereererererererer

        MemoryBlock *currentSearchStart = MemoryBlock::nextFit_;
        MemoryBlock *blockToReturn{nullptr};
        MemoryBlock *toCompare{nullptr};

        if (not currentSearchStart)
        {
            return nullptr;
        }

        auto search = [&](MemoryBlock *endNodeToCompare) -> MemoryBlock *
        {
            MemoryBlock *returnVal{nullptr};

            while (currentSearchStart and currentSearchStart != endNodeToCompare)
            {

                if (currentSearchStart->free() and size <= currentSearchStart->size())
                {
                    return currentSearchStart;
                }
                currentSearchStart = currentSearchStart->next();
            }
            return nullptr;
        };

        blockToReturn = search(nullptr);

        if (not blockToReturn)
        {
            currentSearchStart = head;
            blockToReturn = search(MemoryBlock::nextFit_);
        }

        if (blockToReturn)
        {
            MemoryBlock::nextFit_ = blockToReturn->next();
            if (not MemoryBlock::nextFit_)
            {
                MemoryBlock::nextFit_ = head;
            }
        }

        return blockToReturn;
    }
}
