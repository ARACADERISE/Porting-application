.PHONY: main.c

main.c:
	gcc -Wall -o main.o main.c dimensions.c porter.c
run: main.c dimensions.c porter.c
	./main.o