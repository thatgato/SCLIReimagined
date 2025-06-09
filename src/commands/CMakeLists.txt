add_library(commands_lib STATIC TestCmd.cpp
)
target_include_directories(commands_lib PRIVATE ${CMAKE_SOURCE_DIR}/include)



