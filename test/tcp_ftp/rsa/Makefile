TARGET=server2 client2 server3 client3
SRCS=server2.cpp client2.cpp RSA.h RSA.cpp server3.cpp client3.cpp
OBJS=$(patsubst %.c,%.o,$(SRCS))
CC=gcc 
CX=g++
CCC=arm-linux-gcc
CXX=arm-linux-g++
.PYTHON:all
all:$(TARGET)
#$(TARGET):$(OBJS)
#	$(CX) -o $@ $(addsyffix .o,$^) 
server2:server2.cpp RSA.h RSA.cpp
	$(CX) -o $@ $^
client2a:client2.cpp RSA.h RSA.cpp
	$(CXX) -o $@ $^
client2:client2.cpp RSA.h RSA.cpp
	$(CX) -o $@ $^
server3:server3.cpp RSA.h RSA.cpp
	$(CX) -o $@ $^
client3:client3.cpp RSA.h RSA.cpp
	$(CX) -o $@ $^
.PYTHON:clean
clean:
	rm -rf $(OBJS) $(TARGET) 	
