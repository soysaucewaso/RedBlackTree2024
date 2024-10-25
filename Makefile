all: main.o Node.o Tree.o
	g++ -g main.o Node.o Tree.o -o exe

main.o: main.cpp
	g++ -g -c main.cpp

Node.o: Node.cpp
	g++ -g -c Node.cpp

Tree.o: Tree.cpp
	g++ -g -c Tree.cpp
