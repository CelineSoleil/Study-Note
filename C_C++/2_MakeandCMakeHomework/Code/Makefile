CFLAGS = -Wall -Wextra -g -O0
source = src/main.cpp src/student.cpp src/stats.cpp
objects = main.o student.o stats.o
targets = student_stats
INCLUDE = -Iinclude
.PHONY: clean

student_stats:main.o student.o stats.o
	g++ main.o student.o stats.o -o $@

%.o:src/%.cpp
	g++ $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f *.o $(targets)

.PHONY: all
all: $(targets)
	@echo "all done"