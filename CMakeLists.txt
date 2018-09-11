cmake_minimum_required(VERSION 3.8)

set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 8)

project(allocator VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(allocator main.cpp CustomAllocator.h custom_container.h)

set_target_properties(allocator  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

install(TARGETS allocator RUNTIME DESTINATION bin)
