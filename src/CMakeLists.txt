set(CMAKE_CXX_FLAGS "-std=c++11")

# lcs part
add_executable(replay replay.cpp datatype.cpp)

add_executable(lcs_trace lcs_merge_trace.cpp datatype.cpp)

# add_executable(trace_tree trace_tree.cpp suffix_tree_edit.cpp datatype.cpp)

add_executable(compress suffix_tree_edit.cpp repetition_in_tree.cpp datatype.cpp)
