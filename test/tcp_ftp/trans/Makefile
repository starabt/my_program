TARGET=client server
SRCS=RSA.h AES.h RSA.cpp AES2.cpp
CC=gcc
CX=g++
CCC=arm-linux-gcc
CXX=arm-linux-g++
.PYTHON:all
all:$(TARGET)
client:client.cpp RSA.h AES.h RSA.cpp AES2.cpp
	$(CX) -o $@ $^
server:server.cpp RSA.h AES.h RSA.cpp AES2.cpp
	$(CX) -o $@ $^
