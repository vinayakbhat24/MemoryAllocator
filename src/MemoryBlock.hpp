#pragma once

#include <cstddef>
#include <unistd.h>

class MemoryManagement;

class MemoryBlock
{
public:
    std::size_t size() const
    {
        return size_;
    }

    bool free() const
    {
        return not inUse_;
    }

    MemoryBlock *next()
    {
        return next_;
    }

    static inline MemoryBlock *heapStart_ = nullptr;
    static inline MemoryBlock *heapEnd_ = nullptr;
    static inline MemoryBlock *nextFit_ = nullptr;

private:
    std::size_t size_;
    bool inUse_;
    MemoryBlock *next_;

    friend class MemoryManagement;
};
