# basic GTK+ app makefile
CCFLAGS  = `pkg-config --cflags --libs gtk+-2.0`
CC       = g++

all: first helloworld layout packbox

first: first.cpp
	${CC} -o first first.cpp ${CCFLAGS}

helloworld: helloworld.cpp
	${CC} -o helloworld helloworld.cpp ${CCFLAGS}

layout: layout.cpp
	${CC} -o layout layout.cpp ${CCFLAGS}


packbox: packbox.cpp 
	${CC} -o packbox packbox.cpp ${CCFLAGS}

clean:
	rm -f first
	rm -f helloworld
	rm -f packbox
	rm -f layout
	rm -f *~

