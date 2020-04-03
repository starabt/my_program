TARGEt := AESserver
OBJS = AESserver.o  AES.o
AESserver : $(OBJS)
	g++  -o $@ $(OBJS)
AESserver.o : AESserver.cpp
#	g++ -c AESserver.cpp
AES.o : AES.h 
#	g++ -c AES.cpp
#client:client.c
#	gcc $^ -o $@

clean:
	rm -rf $(OBJS) $(TARGEt)

