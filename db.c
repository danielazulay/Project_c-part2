#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"

int insert_duplicate(User *user, User **db, int *pti);
int insert_new(User *user, User **db, int *pti);
int insert_db(User **db, int *pti);
int compare_dates(char *value, char *date, char *comp);


int create_db(char **line, User **db, int *pti)
{
  User user;

  char *value = strtok(*line, ";");
  int col = 0;

  while (value)
  {

    if (col == 0)
    {
      user.firstName = strdup(value);
    }

    if (col == 1)
    {
      user.lastName = strdup(value);
    }
    if (col == 2)
    {
      user.birth = strdup(value);
    }

    if (col == 3)
    {
      user.idNumber = atoi(value);
    }

    if (col == 4)
    {
      user.phone = atoi(value);
    }
    if (col == 5)
    {
      user.debt = atof(value);
    }
    if (col == 6)
    {
      user.debt_date = strdup(value);
    }

    value = strtok(NULL, "; ");
    col++;
  }
  if (*pti == 0)
  {
    (*db) = malloc(sizeof(User));
    (*db)[*pti] = user;

    (*pti)++;
  }
  else if (insert_duplicate(&user, db, pti))
  {
    insert_db(db,pti);
    insert_new(&user, db, pti);
    (*pti)++;
  }

  return 0;
}

int insert_duplicate(User *user, User **db, int *pti)
{

  for (int j = 0; j < *pti; j++)
  {

    if ((*db)[j].idNumber == user->idNumber)
    {
      (*db)[j].debt += user->debt;

      return 0;
    }
  }
  return 1;
}

int insert_new(User *user, User **db, int *pti)
{
  int j;

  for (j = 0; j < *pti; j++)
  {

    if ((*db)[j].debt < user->debt)
    {

      User aux = (*db)[j];
      (*db)[j] = *user;
      *user = aux;
    }
  }

  (*db)[*pti] = *user;

  return 0;
}

int insert_db(User **db, int *pti)
{
  int x = *pti + 1;
  *db = realloc((*db), x * sizeof(User));

  if (!*db)
  {
    printf("Error on realloc");
  }
  return 0;
}

void free_all(User **db, int *i)
{

  for (int k = 0; k < *i; k++)
  {

    free((*db)[k].firstName);
    free((*db)[k].lastName);
    free((*db)[k].birth);
    free((*db)[k].debt_date);
  }
  free(*db);
  puts("");
  printf("---memory freed---\n");
  puts("");
};

