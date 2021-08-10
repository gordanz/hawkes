cmake_minimum_required(VERSION 3.10)  # setting this is required
project(simulate_hawkes) # this sets the project name

# compiler and flags
set(CMAKE_C_COMPILER /usr/local/opt/llvm/bin/clang) # needs brew-installed compiler for openMP
set(CMAKE_CXX_COMPILER ${CMAKE_C_COMPILER}++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# gather all files
include_directories(include)
file(GLOB SOURCES src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# link to OpenMP
find_package(OpenMP REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

# add run target
add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME} 
    DEPENDS ${CMAKE_PROJECT_NAME} 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )
