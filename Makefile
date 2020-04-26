
CC = gcc
CFLAGS = -Wall -g
all: main

main: tab.o utils.o tema2.o
	$(CC) $(FLAGS) $^ -o $@
tab.o: tab.c
	$(CC) $(FLAGS) -c $< -o $@
tema2.o: tema2.c
	$(CC) $(FLAGS) -c $< -o $@
run:
	./main
clean:
	rm -f *.o main
check:
	valgrind --leak-check=full ./main 1.in 1.out
