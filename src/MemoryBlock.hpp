#include <cstddef>
#include <unistd.h>

class MemoryBlock
{
public:
    std::size_t getSize() const
    {
        return size_;
    }

    std::size_t getUsed() const
    {
        return used_;
    }

    static void *allocate(const std::size_t size)
    {
        const auto alignedSize = align(size);
        MemoryBlock *mb = requestFromOS(alignedSize);
        if (not mb)
        {
            return nullptr;
        }

        mb->size_ = alignedSize;
        mb->used_ = true;
        if (not heapStart)
        {
            heapStart = mb;
        }

        if (not heapEnd)
        {
            heapEnd = mb;
        }
        else
        {
            heapEnd->next_ = mb;
        }

        return static_cast<void *>(reinterpret_cast<char *>(&(mb->next_)) + sizeof(void *));
    }

    static const MemoryBlock *getBlock(const void *dataFiled)
    {

        return reinterpret_cast<const MemoryBlock *>((static_cast<const char *>(dataFiled) - sizeof(MemoryBlock)));
    }

private:
    static MemoryBlock *requestFromOS(const std::size_t size)
    {
        auto memoryBlock = (MemoryBlock *)sbrk(0);

        if (sbrk(size) == (void *)-1)
        {
            return nullptr;
        }

        return memoryBlock;
    }

    static std::size_t align(const std::size_t size)
    {
        return size + (sizeof(void *) - 1) & ~(sizeof(void *) - 1);
    }

    std::size_t size_;
    bool used_;
    MemoryBlock *next_;

    static inline MemoryBlock *heapStart = nullptr;
    static inline MemoryBlock *heapEnd = nullptr;
};
