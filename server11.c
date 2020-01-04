/**
 *	Jarrett Tang
 *	server11.c
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT    10010 
#define MAXLINE 1024 
  
int main() 
{ 
    int udpSocket, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size, client_addr_size;
    int i;

    /*Create UDP socket*/
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

    /*Configure settings in address struct*/
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    // serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_addr.s_addr = AI_PASSIVE;
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*Bind socket with address struct*/
    bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    /*Initialize size variable to be used later on*/
    addr_size = sizeof serverStorage;

    while(1)
    {
        memset(buffer, '\0', strlen(buffer));
        printf("Waiting for signal...\n");

        /* Try to receive any incoming UDP datagram. Address and port of 
        requesting client will be stored on serverStorage variable */
        nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
        printf("Client: %s\n", buffer);

        /*Send message back to client, using serverStorage as the address*/
        sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
    }
  return 0; 
} 