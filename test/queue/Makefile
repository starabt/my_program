GDB = -g
CPP := g++
LINKFLAGS := -lpthread
INCLUDE_PATH := -I./
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
CPPFLAGS := -Wall -O2 
CPPFLAGS += $(GDB) $(INCLUDE_PATH)
TARGET = listtest
$(TARGET): $(OBJS)
	$(CPP) -o $(TARGET) $^ $(LINKFLAGS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $< 
.PHONY: clean
clean:
	rm -fr $(OBJS) $(TARGET) 