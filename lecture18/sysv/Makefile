# Makefile for System V Shared Memory example

all: shm_clnt shm_srvr

shm_srvr: shm_srvr.cpp shm_com.h
	g++ -o shm_srvr shm_srvr.cpp

shm_clnt: shm_clnt.cpp shm_com.h
	g++ -o shm_clnt shm_clnt.cpp

clean:
	rm -f shm_srvr shm_clnt
