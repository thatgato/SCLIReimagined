add_library(pages_lib STATIC TestPage.cpp)
target_include_directories(pages_lib PRIVATE ${CMAKE_SOURCE_DIR}/include)