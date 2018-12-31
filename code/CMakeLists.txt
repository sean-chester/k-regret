# Adapted from https://r4nd0m6uy.ch/cmake-and-cpputest.html

cmake_minimum_required( VERSION 3.4 )
project( k-regret )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set( CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} \
    -fopenmp \
    -march=native \
    -mavx \
    -Wall \
    -g \
    -ansi \
    -Wextra \
    -Wdisabled-optimization \
    -Wunsafe-loop-optimizations \
    -Wpedantic \
    -Wshadow"
)
set( CMAKE_CXX_FLAGS_DEBUG
  "${CMAKE_CXX_FLAGS_DEBUG} \
    -Og"
) 
set( CMAKE_CXX_FLAGS_RELEASE
  "${CMAKE_CXX_FLAGS_RELEASE}"
)
set(
  basepath
    "${CMAKE_SOURCE_DIR}"
)

find_package( Boost 1.62.0 COMPONENTS program_options REQUIRED )

include_directories( ${Boost_INCLUDE_DIR} )
include_directories( "${basepath}/include" )

# Production code
add_subdirectory(src)

# Unit tests -- external dependency -- requires adding Catch2 to ./include/
option(BUILD_TESTS "Build all the unit tests" OFF)
if(BUILD_TESTS)
  add_subdirectory(test)
endif(BUILD_TESTS)
