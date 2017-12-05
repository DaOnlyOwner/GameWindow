file(GLOB_RECURSE SOURCES_GameWindow include/GameWindow/*.hpp)

add_library(GameWindow INTERFACE)
target_sources(GameWindow INTERFACE ${SOURCES_GameWindow})

target_include_directories(GameWindow INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/glfw/include")

set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
target_link_libraries(GameWindow INTERFACE glfw)
