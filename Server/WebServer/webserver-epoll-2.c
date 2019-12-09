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
int read_descriptors[1000];
// Function designed for chat between client and server. 
void func(int connfd, char action, int epollfd) 
{ 
    char responseHeader[512]=\
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
    int writeL = 0;
    int readBytes;
    sleep(3);
    switch(action)
    {
	case 'r':
		ret = read(connfd, buff, sizeof(buff)); 
		buff[ret] = 0;
		path[0] = '.';
		for(i = 1; i < 512; i++)
			path[i] = '\0';
		strncpy(&path[1], &buff[4], strchr(&buff[4], ' ') - &buff[4]);
		printf("From client:\n%s\n", buff); 
		responseHeader[9] = '2';
		responseHeader[11] = '0';
	    	fd = open(path,O_RDONLY);
	    	if(fd == -1)
	    	{
			printf("Failed to open file!\n");
			responseHeader[9] = '4';
	    		responseHeader[11] = '4';
			strcpy(&responseHeader[strlen(responseHeader)], notFound);
			ret = write(connfd, responseHeader, strlen(responseHeader));
			close(connfd);
		}
		else
	    	{
			sleep(3);
			if(strlen(path) == 2 && path[1] == '/')
			{
				strcpy(&responseHeader[strlen(responseHeader)], homePage);
				ret = write(connfd, responseHeader, strlen(responseHeader));
				close(connfd);
			}
			else
			{
				ret = write(connfd, responseHeader, strlen(responseHeader));
				read_descriptors[connfd] = fd;
			}
		
		}
		break;
	case 'w':
		ret = read(read_descriptors[connfd], buff, sizeof(buff));
		writeL = ret;
		if(writeL > 0)
		{
			
			ret = write(connfd, buff, writeL);
		}
		else
		{
			struct epoll_event event;
			event.data.fd = connfd;
			epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, &event);
			close(read_descriptors[connfd]);			
			close(connfd);
		}
	    	break;
	}
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
    int i, connfd, sockfd, epollfd, len, nfds, evs, evfd;
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
	epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev);
	// Function for chatting between client and server
	sleep(3);
	nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
	printf("%d\n", nfds);
	if (nfds == -1) {
		perror("epoll_wait");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < nfds; ++i) {
		printf("%d-%d\n",i,events[i].data.fd); 
		evfd = events[i].data.fd;
		evs=events[i].events;
		if (evfd == sockfd) {
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
		        /*func(connfd); */
		} else {
			/*do_use_fd(events[i].data.fd);*/
			if(evs & EPOLLIN) {
				func(evfd, 'r', 0);
				struct epoll_event event;
				event.data.fd = evfd;
				event.events = EPOLLOUT;
				epoll_ctl(epollfd, EPOLL_CTL_MOD, evfd, &event);
			}
			if(evs & EPOLLOUT) {
				func(evfd, 'w', epollfd);
			}
		}
	}
    }
    // After chatting close the socket 
    close(sockfd); 
    close(epollfd);
}
