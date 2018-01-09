cmake_minimum_required(VERSION 3.9)
project(idk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Werror -Wextra")

add_executable(idk
        main.cpp
        utils.hpp utils.cpp
        Server.cpp Server.hpp
        WorkerPool.cpp WorkerPool.hpp
        Worker.cpp Worker.hpp
        ConnectionInstance.cpp ConnectionInstance.hpp
        Config.cpp Config.hpp)

target_link_libraries(idk ev)