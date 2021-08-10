cmake_minimum_required(VERSION 3.10)  # setting this is required
project(simulate_hawkes) # this sets the project name

# compiler and flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

# gather all files
include_directories(include)
file(GLOB SOURCES src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# link to OpenMP if exists
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
    set(CMAKE_C_COMPILER /usr/local/opt/llvm/bin/clang) # needs brew-installed compiler for openMP
endif()
set(CMAKE_CXX_COMPILER ${CMAKE_C_COMPILER}++)

# add run target
add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME} 
    DEPENDS ${CMAKE_PROJECT_NAME} 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )
