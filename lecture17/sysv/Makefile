all: parent child

parent: parent.cpp foo.cpp
	g++ -o parent parent.cpp foo.cpp

child: child.cpp foo.cpp
	g++ -o child child.cpp foo.cpp

clean:
	rm -f parent child
