/**
Group Members:
Kayla Blake         620096888
Antoneel Thompson   620122831
Labu Beckford       620111107
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


#define BUF_SIZE	2048
#define	SERVER_IP	"127.0.0.1"
#define SERVER_PORT	60000

int main(int argc, char *argv[]){
    int	sock_send;
    struct sockaddr_in	addr_send;
    int	i;
    char text[80],buf[BUF_SIZE];
    int	send_len,bytes_sent, bytes_received;
    int status;

    //Create Message
    char * option(char op[BUF_SIZE])
    {
        strcat(op,"!115");
        return op;
    }

    char * value(char * cell, char * val)
    {
        strcat(cell,":");
        strcat(cell,val);
        strcat(cell,"!150");

        return cell;
    }

    void processMessage(int s, char msg[BUF_SIZE])
    {
        if (strstr(msg,"!quit"))
        {
            status = -1;
        }
        if(strstr(msg,"!105"))
        {
            printf("%s",strtok(msg,"!"));
            printf("\nSend? ");
            scanf("%s",msg);
            bytes_sent=send(s,option(msg),BUF_SIZE,0);
        }
        if(strstr(msg,"!125"))
        {
            printf("%s",strtok(msg,"!"));
            printf("\nSend? ");
            scanf("%s",text);
            bytes_sent=send(s,value(strtok(msg,":"),text),BUF_SIZE,0);
        }
    }

        /* create socket for sending data */
    sock_send=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_send < 0){
        printf("socket() failed\n");
        exit(0);
    }

        /* create socket address structure to connect to */
    memset(&addr_send, 0, sizeof (addr_send)); /* zero out structure */
    addr_send.sin_family = AF_INET; /* address family */
    addr_send.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr_send.sin_port = htons((unsigned short)SERVER_PORT);

        /* connect to the server */
    i=connect(sock_send, (struct sockaddr *) &addr_send, sizeof (addr_send));
    if (i < 0){
        printf("connect() failed\n");
        exit(0);
    }

    strcpy(buf,"connected!100");
        bytes_sent=send(sock_send,buf,BUF_SIZE,0);

    status = 1;
    while (status == 1)
    {
        bytes_received=recv(sock_send,buf,BUF_SIZE,0);
        buf[bytes_received]=0;

        processMessage(sock_send,buf);

    }

    close(sock_send);
}
