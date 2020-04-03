#include "sendfile.h"

/*客户端的处理过程*/
void process_conn_client(int s)
{
	ssize_t size = 0;
	char buffer[BUFFER_SIZE];
	FILE *stream;
 
	int length=0;
	char buffer_add[BUFFER_SIZE]={'\0'};
	for(;;){
		size = read(s, buffer, BUFFER_SIZE-length);
		if(size <= 0){
			return;
		}
		strcat(buffer_add, buffer);
		length+=size;
		if(length>=BUFFER_SIZE) break;
	}
	// printf("%s", buffer_add); 
	bzero(buffer, BUFFER_SIZE);
	char file_name[50] = "8.8.tar.gz";
	memcpy(buffer, "8.8.tar.gz", 10);
	write(s, buffer, BUFFER_SIZE);
	if((stream=fopen(buffer, "r"))==NULL) return;
 	//get offset
 	////////////////////
 	unsigned char buffer1[4];
 	bzero(buffer1, 0);
 	read(s, buffer1, 4);
 	long offset = (buffer1[0]<<24)+(buffer1[1]<<16)+(buffer1[2]<<8)+(buffer1[3]);
 	printf("offset:%ld\n", offset);
 	lseek(fileno(stream), (long)offset, SEEK_CUR);
	printf("ing...\n");
	for(;;){
		size = fread(buffer, sizeof(char), BUFFER_SIZE, stream);
		if(size <= 0){
			return;
		}
		write(s, buffer, size);
	}
	fclose(stream);
}