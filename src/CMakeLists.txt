add_subdirectory(commands)
add_subdirectory(core)
add_subdirectory(internal)
add_subdirectory(pages)

add_executable(scli-r-exec main.cpp)

target_link_libraries(scli-r-exec PRIVATE commands_lib)
target_link_libraries(scli-r-exec PRIVATE core_lib)
target_link_libraries(scli-r-exec PRIVATE internal_lib)
target_link_libraries(scli-r-exec PRIVATE pages_lib)

target_include_directories(scli-r-exec PRIVATE ${CMAKE_SOURCE_DIR}/include)