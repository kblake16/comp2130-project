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
#include <pthread.h>

#define BUF_SIZE	2048
#define LISTEN_PORT	60001

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
    int status = 1;

    char *text;

    char * func[3]= {"AVERAGE","SUM","RANGE"};
    char * grid[NUM_RANGE][NUM_RANGE];
    char letterVal[10][2] = {{'1','1'},{'A','1'},{'B','2'},{'C','3'},{'D','4'},{'E','5'},{'F','6'},{'G','7'},{'H','8'},{'I','9'}};

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


    char * spreadSheet()
    {
        char numS[3];
        int numI;
        static char sheet[BUF_SIZE];
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
    
        for(int i = 0; i < 10; i++)
        {
            if(letterVal[i][0] == cUp)
            {
                num = letterVal[i][1] - '0';
            }
        }
        return num;
    }

    int checkInput(char * c)
    {
        char cellLet = c[0];
        char cellNum = c[1];

        int check = 1;

        if(strlen(c) == 2 && isalpha(cellLet) != 0 && isalnum(cellNum) != 0 && isalpha(cellNum) == 0)
        {
            int num1 = getLetterInt(cellLet);
            int num2 = cellNum -'0';
            if(num1 <= 9 && num2 <= 9 && num1 >= 1 && num2 >= 1)
            {
                check = 0;
            }
        }

        return check;
    }

    int checkDirection(int x1, int y1, int x2, int y2)
    {
        int num = 1;

        if((x1 < x2 || x2 < x1) && y1 == y2)
        {
            num = 0;
        }
        else if (x1 == x2 && (y1 < y2 || y2 < y1))
        {
            num = 0;
        }
        return num;
    }


    // check if sell contains an integer
    int checkCell(int x, int y)
    {
        int num = 1;

        if (isalnum(grid[x][y]) != 0 && isalpha(grid[x][y]) == 0)
        {
            num = 0;
        }

        return num;
    }

    int average(int x1, int y1, int x2 , int y2)
    {
        int count = 0;
        int avg = 0;

        for (j = 0; j < NUM_RANGE; j++)
        {
            for (k = 0; k < NUM_RANGE; k++)
            {
                if (checkCell(j,k) == 0 )
                {
                    
                }
            }
        }

        return avg;
    }

    //Create Messages
    char * menu()
    {
        char * send = "\nEnter a Cell Example:a1 [Type 'shutdown' at any time to exit]!105";
        return send;
    }

    char * value(char* cell)
    {
        strcat(cell,":Funtion\n");
        strcat(cell,"=AVERAGE(cell1,cell2) - returns the average value from cell1 to cell2\n");
        strcat(cell,"=SUM(cell1,cell2) - returns the cumulative total fri cell1 to cell2\n");
        strcat(cell,"=RANGE(cell1,cell2) - return the difference between the largest and in the smallest value from cell1 to cell2\n");
        strcat(cell,"**NB Functions must be typed in all caps\n");
        strcat(cell,"Enter a text, value or function!125");
        return cell;
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

    void processMessage(int s, char msg[BUF_SIZE])
    {
         if (strstr(msg,"shutdown"))
        {
            bytes_sent = send(s,"quit",BUF_SIZE,0);
            pthread_exit(NULL);
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

            if(checkInput(msg) == 0)
            {
                printf("Cell: %s\n", msg);
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
            strtok(msg,"!");
            //printf("Val: %s",msg);

            char tempMsg[100];

            strcpy(tempMsg,msg);

            char * cell = strtok(tempMsg,":");
            int let = getLetterInt(cell[0]);
            int num = cell[1] - '0';

            
            char temp[100];
            int count = 0;

            for(int i = 3; msg[i] != '\0'; i++)
            {
                temp[count] = msg[i];
                count++;
            }

            printf("Msg: %s Cell: %s",temp,cell);

            if(strstr(msg,"=AVERAGE("))
            {
                char * temp = strtok(msg,",");
                char * get;

                /*
                //get first cell
                sprintf(get,"%c",temp[-2]);
                char * r1;
                strcpy(r1,get);
                sprintf(get,"%c",temp[-1]);
                strcat(r1,get);
                
                //get second cell
                temp = strtok(msg,")");
                sprintf(get,"%c",temp[-2]);
                char * r2;
                strcpy(r2,get);
                sprintf(get,"%c",temp[-1]);
                strcat(r2,get);
                */
                
                /*char * cells[] = splitFunction(msg);
                char * r1,r2; 
                strcpy(r1,cells[0]);
                strcpy(r2,cells[1]);*/

                char * r1 = "a1";
                char * r2 = "a2";

                //printf("R1: %s R2: %s",r1,r2);

                if (checkDirection(getLetterInt(r1[0]),r1[1]-'0',getLetterInt(r2[0]), r2[1]-'0') == 0)
                {
                    printf("Correct direction");
                    placeOnSheet(let,num,"a");
                    msg = spreadSheet();
                    strcat(msg,menu());
                    bytes_sent = send(s,msg,BUF_SIZE,0);
                }
                else
                {
                    printf("Not Value: %s\n",msg);
                    strcpy(msg,cell);
                    strcat(msg,":[VALUE ERROR] ReEnter a text, value or function!125");
                    bytes_sent = send(s,msg,BUF_SIZE,0);
                }
                
            }
            else if(strstr(msg,"=SUM("))
            {

            }
            else if(strstr(msg,"=RANGE("))
            {

            }
            else
            {
                placeOnSheet(let,num,temp);
                msg = spreadSheet();
                strcat(msg,menu());
                bytes_sent = send(s,msg,BUF_SIZE,0);
            }
        }
        else
        {
            printf("Received: %s\n",buf);
            msg = spreadSheet();
            strcat(msg,menu());
            bytes_sent = send(s,msg,BUF_SIZE,0);
        }
    }

    void * handleConnection(void * pclient){
    
    	int client= *((int*)pclient);
		free(pclient);
    
        while (status == 1)
        {
            bytes_received=recv(client,buf,BUF_SIZE,0);
            buf[bytes_received]=0;

            processMessage(client,buf);
        }
    } 

    getNewSpreadSheet();

    while (1){

		/* get new socket to receive data on */
		/* It extracts the first connection request from the  */
		/* listening socket  */
		//Connecting 
        printf("Waiting for connection\n");
		addr_size=sizeof(recv_addr);
		sock_recv=accept(sock_listen, (struct sockaddr *) &recv_addr, &addr_size);
		if (recv<0){
			printf("connection failed");
		}

        printf("Connected\n");
			
		//use of thread to allow for mutliclient
		pthread_t t;
		int *pclient = malloc(sizeof(int));
		*pclient = sock_recv;
		pthread_create(&t,NULL,handleConnection,pclient);

    }

    close(sock_recv);
    close(sock_listen);
}
