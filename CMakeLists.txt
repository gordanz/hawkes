cmake_minimum_required(VERSION 3.10)  # setting this is required
project(simulate_hawkes) # this sets the project name

# compiler and flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")


# gather all files
include_directories(include)
file(GLOB SOURCES src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# link to OpenMP if exists
find_package(OpenMP REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)

# Looks like you need brew clang for omp, but the Apple one for find_package(OpenMP...)
if(APPLE)
    set(CMAKE_C_COMPILER /usr/local/opt/llvm/bin/clang)
    set(CMAKE_CCX_COMPILER ${CMAKE_C_COMPILER}++)
endif()

# add run target
add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME} 
    DEPENDS ${CMAKE_PROJECT_NAME} 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )

# Doxygen

# look for Doxygen package
find_package(Doxygen)

if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target( doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
