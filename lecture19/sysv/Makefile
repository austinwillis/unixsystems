all: msg_server msg_client

msg_server: msg_server.cpp msg.h
	g++ -o msg_server msg_server.cpp

msg_client: msg_client.cpp msg.h
	g++ -o msg_client msg_client.cpp

clean:
	rm -f msg_server msg_client
