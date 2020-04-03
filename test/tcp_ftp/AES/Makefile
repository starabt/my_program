TARGET=clientAES serverAES
SCRS=AES2.cpp AES.h clientAES.cpp serverAES.cpp
CC=gcc
CX=g++
CCC=arm-linux-gcc
CXX=arm-linux-g++
.PYTHON:all
all:$(TARGET)
clientAES:AES2.cpp AES.h clientAES.cpp 
	$(CX) -o $@ $^
serverAES:AES2.cpp AES.h serverAES.cpp
	$(CX) -o $@ $^
