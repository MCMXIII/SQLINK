#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#define MAX 4096
#define PORT 8080 
#define SA struct sockaddr 

const char* response=\
"HTTP/1.1 200 OK\n" \
"Date: Mon, 27 Jul 2009 12:28:53 GMT\n" \
"Server: Apache/2.2.14 (Win32)\n" \
"Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n" \
"Content-Type: text/html\n" \
"Connection: Closed\n" \
"\n" \
"<html>\n" \
"<body>\n" \
"<h1>Welcome to my website</h1>\n" \
"<p>my website is bla bla bla</p>\n" \
"</body>\n" \
"</html>\n";

void func(int connectionfd) 
{ 
    char buff[MAX]; 
    int ret=read(connectionfd, buff, sizeof(buff));
    printf("Data I got from client follows...\n");
    buff[ret]=0;
    printf("%s", buff);
    ret=write(connectionfd, response, strlen(response));
    printf("ret is %d, strlen is %ld\n", ret, strlen(response));
    close(connectionfd);
} 
  
int main() 
{ 
    int sockfd, connfd; 
    socklen_t len;
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 

    while(1) {
	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	printf("server acccept the client...\n"); 
	// Function for chatting between client and server 
	func(connfd); 
    }
    // After chatting close the socket 
    close(sockfd); 
} 

