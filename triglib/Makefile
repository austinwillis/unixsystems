#CS375 Homework 1
#Austin Willis

PROJECT = libmytrig.a
OBJECTS = mytan.o mysin.o mycos.o mytrig.h
CFLAGS = -Wall -pedantic

all: $(PROJECT)

.cpp.o:
	g++ -c $(CFLAGS) $<

$(PROJECT): $(OBJECTS)
	ar rc $(PROJECT) $(OBJECTS)

testmytrig: testmytrig.cpp
	g++ -o testmytrig testmytrig.cpp -L. -lmytrig
