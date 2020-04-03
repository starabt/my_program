#ifndef _CLIENTFD_H_
#define _CLIENTFD_H_

#include "global.h"
#include <stdio.h>
#include <pthread.h>

void add_new_clientfd(int);
void rm_clientfd(int);
int find_client_fd(int);
void printf_clientfd();

#endif