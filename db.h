#ifndef USER_H
#define USER_H

#include "user.h"

int create_db(char **line, User **db, int *pti);
int select2(char *line, char *newBuffer, User **db, int *pti,int *size);
void tolowercase(char *tt);
void free_all(User **db, int *i);

#endif
