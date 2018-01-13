cmake_minimum_required(VERSION 3.9)
project(idk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Werror -Wextra")

add_executable(idk
        main.cpp
        utils/utils.hpp utils/utils.cpp
        Server/Server.cpp Server/Server.hpp
        Pool/WorkerPool.cpp Pool/WorkerPool.hpp
        Pool/Worker.cpp Pool/Worker.hpp
        Server/ConnectionInstance.cpp Server/ConnectionInstance.hpp
        Server/Config.cpp Server/Config.hpp)

target_link_libraries(idk ev)