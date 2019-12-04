#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <pthread.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#define MAX 4096
#define MAX_EVENTS 10
#define PORT 8080 
#define SA struct sockaddr 
const char* notFound = "<html>\n" \
"<body>\n" \
"<h1>404: Error - not found</h1>\n" \
"<p>The requested page was not found!</p>\n" \
"</body>\n" \
"</html>\n";
const char* homePage = "<html>\n" \
"<body>\n" \
"<h1>Home page</h1>\n" \
"<p>Enter a relevant address of a page</p>\n" \
"</body>\n" \
"</html>\n";
char* responseHeader=\
"HTTP/1.1 200 OK\n" \
"Date: Mon, 27 Jul 2009 12:28:53 GMT\n" \
"Server: Apache/2.2.14 (Win32)\n" \
"Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n" \
"Content-Type: text/html\n" \
"Connection: Closed\n" \
"\n";
const char* buffers_to_write[10];
int read_descriptors[10000];
int count_to_write[10];
char* outbuffer[4096];
// Function designed for chat between client and server. 
void func(int connfd) 
{ 
    char response[1048576]=\
    "HTTP/1.1 200 OK\n" \
    "Date: Mon, 27 Jul 2009 12:28:53 GMT\n" \
    "Server: Apache/2.2.14 (Win32)\n" \
    "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n" \
    "Content-Type: text/html\n" \
    "Connection: Closed\n" \
    "\n";
    char buff[MAX];
    char path[512];
    int ret; 
    int fd, i;
    int resSize = 0;
    int readBytes;
    /*sleep(30);*/
    ret = read(connfd, buff, sizeof(buff)); 
    buff[ret] = 0;
    path[0] = '.';
    for(i = 1; i < 512; i++)
	path[i] = '\0';
    strncpy(&path[1], &buff[4], strchr(&buff[4], ' ') - &buff[4]);
    printf("From client:\n%s\n", buff); 
    response[9] = '2';
    response[11] = '0';
    fd = open(path,O_RDONLY);
    if(fd == -1)
    {
	printf("Failed to open file!\n");
	response[9] = '4';
    	response[11] = '4';
	strcpy(&response[strlen(response)], notFound);
    }
    else
    {
	/*sleep(30);*/
	if(strlen(path) == 2 && path[1] == '/')
	{
		strcpy(&response[strlen(response)], homePage);
	}
	else
	{
        	resSize = strlen(response);
		/*printf("%d\n", resSize);*/
		readBytes=read(fd, &response[resSize], 1048576 - resSize);
        	resSize+=readBytes;
		/*printf("%d\n",readBytes);*/
	        response[resSize] = '\0';
		/*printf("%d\n", resSize);*/
		close(fd);
	}
    }
    ret = write(connfd, response, strlen(response));
    close(connfd);
        /*// if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } */
    /*} */
}  
// Driver function 
int main() 
{ 
    int i, connfd, sockfd, epollfd, len, nfds;
    struct sockaddr_in servaddr, cli; 
    struct epoll_event ev, events[MAX_EVENTS];
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
    epollfd = epoll_create1(0);
    if (epollfd == -1) {
	perror("epoll_create1");
	exit(EXIT_FAILURE);
    }
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
	perror("epoll_ctl: listen_sock");
	exit(EXIT_FAILURE);
    }
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
	/*connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	}*/
	
	// Function for chatting between client and server
	nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
	printf("%d\n", nfds);
	if (nfds == -1) {
		perror("epoll_wait");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < nfds; ++i) {
		printf("%d-%d\n",i,events[i].data.fd); 
		if (events[i].data.fd == sockfd) {
			printf("1...\n"); 
			connfd = accept(sockfd, (SA*)&cli, &len);
			if (connfd < 0) { 
				printf("server acccept failed...\n"); 
				exit(0); 
			}
			printf("server acccept the client... %d\n", connfd); 
			/*setnonblocking(connfd);*/
			ev.events = EPOLLIN | EPOLLET;
			ev.data.fd = connfd;
			if (epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &ev) == -1) {
				perror("epoll_ctl: conn_sock");
				exit(EXIT_FAILURE);
			}
			char buff[MAX];
			char path[512];
			int ret; 
			int j;
			int resSize = 0;
			int readBytes;
    /*sleep(30);*/
			ret = read(connfd, buff, sizeof(buff)); 
			buff[ret] = 0;
			path[0] = '.';
			for(i = 1; i < 512; i++)
			path[i] = '\0';
			strncpy(&path[1], &buff[4], strchr(&buff[4], ' ') - &buff[4]);
			printf("From client:\n%s\n", buff); 
			response[9] = '2';
			response[11] = '0';
			read_descriptors[fd] = open(path,O_RDONLY);
    if(fd == -1)
    {
	printf("Failed to open file!\n");
	response[9] = '4';
    	response[11] = '4';
	strcpy(&response[strlen(response)], notFound);
    }
    else
    {
	/*sleep(30);*/
	if(strlen(path) == 2 && path[1] == '/')
	{
		strcpy(&response[strlen(response)], homePage);
	}
	else
	{
        	resSize = strlen(response);
		/*printf("%d\n", resSize);*/
		readBytes=read(fd, &response[resSize], 1048576 - resSize);
        	resSize+=readBytes;
		/*printf("%d\n",readBytes);*/
	        response[resSize] = '\0';
		/*printf("%d\n", resSize);*/
		close(fd);
	}
    }
    ret = write(connfd, response, strlen(response));
    close(connfd);
		} else {
			/*do_use_fd(events[i].data.fd);*/
			printf("ssss\n"); 
		}
	}
    }
    // After chatting close the socket 
    close(sockfd); 
} 
