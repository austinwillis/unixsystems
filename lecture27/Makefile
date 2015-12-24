# basic GTK+ app makefile
CCFLAGS  = `pkg-config --cflags --libs gtk+-2.0`
CC       = g++

all: layout tablelayout dialog buttons adder

layout: layout.cpp
	${CC} -o layout layout.cpp ${CCFLAGS}

tablelayout: tablelayout.cpp
	${CC} -o tablelayout tablelayout.cpp ${CCFLAGS}

dialog: dialog.cpp
	${CC} -o dialog dialog.cpp ${CCFLAGS}

buttons: buttons.cpp
	${CC} -o buttons buttons.cpp ${CCFLAGS}

adder: adder.cpp
	${CC} -o adder adder.cpp ${CCFLAGS}


clean:
	rm -f layout
	rm -f tablelayout
	rm -f dialog
	rm -f buttons
	rm -f adder
	rm -f *~
