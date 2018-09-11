cmake_minimum_required(VERSION 3.8)

set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 8)

project(allocator VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(allocator main.cpp CustomAllocator.h custom_container.h)

set(target "allocator")

function(set_warning_flags target)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
                target_compile_options(${target} PRIVATE "-Wall" "-Wextra" "-pedantic-errors")
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
                target_compile_options(${target} PRIVATE "/W4")
        endif()
endfunction()


install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dontevenwriteme@example.com)

include(CPack)
