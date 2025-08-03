cmake_minimum_required(VERSION 3.10)

include_directories(
    .
    ./gtthread
    ./gtthread/handler
    ./gtthread/looper
    ./gtthread/task/
    ./gtthread/task/event
    ./gtthread/task/work
    ./gtthread/thread
    ./gtthread/utils
    ./gtthread/timer
    ./unittest
)

add_subdirectory(gtthread)
add_subdirectory(unittest)

