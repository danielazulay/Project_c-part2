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
    char buffer[MAX_LEN] = {0};
    char newBuffer[MAX_LEN] = {0};
    int n;
    int new_sock = (int)args;

    n = recv(new_sock, buffer, MAX_LEN, 0);
    if (n < 0)
    {
        perror("Server error receiving data");
        goto exit;
    }
    buffer[n] = '\0';

    printf("Server received: %s\n", buffer);
    char *vr[] = {"select", "set", "print", "exit"};
    char str2[20];

    for (int i = 0; i < 4; i++)
    {
        if (strstr(buffer, vr[i]))
        {
            strcpy(str2, vr[i]);
            break;
        }
    }

    if (!strcmp(str2, "select"))
    {

        sel(buffer, newBuffer, &db, &pti);
    }
    else if (strstr(str2, "set"))
    {
        int size = 0;
        set(buffer, newBuffer, &db, &pti, &size);
    }
    else if (!strcmp(buffer, "print"))
    {

        int sizei = 0;
        for (int i = 0; i < pti; i++)
        {

            int x = snprintf(newBuffer + sizei, 1024, "First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", db[i].firstName, db[i].lastName, db[i].birth, db[i].idNumber, db[i].phone, db[i].debt, db[i].debt_date);

            sizei += x;
        }
    }
    else if (!strcmp(buffer, "exit"))
    {
        goto exit;
    }

    n = send(new_sock, newBuffer, strlen(newBuffer), 0);
    if (n < 0)
    {
        perror("Server error sending data");
        goto exit;
    }
exit:

    close(new_sock);
    return NULL;
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

    FILE *file = fopen("arquivo.csv", "r");

    if (!file)
    {
        printf("Error: file %s does not exist.\n", argv[1]);
        return 1;
    }

    int size = 0;

    while (fgets(line, sizeof(line), file))
    {
        check_data(line, dbbuffer, &db, &pti, &size);
    }
    printf("%s", dbbuffer);

    fclose(file);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    for (int i = 0; i < pti; i++)
    {

        printf("First Name: %s Last Name: %s birth: %s Id Number: %d Phonne Number: %d Debt: %.2f Debt Date: %s \n", db[i].firstName, db[i].lastName, db[i].birth, db[i].idNumber, db[i].phone, db[i].debt, db[i].debt_date);
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

    if (listen(sockfd, 5) < 0)
    {
        perror("Error listenning");
        return 1;
    }

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