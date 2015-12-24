all: local_client local_server

local_client: local_client.cpp
	g++ -o local_client local_client.cpp

local_server: local_server.cpp
	g++ -o local_server local_server.cpp

clean:
	rm -f local_client local_server *~
