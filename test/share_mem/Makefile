####different compile condition
# GDB = 1
# CROSS_COMPILATION = arm-linux-
ifdef CROSS_COMPILATION
export CPP := $(CROSS_COMPILATION)g++
endif
export CPP := g++

ifdef GDB
	export FLAG := -Wall  -g
else
	export FLAG := -Wall -O2
endif
LINKFLAGS := -lpthread

INC_PATH := -I./
FLAG += $(INC_PATH)

#change TARGET for different program with the program name
TARGET = monitor monitor_msg_src 
ALL:$(TARGET)
monitor:monitor.o share_mem.o
	$(CPP) -o $@ $^ $(LINKFLAGS)
monitor_msg_src:monitor_msg_src.o share_mem.o
	$(CPP) -o $@ $^ $(LINKFLAGS)

%.o: %.cpp
	$(CPP) -c $(FLAG) -o $@ $< 

.PHONY:clean cleanall
clean:
#	@echo $(OBJ) 
	rm -rf *.o $(TARGET)
