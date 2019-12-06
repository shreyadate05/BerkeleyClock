# Makefile for the socket programming example
#
daemon_objects  = TimeDaemon.o Socket.o TimeDaemonMain.o 
server_objects = Server.o Socket.o ServerMain.o 

all : daemon server

daemon: $(daemon_objects)
	g++ -pthread -o daemon $(daemon_objects)

server: $(server_objects)
	g++ -pthread -o server $(server_objects)

Socket: Socket.cpp
TimeDaemon: TimeDaemon.cpp
Server: Server.cpp
daemon_main: TimeDaemonMain.cpp
server_main: ServerMain.cpp

clean:
	rm -rf *.o daemon server
