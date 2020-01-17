all: project1

project1: user_interface.o database.o
	gcc -o project1 user_interface.o database.o

user_interface.o: user_interface.c
	gcc -ansi -pedantic-errors -Wall -c user_interface.c

database.o: database.c
	gcc -ansi -pedantic-errors -Wall -c database.c

clean:
	-rm -f user_interface.o
	-rm -f database.o
	-rm -f project1.o
	-rm -f project1
	-rm -f database.txt