int select2(char *line, char *newBuffer, User **db, int *pti)
{
  char variable[50];
  char comp[50];
  char value[50];

  int col = 0;
  char *val = strtok(line, ";");
  int x;
  int size =0;

  while (val)
  {
    if (col == 0)
    {
      strcpy(variable, val);
    }
    if (col == 1)
    {

      strcpy(comp, val);
    }

    if (col == 2)
    {
      strcpy(value, val);
    }

    val = strtok(NULL, "; ");
    col++;
  }

  if (!strcmp("birth", variable) && (!strcmp(">", comp) || !strcmp("<", comp)))
  {
    int flag = 0;

    
    for (int k = 0; k < *pti; k++)
    {

      if (compare_dates(value, (*db)[k].birth, comp))
      {
        flag = 1;
       x= snprintf(newBuffer+size, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
      size+=x;
      }
    }
    if (flag == 0)
     x=  snprintf(newBuffer+size, 1024, "%s %s %s not found \n", variable, comp, value);
        size+=x;
  }
  else if (!strcmp("debtdate", variable) && (!strcmp(">", comp) || !strcmp("<", comp)))
  {

    int flag = 0;

    
    for (int k = 0; k < *pti; k++)
    {

      if (compare_dates(value, (*db)[k].debt_date, comp))
      {
        
        flag = 1;
        x =snprintf(newBuffer+size, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
      size+=x;
      }
    }
    if (flag == 0)
    {

     x=  snprintf(newBuffer+size, 1024, "%s %s %s not found \n", variable, comp, value);
       size+=x;
    }
  }
  else if (!strcmp("firstname", variable) && !strcmp("=", comp))
  {
    int flag = 0;


    for (int k = 0; k < *pti; k++)
    {

      if (!strcmp((*db)[k].firstName, value))
      {
        flag = 1;

     x=   snprintf(newBuffer+size, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
       size+=x;
      }
    }
    if (flag == 0)
    {

      x= snprintf(newBuffer+size, 1024, "%s %s %s not found \n", variable, comp, value);
         size+=x;
    }
  }
  else if (!strcmp("lastname", variable))
  {
    int flag = 0;
  
    
    for (int k = 0; k < *pti; k++)
    {

      if (!strcmp((*db)[k].lastName, value))
      {
        flag = 1;
     x=    snprintf(newBuffer+size, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
       size+=x;
      }
    }
    if (flag == 0)
     x=  snprintf(newBuffer+size, 1024, "%s %s %s not found \n", variable, comp, value);
       size+=x;
  }
  else if (!strcmp("debt", variable))
  {

    if (!strcmp("=", comp))
    {
      int flag = 0;
   
    
      for (int k = 0; k < *pti; k++)
      {
        if ((*db)[k].debt == atoi(value))
        {
          flag = 1;
       x=    snprintf(newBuffer+size, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
           size+=x;
        }
      }
      if (flag == 0)
     x=    snprintf(newBuffer+size, 1024, "%s %s %s not found \n", variable, comp, value);
           size+=x;
    }
    else if (!strcmp("<", comp))
    {
      int flag = 0;
   
    
      for (int k = 0; k < *pti; k++)
      {
        if ((*db)[k].debt < atoi(value))
        {
          flag = 1;
      x=     snprintf(newBuffer+size, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
        size+=x;
        }
      }
      if (flag == 0)
       x=  snprintf(newBuffer+size, 1024, "%s %s %s not found \n", variable, comp, value);
            size+=x;
    }
    else if (!strcmp(">", comp))
    {
      int flag = 0;
  
    
      for (int k = 0; k < *pti; k++)
      {
        if ((*db)[k].debt > atoi(value))
        {
          flag = 1;
        x=   snprintf(newBuffer+size, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
             size+=x;
        }
      }
      if (flag == 0)
        x= snprintf(newBuffer+size, 1024, "%s %s %s not found \n", variable, comp, value);
              size+=x;
    }
    else if (!strcmp(">=", comp))
    {
      int flag = 0;
      
      for (int k = 0; k < *pti; k++)
      {
        if ((*db)[k].debt > atoi(value))
        {
          flag = 1;
      x=     snprintf(newBuffer+size, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
         size+=x;
        }
      }
      if (flag == 0)
      x=   snprintf(newBuffer+size, 1024, "%s %s %s not found \n", variable, comp, value);
            size+=x;
    }
    else if (!strcmp("<=", comp))
    {
      int flag = 0;
      for (int k = 0; k < *pti; k++)
      {
        if ((*db)[k].debt <= atoi(value))
        {
          flag = 1;
       x=    snprintf(newBuffer, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", (*db)[k].firstName, (*db)[k].lastName, (*db)[k].birth, (*db)[k].idNumber, (*db)[k].phone, (*db)[k].debt, (*db)[k].debt_date);
        }
      }
      if (flag == 0)
      x=   snprintf(newBuffer, 1024, "%s %s %s not found \n", variable, comp, value);
    }
  }
  return 0;
}

int compare_dates(char *value, char *date, char *comp)
{
  char valuedate[10];
  strcpy(valuedate, value);
  for (int j = 0; j < 10; j++)
  {
    if (!strcmp("<", comp))
    {
      if (date[j] > valuedate[j])
      {
        return 0;
      }
      else if (date[j] < valuedate[j])
      {
        return 1;
      }
    }
    if (!strcmp(">", comp))
    {
      if (date[j] < valuedate[j])
      {
        return 0;
      }
      else if (date[j] > valuedate[j])
      {
        return 1;
      }
    }
  }
  return 0;
}
