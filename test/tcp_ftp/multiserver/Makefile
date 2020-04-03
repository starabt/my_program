CROSS_COMPILATION = arm-linux-
ifdef CROSS_COMPILATION
CPP = $(CROSS_COMPILATION)g++
endif
CPP = g++
GDB = 1
ifdef GDB
	FLAG =  -g
else
	FLAG = -Wall -O2
endif
#change TARGET for different program with the program name
TARGET = myqueue
ALL:$(TARGET)
MAIN_SRC := $(TARGET)_test.cpp
SRC := $(wildcard ./$(TARGET).cpp)
INC := $(wildcard ./$(TARGET).h)
DIR := $(notdir $(SRC))	
OBJ := $(patsubst %.cpp,%.o,$(DIR))
# OBJ := $($(SRC):%.cpp=%.o)
$(OBJ):$(SRC) $(INC)
	$(CPP) -c $(FLAG)  $(SRC)
$(TARGET):$(MAIN_SRC) $(OBJ)
	$(CPP) -o $(TARGET) $^ 
.PHONY:clean
clean:
	rm -rf $(OBJ) $(TARGET)