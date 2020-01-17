all: project2

project2: user_interface.o llist.o
	g++ -o project2 user_interface.o llist.o
user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall $(DEBUG) -c user_interface.cpp
llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall $(DEBUG) -c llist.cpp
debug: DEBUG = -DDEBUG

debug: project2

clean:
	-rm -f user_interface.o
	-rm -f llist.o
	-rm -f project2.o
	-rm -f project2
