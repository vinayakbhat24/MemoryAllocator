#pragma once

#include <cstddef>

#include "MemoryBlock.hpp"

namespace MemoryBlockSearch
{
    inline MemoryBlock *firstFit(std::size_t size, MemoryBlock *head)
    {
        MemoryBlock *node = head;
        while (node != nullptr)
        {
            if (node->free() and size <= node->size())
            {
                return node;
            }
            node = node->next();
        }
        return nullptr;
    }
}
