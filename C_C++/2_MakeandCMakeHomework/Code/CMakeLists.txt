cmake_minimum_required(VERSION 3.10)
#最低版本号

project(student_stats CXX)
#项目名字

file(GLOB SOURCES src/*.cpp)  # 自动收集 src/ 下所有 cpp，不用手写列表
#set(SOURCES src/main.cpp src/topStudent.cpp src/printAll.cpp src/average.cpp)
#要用文件

add_executable(student_stats ${SOURCES})
#生成可执行文件名字，执行cmake，自动给我们生成makefile文件，如bulid文件夹下面

target_include_directories(student_stats PRIVATE include)