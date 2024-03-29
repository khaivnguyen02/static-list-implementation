all:
	gcc -g -Wall -Werror -o demo main.c list.c
clean:
	rm demo