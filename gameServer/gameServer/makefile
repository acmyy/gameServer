CC = gcc
CXX = g++

CCFLAGS = -g -o

server : gameServer.o serverSocket.o 
	$(CXX) -o server gameServer.o serverSocket.o 

gameServer.o : gameServer.cpp
	$(CXX) -c gameServer.cpp

serverSocket.o : serverSocket.cpp
	$(CXX) -c serverSocket.cpp

all: server 
	@echo "complie done!"

clean :
	rm -rf server 
