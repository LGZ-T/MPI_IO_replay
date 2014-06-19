set(CMAKE_CXX_FLAGS "-std=c++11")

# lcs part
add_executable(replay replay.cpp datatype.cpp)

add_executable(lcs_trace lcs_merge_trace.cpp datatype.cpp)

# add_executable(trace_tree suffix_tree_edit.cpp test_suffix_tree_diff.cpp datatype.cpp)

add_executable(compress suffix_tree_edit.cpp repetition_in_tree.cpp datatype.cpp)
