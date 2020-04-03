CROSS_COMPILE?=
SRC_TOPDIR :=$(shell pwd)

DIRS		:=. 
DEBUG		?=NO
ONLYCXX		:=NO
OBJDIR		:=.

INCDIRS		=${DIRS}
TMPDIR		:= tmp

#****************************************************************************
# Target
#****************************************************************************
SHARED 		?=NO

ifeq ($(SHARED),YES)
	TARGET		:=testModule.so
	SHARED_FLAGS := -shared -fPIC
	SHARED_SETNAME := -Wl,-soname,$(TARGET)
else
	APPOUT := -D CHECK
	TARGET		:=libcommon.a
endif


#****************************************************************************
# Compiler
#****************************************************************************
CC                 := ${CROSS_COMPILE}gcc
CXX                := ${CROSS_COMPILE}g++
AR                 := ${CROSS_COMPILE}ar
ARFLAGS            := rs

DEBUG_CFLAGS       := $(SHARED_FLAGS) -Wall  -g -std=c++11
#DEBUG_CFLAGS       := $(SHARED_FLAGS) -Wall -Wno-format -g 
#RELEASE_CFLAGS     := $(SHARED_FLAGS) -Wall -Wno-unknown-pragmas -Wno-format -O3 -g 
RELEASE_CFLAGS     := $(SHARED_FLAGS) -Wall -Wno-unknown-pragmas -Wno-format -O3 -s -std=c++11

ifeq (${DEBUG},YES)
   CCFLAGS         += ${DEBUG_CFLAGS}
   CXXFLAGS        += ${DEBUG_CFLAGS}
else
   CCFLAGS         += ${RELEASE_CFLAGS}
   CXXFLAGS        += ${RELEASE_CFLAGS}
endif

#****************************************************************************
# Paths
#****************************************************************************
#$(shell find . -maxdepth 2 -type d)
INCPRJ=$(foreach dir,$(INCDIRS),$(join -I,$(dir))) 

LIB_PATH           :=

INC_PATH           := ${INCPRJ} \
                      -I${SRC_TOPDIR}/include \
#****************************************************************************
# Source files
#****************************************************************************
ifeq (${ONLYCXX},NO)
SRCS               := ${foreach n,$(DIRS),$(wildcard ${n}/*.cpp ${n}/*.c)}
else
SRCS               := ${foreach n,$(DIRS),$(wildcard ${n}/*.cpp)}
endif

OBJS               := ${SRCS:%.cpp=${OBJDIR}/%.o}
OBJS               := ${OBJS:%.c=${OBJDIR}/%.o}
DEPE               := ${OBJS:%.o=%.d}
TMPDEF		   := ${foreach n,$(DIRS),$(wildcard ${n}/*.i)}


# LIBS               :=-lpthread -ldl -lc -lgcc -lm -lrt 

# LIBS :=-lstdc++ -lpthread -lm 

#****************************************************************************
# Output
#****************************************************************************
${TARGET}:${OBJS}
#${CXX} -rdynamic -s $(SHARED_FLAGS) -o $@ ${LIB_PATH} ${OBJS} ${LIBS}
	$(AR) $(ARFLAGS) $(SHARED_FLAGS) $(SHARED_SETNAME) -o $@ ${OBJS} ${LIB_PATH}  ${LIBS} 

-include $(DEPE) 
${OBJDIR}/%.o : %.cpp
	@[ -d $(@D) ] || mkdir -p $(@D)
	${CXX} $(APPOUT) -c ${CXXFLAGS} ${INC_PATH} $< -o $@

${OBJDIR}/%.d : %.cpp 
	@[ -d $(@D) ] || mkdir -p $(@D)
	@set -e; ${RM} $@; \
	$(CXX) -MM ${CXXFLAGS} ${INC_PATH} $< > $@.$$$$.i; \
	sed 's,\($(*F)\)\.o[ :]*,$*.o $@ : ,g' < $@.$$$$.i > $@; \
	${RM} $@.$$$$.i;

ifeq (${ONLYCXX},NO)
${OBJDIR}/%.o : %.c
	@[ -d $(@D) ] || mkdir -p $(@D)
	${CC} -c ${CCFLAGS} ${INC_PATH} $< -o $@

${OBJDIR}/%.d : %.c
	@[ -d $(@D) ] || mkdir -p $(@D)
	@set -e; ${RM} $@; \
	$(CC) -MM ${CCFLAGS} ${INC_PATH} $< > $@.$$$$.i; \
	sed 's,\($(*F)\)\.o[ :]*,$*.o $@ : ,g' < $@.$$$$.i > $@; \
	${RM} $@.$$$$.i;
endif	


.PHONY:all
all:${TARGET}

.PHONY:clean cleanobj
clean:
	${RM} ${TARGET} ${OBJS} ${DEPE} ${TMPDEF}
cleanobj:
	${RM} ${OBJS} ${DEPE} ${TMPDEF}


	 
