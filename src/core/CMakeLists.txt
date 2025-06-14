add_library(core_lib STATIC TestCore.cpp
        Core.cpp
        Logger.cpp
)
target_include_directories(core_lib PRIVATE ${CMAKE_SOURCE_DIR}/include)