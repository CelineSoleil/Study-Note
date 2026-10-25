cmake_minimum_required(VERSION 3.10)
#最低版本号

project(StudentManager LANGUAGES CXX)
#项目名字

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(SOURCES main.cpp StudentService.cpp)#1.
#要用文件

#add_executable(cmake_student_manager ${SOURCES})#1.
add_executable(cmake_student_manager main.cpp StudentService.cpp)#2.
#生成可执行文件名字，执行cmake，自动给我们生成makefile文件，如bulid文件夹下面
# cmake -S . -B build
# cmake --build build