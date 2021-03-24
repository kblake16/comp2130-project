/**Group Members:
Kayla Blake     620096888
Name            ID no.
Name            ID no.*/

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#define PORT 8080
#define MAX 80
#define SA struct sockaddr

void func(int s)
{
    char buff[MAX];
    int n;

    for(;;)
    {
        bzero(buff, MAX);

        //Get message from client
        read(s, buff, sizeof(buff));
        
        //Print Client message
        printf("From client: %s\t To client: ",buff);
        bzero(buff,MAX);
        
        n =0;
        //Save server message
        while ((buff[n++] = getchar()) != '\n')
            ;
        
        //Send message to client
        write(s,buff,sizeof(buff));

        if (strncmp("exit",buff,4) == 0){
            printf("Exit Server \n");
            break;
        }

    }
}

int main(int argc, char const *argv[])
{
    //Get server PORT from command line
    /**
    if (argc != 3)
    {
        printf('Please supply a server port');
        exit()
    }
    */

    printf("Spreadsheet Server \n");

    int s, conn, len;
    struct sockaddr_in servaddr, client;

    //create socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("Could not create socket\n");
        exit(0);
    }

    printf("Socket Created\n");

    bzero(&servaddr, sizeof(servaddr)); // not sure what this does

    // assign HOST and PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    //Bind socket
    if ((bind(s, (SA*)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("Socket Bind Failed \n");
        exit(0);
    }

    printf("Socket Binded");

    //Listen
    if ((listen(s,5)) != 0)
    {
        printf("Listen Failed \n");
        exit(0);
    }

    printf("Socket now listening");

    len = sizeof(client);

    if (conn < 0){
        printf("Accept Connection Failed");
        exit(0);
    }

    printf("Connected by ");

    func(conn);

    close(s);
    printf("Close connection socket");
    return 0;
}