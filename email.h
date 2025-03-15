#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>


typedef unsigned int8 int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;


struct s_email {
    int8 src[64];
    int8 dst[64];
    int8 id[64];
    int8 subject[128];
    int8 *domain;
    int8 data[];
    
};
typedef struct s_email Email;

struct s_server {
    int8 domain[64];
    int8 server[64];
    int32 ip;
};
typedef struct s_server Server;

#define $8 (int8 *)
#define $6 (int16)
#define $2 (int32)
#define $4 (int64)
#define $c (int8 *)
#define $i (int)

#define log(f, args...)  printf(f, args)


bool sendmail(Email*,Server*);
int main(int, int8**);
