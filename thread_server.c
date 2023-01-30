#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "user.h"
#include "query.h"
#include "validate.h"
#define MAX_LEN 1024

int pti = 0;
User *db;

void *conn_handler(void *args)
{
    char buffer[MAX_LEN];
    char newBuffer[MAX_LEN];
    int n;
    int new_sock = (int)args;
    

    n = recv(new_sock, buffer, MAX_LEN, 0);
    if (n < 0)
    {
        perror("Server error receiving data");
        goto exit;
    }
    buffer[n] = '\0';
    if (!strstr(buffer, "select"))
    {
       
        sel(buffer, newBuffer);
    }
    else if (!strstr(buffer, "set"))
    {
        set(buffer, newBuffer);
    }
   /*  else if (strstr(buffer, "print"))
    {    
      
        for(int i=1;i<pti;i++){
        snprintf(newBuffer, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", db[i].firstName, db[i].lastName, db[i].birth, db[i].idNumber, db[i].phone, db[i].debt, db[i].debt_date);
   
        } */
        
     


    printf("Server received: %s\n", newBuffer);


 n = send(new_sock, newBuffer, strlen(newBuffer), 0);
     if (n < 0)
    {
        perror("Server error sending data");
        goto exit;
    }

exit:
    close(new_sock);
    return 0;
}

int main(int argc, char **argv)
{
    char line[100];
    char dbbuffer[MAX_LEN];
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    if (argc < 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Error: file %s does not exist.\n", argv[1]);
        return 1;
    }

    while (fgets(line, sizeof(line), file))
    {
        check_data(line, dbbuffer, &db, pti);
    }


    fclose(file);

    /* Create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    /* Bind the socket to a specific port */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error binding socket");
        return 1;
    }

    if (listen(sockfd, 1) < 0)
    {
        perror("Error listenning");
        return 1;
    }

    char line[100];
    FILE *file = fopen("arquivo.csv", "r");
    if (file)
    {
        while (fgets(line, sizeof(line), file))
        {
            check_data(line, dbbuffer,&db,pti);
        }
    }

    fclose(file);

    /* Receive data from clients */
    while (1)
    {
        pthread_t tid;
        int new_sock = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
        if (new_sock < 0)
        {
            perror("accept failed");
            return 1;
        }

        pthread_create(&tid, NULL, conn_handler, (void *)new_sock);
        pthread_join(tid, NULL);
    }

    return 0;
}
