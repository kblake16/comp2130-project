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

#define BUF_SIZE	2048
#define LISTEN_PORT	60020

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
    int status;

    char *text;

    char * func[3]= {"AVERAGE","SUM","RANGE"};
    char * grid[NUM_RANGE][NUM_RANGE];
    char letterVal[9][2] = {{'A','1'},{'B','2'},{'C','3'},{'D','4'},{'E','5'},{'F','6'},{'G','7'},{'H','8'},{'I','9'}};

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

        strcpy(sheet,NLINE);
        strcat(sheet,"\n");

        strcat(sheet,HLINE);
        strcat(sheet,"\n");

        for (j = 0; j < NUM_RANGE; j++)
        {  
            strcat(sheet,VLINE);
            strcat(sheet,"\n");

            numI = j+1;
            sprintf(numS,"%d ",numI);
            strcat(sheet,numS);

            for (k = 0; k < NUM_RANGE; k++)
            {  
                if(strcmp(grid[k][j],"   ") == 0)
                {
                    strcat(sheet,"| ");
                    strcat(sheet,grid[k][j]);
                }
                else
                {
                    strcat(sheet,"| ");
                    strcat(sheet,grid[k][j]);
                    strcat(sheet,"  ");
                }
            }
            strcat(sheet,"|");

            strcat(sheet,"\n");

            strcat(sheet,VLINE);
            strcat(sheet,"\n");

            strcat(sheet,HLINE);
            strcat(sheet,"\n");
        }
        return sheet;
    }

    void placeOnSheet(int x, int y, char* c)
    {
        grid[x-1][y-1] = c;
        return;
    }

    int getLetterInt(char c)
    {
        int num;
        char cUp = toupper(c);
        for(int i = 0; i < 9; i++)
        {
            if(letterVal[i][0] == cUp)
            {
                num = letterVal[i][1] - '0';
            }
        }
        return num;
    }

    //Create Messages
    char * menu()
    {
        char * send = "\nEnter a Cell Example:a1 [Type 'shutdown' at any time to exit]!105";
        return send;
    }

    char * value(char* cell)
    {
        strcat(cell,":Enter the value!125");
        return cell;
    }

    // check if sell contains number or text
    void checkCell(int x, int y)
    {
        return;
    }


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

    void processMessage(int s, char msg[BUF_SIZE])
    {
         if (strstr(msg,"shutdown"))
        {
            bytes_sent = send(s,"!quit",BUF_SIZE,0);
            status = -1;
        }
        else if(strstr(msg,"!100"))
        {
            msg = spreadSheet();
            strcat(msg,menu());
            bytes_sent = send(s,msg,BUF_SIZE,0);
        }
        else if(strstr(msg,"!115"))
        {
            strcpy(msg,strtok(msg,"!"));

            char cellLet = msg[0];
            char cellNum = msg[1];

            if(strlen(msg) == 2 && isalpha(cellLet) != 0 && isalnum(cellNum) != 0 && isalpha(cellNum) == 0)
            {
                int num = cellNum - '0';
                //placeOnSheet(getLetterInt(cellLet),num,"T");
                printf("Cell: %c num: %d\n",cellLet,num);
                msg = value(msg);
                bytes_sent = send(s,msg,BUF_SIZE,0);
            }
            else
            {
                printf("Not Cell: %s\n",msg);
                msg = "Enter a cell range on the spread sheet!105";
                bytes_sent = send(s,msg,BUF_SIZE,0);
            }
        }
        else if(strstr(msg,"!150"))
        {
            strcpy(msg,strtok(msg,"!"));
            printf("Val: %s",msg);
        }
        else
        {
            printf("Received: %s\n",buf);
            msg = spreadSheet();
            strcat(msg,menu());
            bytes_sent = send(s,msg,BUF_SIZE,0);
        }
    }

    getNewSpreadSheet();
    status = 1;

    while (status == 1){
        //recieve
        bytes_received=recv(sock_recv,buf,BUF_SIZE,0);
        buf[bytes_received]=0;

        processMessage(sock_recv,buf);
    }

    free(sheet);
    close(sock_recv);
    close(sock_listen);
}
