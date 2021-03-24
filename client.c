/**Group Members:
Kayla Blake     620096888
Name            ID no.
Name            ID no.*/

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAX 80
#define SA struct sockaddr

void func(int s)
{
    char buff[MAX];
    int n;

    for(;;)
    {
        bzero(buff, sizeof(buff));
        printf("Enter the string: ");
        n = 0;

        while ((buff[n++] = getchar()) != '\n')
            ;
        
        write(s, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(s, buff, sizeof(buff));
        printf("From Server: %s", buff);
        if((strncmp(buff, "exit", 4)) == 0)
        {
            printf("Exit Client \n");
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    //Get PORT from command line
    /**
    if (argc != 3)
    {
        printf('Please supply a server port');
        exit()
    }
    */

    printf("Client \n");

    int s, conn;
    struct sockaddr_in servaddr, client;

    //create socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("Could not create socket\n");
        exit(0);
    }

    printf("Socket Created \n");

    bzero(&servaddr, sizeof(servaddr)); // not sure what this does

    // assign IP and PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    //Bind socket
    if (connect(s, (SA*)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection Failed\n");
        exit(0);
    }

    printf("Client connected to Server \n");
    
    func(s);

    close(s);
    printf("Close connection socket");
    return 0;
}