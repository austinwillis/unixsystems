all: parent child

parent: parent.cpp foo.cpp
	g++ -o parent parent.cpp foo.cpp -pthread

child: child.cpp foo.cpp
	g++ -o child child.cpp foo.cpp -pthread

clean:
	rm -f parent child
