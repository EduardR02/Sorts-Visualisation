CC=g++
LIBS=-L src/lib -lsfml-graphics -lsfml-window -lsfml-system
INC=-I src/include
FLAGS=-std=c++14 -static-libstdc++ -pthread -Wall -Wextra -pedantic-errors

all: program

%.o: %.cpp
	$(CC) $(FLAGS) $(INC) -c $< -o $@

%.o: %.hpp
	$(CC) $(FLAGS) $(INC) -c $< -o $@

program: main.o gui.o bar.o sorts.o
	@echo "** Building"
	$(CC) $(FLAGS) -o program.exe main.o gui.o bar.o sorts.o $(LIBS)

clean:
	@echo "** Removing object and exe files!"
	del -f program.exe *.o

.PHONY: clean all