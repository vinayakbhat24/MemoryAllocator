#include <cstddef>
#include <unistd.h>

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

    static void *allocate(const std::size_t size)
    {
        const auto alignedSize = align(size);
        MemoryBlock *mb = requestFromOS(alignedSize);
        if (not mb)
        {
            return nullptr;
        }

        mb->size_ = alignedSize;
        mb->inUse_ = true;

        /*Update linked list*/
        if (not heapStart)
        {
            heapStart = mb;
        }
        if (heapEnd)
        {
            heapEnd->next_ = mb;
        }
        heapEnd = mb;

        return static_cast<void *>(reinterpret_cast<char *>(&(mb->next_)) + sizeof(void *));
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
    bool inUse_;
    MemoryBlock *next_;

    static inline MemoryBlock *heapStart = nullptr;
    static inline MemoryBlock *heapEnd = nullptr;
};
