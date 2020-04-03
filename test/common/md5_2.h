#ifndef MD5_H
#define MD5_H

typedef struct _MD5_CTX{  
	unsigned int count[2];
	unsigned int state[4];
	unsigned char buffer[64];
}MD5_CTX;

void MD5_Init(MD5_CTX *ctx);  
void MD5_Update(MD5_CTX *ctx, unsigned char *input, unsigned int len);
void MD5_Final(MD5_CTX *ctx, unsigned char digest[16]);
void MD5_Transform(unsigned int state[4], unsigned char block[64]);
void MD5_Encode(unsigned char *output, unsigned int *input, unsigned int len);
void MD5_Decode(unsigned int *output, unsigned char *input, unsigned int len);
void MD5_data(unsigned char *output, unsigned char *input, unsigned int len);

#endif