cmake_minimum_required(VERSION 3.10)  # setting this is required
project(goodvector) # this sets the project name

# compiler and flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")


# gather all files
# include_directories(include)
file(GLOB SOURCES *.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})


# add run target
add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME} 
    DEPENDS ${CMAKE_PROJECT_NAME} 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )
