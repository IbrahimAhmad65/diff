cmake_minimum_required(VERSION 3.22.1)
project(diff)
set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")
file(GLOB_RECURSE diff_src src/*.cpp)
add_executable(diff main.cpp ${diff_src}) 
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

#if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    add_compile_options(-fdump-lang-class)
#else()
#    message(WARNING "This directive is only supported with GCC.")
#endif()

if(NOT USE_SYSTEM_EIGEN)
    set(EIGEN_BUILD_CMAKE_PACKAGE TRUE)
    FetchContent_Declare(
        Eigen3
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        # master on 2025-01-02
        GIT_TAG 7bb23b1e360e22a395eef75061565fc079ae6a85
    )
    fetchcontent_makeavailable(Eigen3)
else()
    find_package(Eigen3 CONFIG REQUIRED)
endif()

target_link_libraries(diff PUBLIC Eigen3::Eigen)

target_include_directories(diff PRIVATE inc/ src/)
target_compile_options(diff PRIVATE -march=native -fconcepts -fdump-lang-class)
