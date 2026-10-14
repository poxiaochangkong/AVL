cmake_minimum_required(VERSION 3.14)

project(AVL)


aux_source_directory(src/src SRC)

add_executable(main ${SRC})

#<filesystem>需要C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(main PUBLIC src/include)
