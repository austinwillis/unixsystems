#CS375 Homework 1
#Austin Willis

CC = clang++
PROJECT = connect4
CFLAGS = -std=c++0x -lncurses -lmenu -lgdbm
DEPS = board.h
OBJECTS = board.o cfour.o

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean :
	rm cnct4 board.o cfour.o
