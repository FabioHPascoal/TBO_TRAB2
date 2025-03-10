all:
	gcc -Wall -g -o main.out *.c
run:
	./main.out
valgrind:
	valgrind --leak-check=full ./main.out
clean:
	rm -f main.out