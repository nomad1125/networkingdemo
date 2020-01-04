/**
 *  Jarrett Tang
 *  client12.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "10010" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// argv[1] = ip address
// argv[2] = c
// argv[3] = a
// argv[4] = b
int main(int argc, char *argv[])
{
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    char c[2];
    char a[4];
    char b[4];
    char temp[4];
    char M[10];
    char mark[] = ",";
    int lenS;

    if (argc < 5)
    {
        fprintf(stderr,"usage: missing important command components\n");
        exit(1);
    }
    
    memset(c, '\0', 1);
    c[0] = argv[2][0];
    // printf("%s\n", c);

    memset(temp, '\0', 4);
    lenS = strlen(argv[3]);
    for (int i = 3; i >= 0; i--)
    {
        lenS--;
        if (lenS < 0)
        {
            temp[i] = '0';
        }
        else
        {
            temp[i] = argv[3][lenS];
        }
    }
    a[0] = temp[1];
    a[1] = temp[2];
    a[2] = temp[3];
    // printf("%s\n", a);
    
    memset(temp, '\0', 4);
    lenS = strlen(argv[4]);
    for (int i = 3; i >= 0; i--)
    {
        lenS--;
        if (lenS < 0)
        {
            temp[i] = '0';
        }
        else
        {
            temp[i] = argv[4][lenS];
        }
    }
    b[0] = temp[1];
    b[1] = temp[2];
    b[2] = temp[3];
    // printf("%s\n", b);

    // message M
    memset(M, '\0', 10);
    memset(buf, '\0', MAXDATASIZE);
    strcat(M,c);
    strcat(M,a);
    strcat(M,b);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    if (send(sockfd, M, 9, 0) == -1)
    {
        perror("send");
    }

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("%s %s %s = %s\n",a,c,b,buf);

    close(sockfd);

    return 0;
}
