INC_PATH	=  	-I$(COMMON_PATH) 
CPPFLAGS	:=	$(CPPFLAGS_V) $(INC_PATH)
SRCS		:=	$(wildcard *.cpp)
OBJS		:=	$(SRCS:%.cpp=%.o)

LOCAL_TARGET := $(notdir $(SUB_PATH)).a
$(LOCAL_TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $(LOCAL_TARGET) $(OBJS)

%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) -shared -fPIC  -o $@ $< 
	
.PHONY: clean dep

clean:
	rm -f $(OBJS) $(LOCAL_TARGET) *.dep
	
dep:
	(for i in *.cpp;do echo -n "    ";$(CPP) -MM $(INC_PATH) $$i;done) > Makefile.dep
	
### Dependencies:
ifeq (Makefile.dep, $(wildcard Makefile.dep))
include Makefile.dep
endif