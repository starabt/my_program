#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "RSA.h"
#define ll long long
using namespace std;
int llllen(const char *test)
{
    printf("strlen:%d\n",strlen(test) );
    printf("sizeof%d\n",sizeof(test) );
    return 0;
}
const char a[]="1234567890";
const char b[]={0,1,2,3,4,5};
char c[20];


int main(){
    unsigned int i;
for(i=0;i<sizeof(b);i++)
{
    c[i]=b[i];
}
    c[i]='\0';
    llllen(a);
    llllen(b);
    printf("astrlen:%d\n",strlen(a) );
    printf("asizeof%d\n",sizeof(a) );
    printf("bstrlen:%d\n",strlen(b) );
    printf("bsizeof%d\n",sizeof(b) );
    printf("cstrlen:%d\n",strlen(c) );
    printf("csizeof%d\n",sizeof(c) );
    return 0;
}

