# GDB = -g
#CROSS := arm-himix200-linux-
CROSS := arm-oe-linux-gnueabi-
CPP := $(CROSS)g++
LINKFLAGS := -lpthread -lstdc++
INCLUDE_PATH := -I./
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
CPPFLAGS := -Wall -O2 
CPPFLAGS +=  $(INCLUDE_PATH)
TARGET = /home/lxc/work/opencpu/transcenter/ftp_upload
$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $^ $(LINKFLAGS)
	cp $(TARGET) ./
%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $< 
.PHONY: clean
clean:
	rm -fr $(OBJS) $(TARGET) 
