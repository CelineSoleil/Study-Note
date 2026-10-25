#编译器
CXX :=g++

#编译选项
# -MMD -MP：自动生成头文件依赖关系
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -MMD -MP

#最终程序
TARGET := make_student_manager.exe

#所有资源文件
SRCS := main.cpp StudentService.cpp

#将main.cpp StudentService.cpp变成.o文件
OBJS :=$(SRCS:.cpp=.o)

#自动生成依赖文件
DEPS := $(OBJS:.o=.d)

#默认目标
all: $(TARGET)

#链接，把所有.o链接成exe
$(TARGET):$(OBJS)
	$(CXX) $(OBJS) -o $@

#编译,把每个.cpp编译成对应.o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
#运行程序
run: $(TARGET)
	./$(TARGET)

#清理生成文件
clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET)

# 让 make 知道哪些 .cpp 依赖哪些 .h
-include $(DEPS)

.PHONY: all run clean