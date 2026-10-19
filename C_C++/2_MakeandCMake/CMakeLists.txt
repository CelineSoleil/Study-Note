cmake_minimum_required(VERSION 3.10)
#最低版本号
project(HelloWorld)
#项目名字
set(SOURCES main.cpp message.cpp)
#要用文件
add_executable(hello ${SOURCES})
#生成可执行文件名字，执行cmake，自动给我们生成makefile文件，如bulid文件夹下面