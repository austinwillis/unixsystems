all: master reverse upper

master: master.cpp msg.h
	g++ -o master master.cpp -lrt -lpthread

reverse: reverse.cpp msg.h
	g++ -o reverse reverse.cpp -lrt -lpthread

upper: upper.cpp
	g++ -o upper upper.cpp -lrt -lpthread

clean:
	rm -f master reverse upper
