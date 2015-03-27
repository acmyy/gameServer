CC = gcc
CXX = g++

CCFLAGS = -g -o

server : test.o netpacket.o serverSocket.o serverThread.o mysql.o
	$(CXX) -o server test.o netpacket.o serverSocket.o serverThread.o mysql.o -lpthread -lmysqlclient 

test.o : test.cpp
	$(CXX) -c test.cpp 
netpacket.o : netpacket.cpp
	$(CXX) -c netpacket.cpp
serverSocket.o : serverSocket.cpp
	$(CXX) -c serverSocket.cpp
serverThread.o : serverThread.cpp
	$(CXX) -c serverThread.cpp -lpthread
mysql.o : mysql.cpp
	$(CXX) -c mysql.cpp -lmysqlclient

client : muti_thread_echo_cli.o netpacket.o
	$(CXX) -o client muti_thread_echo_cli.o netpacket.o -lpthread

muti_thread_echo_cli.o : muti_thread_echo_cli.cpp
	$(CXX) -c muti_thread_echo_cli.cpp

all: server client 
	@echo "complie done!"

clean :
	rm -rf server client 
