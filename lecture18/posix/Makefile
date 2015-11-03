# Makefile for POSIX shared memory exercise

all: mmap_clnt mmap_srvr

mmap_srvr: mmap_srvr.cpp mmap_com.h
	g++ -o mmap_srvr mmap_srvr.cpp -lrt

mmap_clnt: mmap_clnt.cpp mmap_com.h
	g++ -o mmap_clnt mmap_clnt.cpp -lrt

clean:
	rm -f mmap_srvr mmap_clnt
