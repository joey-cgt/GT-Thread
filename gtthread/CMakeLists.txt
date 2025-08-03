cmake_minimum_required(VERSION 3.10)
project(gtthread)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    .
    ./handler
    ./looper
    ./task
    ./task/event
    ./task/work
    ./thread
    ./utils
    ./timer
)

# 递归收集所有 .cpp 文件
file(GLOB_RECURSE SRC_FILES "*.cpp")

# 排除 build 目录（假设构建目录为 ${CMAKE_BINARY_DIR}）
list(FILTER SRC_FILES EXCLUDE REGEX "${CMAKE_BINARY_DIR}/.*")

find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# 生成静态库
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)

if(WIN32)
    # Windows 下无需链接 pthread，直接使用系统 API
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()
