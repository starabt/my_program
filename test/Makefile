CROSS=
DEBUG?=
# FLAG=-Wall
FLAG=
ifeq ($(DEBUG),YES)
	FLAG+=-g
endif
CPP=g++
LIB=-lpthread 
LIB+=-std=c++11
TARGET=app
OBJ=test.o
$(TARGET):$(OBJ)
	$(CROSS)$(CPP) -o $@ $^ $(LIB)
%.o:%.cpp
	$(CROSS)$(CPP) -c $(FLAG) -o $@ $< $(LIB)
.PHONY:clean
clean:
	rm $(TARGET) $(OBJ)
