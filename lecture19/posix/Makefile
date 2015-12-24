all: msg_server msg_client

msg_server: msg_server.cpp msg.h
	g++ -o msg_server msg_server.cpp -lrt

msg_client: msg_client.cpp msg.h
	g++ -o msg_client msg_client.cpp -lrt

clean:
	rm -f msg_server msg_client
