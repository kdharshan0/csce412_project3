CC = g++
CFLAGS = -Wall -std=c++11

all: loadbalancer

loadbalancer: main.o LoadBalancer.o WebServer.o Request.o
	$(CC) $(CFLAGS) -o loadbalancer main.o LoadBalancer.o WebServer.o Request.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

LoadBalancer.o: LoadBalancer.cpp LoadBalancer.h
	$(CC) $(CFLAGS) -c LoadBalancer.cpp

WebServer.o: WebServer.cpp WebServer.h
	$(CC) $(CFLAGS) -c WebServer.cpp

Request.o: Request.cpp Request.h
	$(CC) $(CFLAGS) -c Request.cpp

clean:
	rm -f *.o loadbalancer