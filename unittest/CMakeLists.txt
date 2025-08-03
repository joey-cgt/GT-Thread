cmake_minimum_required(VERSION 3.10)
project(gtthreadunittest)

file(GLOB_RECURSE SRC_FILES "*.cpp")

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries(${PROJECT_NAME} 
    GTest::GTest
    GTest::Main
    gtthread
)
