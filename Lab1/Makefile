CXXFLAGS+=-O2 -ggdb -DDEBUG
CXXFLAGS+=-Wall -Wextra

all: sudoku

sudoku: main.cc sudoku_basic.cc 
	g++ -o $@ $^ -lpthread

clean:
	rm sudoku
