add_library(internal_lib STATIC
        util/GeneralUtil.cpp)
target_include_directories(internal_lib PRIVATE ${CMAKE_SOURCE_DIR}/include/internal)