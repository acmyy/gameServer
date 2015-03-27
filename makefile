CC = gcc
CXX = g++

CCFLAGS = -g -o

server : test_server.o netpacket.o server_socket.o server_thread.o mysql.o logic_factory.o
	$(CXX) -o server test_server.o netpacket.o server_socket.o server_thread.o mysql.o logic_factory.o -lpthread -lmysqlclient 

logic_factory.o : logic_factory.cpp
	$(CXX) -c logic_factory.cpp -lmysqlclient 
test_server.o : test_server.cpp
	$(CXX) -c test_server.cpp 
netpacket.o : netpacket.cpp
	$(CXX) -c netpacket.cpp
server_socket.o : server_socket.cpp
	$(CXX) -c server_socket.cpp
server_thread.o : server_thread.cpp
	$(CXX) -c server_thread.cpp -lpthread
mysql.o : mysql.cpp
	$(CXX) -c mysql.cpp -lmysqlclient



all: server  
	@echo "complie done!"

clean :
	rm -rf server 
