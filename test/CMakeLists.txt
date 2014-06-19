set(CMAKE_CXX_FLAGS "-std=c++11")
include_directories(../src)

add_executable(test-basic-merge test_basic_merge.cpp ../src/datatype.cpp)
add_executable(test-reorder test_reorder.cpp)
