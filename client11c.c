/**
 *	Jarrett Tang
 *	client11b.c
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <time.h>			// for clock_t, clock(), CLOCKS_PER_SEC
  
#define PORT    10010 
#define MAXLINE 1024 
  
// Driver code 
int main()
{
    int clientSocket, portNum, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char targetAddr[15];
    double rtt = 0.0;
    char ch_arr[10000][5];

    /*Making Array*/
    for (int i = 1; i <= 10000; i++)
    {
        sprintf(ch_arr[i], "%d", i);
    }

    /*Create UDP socket*/
    clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

    /*Configure settings in address struct*/
    printf("Please enter name of the echo server: \n");
    fgets(targetAddr,15,stdin);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(targetAddr);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*Initialize size variable to be used later on*/
    addr_size = sizeof serverAddr;

    /* Cool Stuff here */
    clock_t begin = clock();
    nBytes = strlen(buffer) + 1;

    for (int i = 1; i <= 10000; i++)
    {
        memset(buffer, '\0', strlen(buffer));
        strcpy(buffer, ch_arr[i]);

        /*Send message to server*/
        sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

        // Receive message from server.
        // should wait for return message.
        nBytes = recvfrom(clientSocket,buffer,1024,0,NULL,NULL);
        printf("Received from server: %s\n",buffer);
    }

    clock_t end = clock();
    rtt += (double)(end-begin) / CLOCKS_PER_SEC;
    printf("RTT: %f s\n", rtt);

	return 0;
}