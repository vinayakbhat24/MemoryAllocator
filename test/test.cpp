#include <catch2/catch_test_macros.hpp>

#include "MemoryManagement.hpp"

TEST_CASE("MemoryManagement", "[basic]")
{
    std::size_t allocationSize = 100;
    auto allocationForData = MemoryManagement::allocate(allocationSize);
    auto memoryHeader = MemoryManagement::getBlock(allocationForData);
    REQUIRE(memoryHeader->size() == ((allocationSize + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1)));

    REQUIRE(not memoryHeader->free());

    MemoryManagement::free(allocationForData);
    REQUIRE(memoryHeader->free());
}

TEST_CASE("MemoryManagement", "[FirstFit]")
{
}

TEST_CASE("MemoryManagement", "[NextFit]")
{
}
