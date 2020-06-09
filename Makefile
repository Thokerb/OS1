CFLAGS = -std=gnu11 -Wall  -Wextra

.PHONY: all clean

all: task1 task2 task3

clean:
	$(RM) task1 task2 task3

task1: task1.c
task2: task2.c
task3: task3.c