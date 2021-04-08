/**
Group Members:
Kayla Blake         620096888
Antoneel Thomspon   620122831
Labu Beckford       620111107
*/

#include <stdio.h>
#include <sys/types.h>	/* system type defintions */
#include <sys/socket.h>	/* network system functions */
#include <netinet/in.h>	/* protocol & struct definitions */
#include <stdlib.h>	/* exit() warnings */
#include <string.h>	/* memset warnings */
#include <unistd.h>
#include <ctype.h>

#define BUF_SIZE	1024
#define LISTEN_PORT	60000

int main(int argc, char *argv[])
{
    int	sock_listen,sock_recv,send_len;
    struct sockaddr_in	my_addr,recv_addr;
    int i,addr_size,bytes_received, bytes_sent;
    int	incoming_len;
    struct sockaddr	remote_addr;
    int	recv_msg_size;
    char buf[BUF_SIZE];
    int const NUM_RANGE = 9;
    int k,j;
<<<<<<< HEAD
    char text[80];

    char * grid[NUM_RANGE][NUM_RANGE];
=======
    char *text;

    char * func[3]= {"AVERAGE","SUM","RANGE"};
    char * grid[NUM_RANGE][NUM_RANGE];
    char letterVal[9][2] = {{'A','0'},{'B','1'},{'C','2'},{'D','3'},{'E','4'},{'F','5'},{'G','6'},{'H','7'},{'I','8'}};
>>>>>>> main

    void getNewSpreadSheet()
    {
        for (j=0; j < NUM_RANGE; j++)
        {
            for (k=0; k < NUM_RANGE; k++)
            {
                grid[k][j]="   ";
            }
        }
        return;
    }

    char * sheet = (char *) malloc(1);

    char * spreadSheet()
    {
        char numS[3];
        int numI;
        char * const NLINE = "    A    B    C    D    E    F    G    H    I";
        char * const HLINE = "  +----+----+----+----+----+----+----+----+----+";
        char * const VLINE = "  |    |    |    |    |    |    |    |    |    |";

        //printf("%s\n",NLINE);
        strcpy(sheet,NLINE);
        strcat(sheet,"\n");

        //printf("%s\n",HLINE);
        strcat(sheet,HLINE);
        strcat(sheet,"\n");

        for (j = 0; j < NUM_RANGE; j++)
        {  
            //printf("%s\n",VLINE);
            strcat(sheet,VLINE);
            strcat(sheet,"\n");

            //printf("%d ",j+1);
            numI = j+1;
            sprintf(numS,"%d ",numI);
            strcat(sheet,numS);

            for (k = 0; k < NUM_RANGE; k++)
            {  
                if(strcmp(grid[k][j],"   ") == 0)
                {
                    //printf("| %s",grid[k][j]);
                    strcat(sheet,"| ");
                    strcat(sheet,grid[k][j]);
                }
                else
                {
                    //printf("| %s  ",grid[k][j]);
                    strcat(sheet,"| ");
                    strcat(sheet,grid[k][j]);
                    strcat(sheet,"  ");
                }
            }
            //printf("%s","|");
            strcat(sheet,"|");

            //printf("\n");
            strcat(sheet,"\n");

            //printf("%s\n",VLINE);
            strcat(sheet,VLINE);
            strcat(sheet,"\n");
<<<<<<< HEAD

            //printf("%s\n",HLINE);
            strcat(sheet,HLINE);
            strcat(sheet,"\n");
        }
        return sheet;
    }

=======

            //printf("%s\n",HLINE);
            strcat(sheet,HLINE);
            strcat(sheet,"\n");
        }
        return sheet;
    }

>>>>>>> main
    printf("SpreadSheet Server\n");

    /* create socket for listening */
    sock_listen=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_listen < 0)
    {
        printf("socket() failed\n");
        exit(0);
    }

    printf("Socket Created\n");

    /* make local address structure */
    memset(&my_addr, 0, sizeof (my_addr));	/* zero out structure */
    my_addr.sin_family = AF_INET;	/* address family */
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);  /* current machine IP */
    my_addr.sin_port = htons((unsigned short)LISTEN_PORT);

     /* bind socket to the local address */
    i=bind(sock_listen, (struct sockaddr *) &my_addr, sizeof (my_addr));
    if (i < 0)
    {
        printf("bind() failed\n");
        exit(0);
    }
    
    printf("Socket Binded\n");

    /* listen ... */
    i=listen(sock_listen, 5);
    if (i < 0){
        printf("listen() failed\n");
        exit(0);
    }
    
    printf("Socket now listening...\n");

    /* get new socket to receive data on */
    /* It extracts the first connection request from the  */
    /* listening socket  */
    addr_size=sizeof(recv_addr);
    sock_recv=accept(sock_listen, (struct sockaddr *) &recv_addr, &addr_size);

    printf("Connected\n");

    getNewSpreadSheet();

    while (1){
<<<<<<< HEAD
        printf("%s",spreadSheet());
=======
        //send
        text = spreadSheet();
        send_len = strlen(text);
        bytes_sent = send(sock_recv,text,send_len,0);

        //recieve
>>>>>>> main
        bytes_received=recv(sock_recv,buf,BUF_SIZE,0);
        buf[bytes_received]=0;
        printf("Received: %s\n",buf);
        if (strcmp(buf,"shutdown") == 0)
            break;
<<<<<<< HEAD
    }
=======
        
        //alpha numeric
        printf("Buf len");
        if (strlen(buf)==2 && isalpha(buf[0]) && isalnum(buf[1] && !(isalpha(buf[1]))))
            //then enter value
            printf("Cell: %s\n",buf);

        //function AVERAGE SUM RANGE
        //if ()

    }

>>>>>>> main
    free(sheet);
    close(sock_recv);
    close(sock_listen);
}
