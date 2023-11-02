cmake_minimum_required(VERSION 3.1...3.27)
project(
  MemoryAllocatorTest
  VERSION 1.0
  LANGUAGES CXX)
find_package(Catch2 3 REQUIRED)
add_executable(tests test.cpp)

target_include_directories(tests PRIVATE ../src)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)


