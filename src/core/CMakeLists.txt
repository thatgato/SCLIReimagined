add_library(core_lib STATIC TestCore.cpp
)
target_include_directories(core_lib PRIVATE ${CMAKE_SOURCE_DIR}/include)