add_library(core_lib STATIC
        Core.cpp
        Logger.cpp
        ConsoleProcess.cpp
        Color.cpp
)
target_include_directories(core_lib PRIVATE ${CMAKE_SOURCE_DIR}/include)