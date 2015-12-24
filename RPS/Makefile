#Austin Willis
#CS375
#Final Project
all: server client guiclient

server:
	g++ -o referee server.cpp -std=c++11 -lpthread

client:
	g++ -o player client.cpp

guiclient:
	g++ -o gui-player gui-client.cpp `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm referee player gui-player
