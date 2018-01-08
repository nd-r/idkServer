cmake_minimum_required(VERSION 3.9)
project(idk)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Werror -Wextra")

add_executable(idk main.cpp utils.hpp Server.cpp Server.hpp WorkerPool.cpp WorkerPool.hpp Worker.cpp Worker.hpp ConnectionInstance.cpp ConnectionInstance.hpp utils.cpp)
target_link_libraries(idk ev)