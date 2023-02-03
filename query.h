#ifndef QUERY_H
#define QUERY_H

#include "user.h"


int set(char *value,char * newBuffer,User**db,int *pti,int *size);
int sel(char *line,char * newBuffer,User**db,int *pti,int *size);


#endif
