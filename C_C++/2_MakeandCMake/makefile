# hello: main.cpp message.cpp
# g++ main.cpp message.cpp -o hello
#实际是先编译成.o文件,-o表示输出文件名字，-c表示编译成.o文件而不进行进行链接
#俩个一样的可以空格隔开，然后重命名加$@自动变量

#hello world: main.o message.o
#g++ main.o message.o -o $@

#world: main.o message.o
#g++ main.o message.o -o world


#定义变量,运用就$(targets)
CFLAGS = -Wall -g -02
targets = hello world
sources = main.cpp message.cpp
objects = main.o message.o


$(objects): $(sources)
	g++ $(CFLAGS) -c $< -o $@

$(targets): $(objects)
	g++ $^ -o $@


# 伪目标指不生成文件的目标，只是一些标签，只执行操作，如clean：
# 加个.PHONY: clean，表示clean是一个伪目标，不会生成clean文件
# 也就是不会提醒依旧是最新的了
.PHONY: clean

clean:
	rm -f *.o hello world

# all，make默认执行第一个目标，all表示编译所有的目标
.PHONY: all
all: hello world
	@echo "all done"

#如果文件名不算makefile，需要加上指定makefile文件名如：make clean -f hello.mk
#其他操作，make -n 打印要执行的命令，但不会真执行

