#include "reactor_t.h"
#include <iostream>
#include <string>
#include <iterator>
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

using namespace std;
const char* Reactor_t::notFound = "<html>\n" \
				"<body>\n" \
				"<h1>404: Error - not found</h1>\n" \
				"<p>The requested page was not found!</p>\n" \
				"</body>\n" \
				"</html>\n";
const char* Reactor_t::homePage = "<html>\n" \
				"<body>\n" \
				"<h1>Home page</h1>\n" \
				"<p>Enter a relevant address of a page</p>\n" \
				"</body>\n" \
				"</html>\n";
Reactor_t* Reactor_t::instance = 0;
void Reactor_t::init(const int& mevents)
{
	instance = new Reactor_t(mevents);
	instance->sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (instance->sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&instance->servaddr, sizeof(instance->servaddr)); 
    instance->epollfd = epoll_create1(0);
    if (instance->epollfd == -1) {
	perror("epoll_create1");
	exit(EXIT_FAILURE);
    }
    instance->ev.events = EPOLLIN;
    instance->ev.data.fd = instance->sockfd;
    if (epoll_ctl(instance->epollfd, EPOLL_CTL_ADD, instance->sockfd, &instance->ev) == -1) {
	perror("epoll_ctl: listen_sock");
	exit(EXIT_FAILURE);
    }
    // assign IP, PORT 
    instance->servaddr.sin_family = AF_INET; 
    instance->servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    instance->servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(instance->sockfd, (SA*)&instance->servaddr, sizeof(instance->servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(instance->sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
}
void Reactor_t::readReq(const int& rfd)
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
    ret = read(rfd, buff, sizeof(buff)); 
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
		ret = write(rfd, responseHeader, strlen(responseHeader));
		close(rfd);
	}
	else
    	{
		sleep(3);
		if(strlen(path) == 2 && path[1] == '/')
		{
			strcpy(&responseHeader[strlen(responseHeader)], homePage);
			ret = write(rfd, responseHeader, strlen(responseHeader));
			close(rfd);
		}
		else
		{
			ret = write(rfd, responseHeader, strlen(responseHeader));
			read_descriptors[rfd] = fd;
		}
	
	}
}
void Reactor_t::writeReq(const int& wfd)
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
    ret = read(read_descriptors[wfd], buff, sizeof(buff));
	writeL = ret;
	if(writeL > 0)
	{
		
		ret = write(wfd, buff, writeL);
	}
	else
	{
		struct epoll_event event;
		event.data.fd = wfd;
		epoll_ctl(instance->epollfd, EPOLL_CTL_DEL, wfd, &event);
		close(read_descriptors[wfd]);			
		close(wfd);
	}
}
void Reactor_t::run()
{
	struct epoll_event events[max_events];
	struct sockaddr_in cli; 
	int i, nfds, evs, evfd;
	unsigned int len = sizeof(cli);

	while(1) {
	// Accept the data packet from client and verification 
	/*connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	}*/
		epoll_ctl(instance->epollfd, EPOLL_CTL_ADD, instance->sockfd, &instance->ev);
		// Function for chatting between client and server
		sleep(3);
		nfds = epoll_wait(instance->epollfd, events, instance->max_events, -1);
		printf("%d\n", nfds);
		if (nfds == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < nfds; ++i) {
			printf("%d-%d\n",i,events[i].data.fd); 
			evfd = events[i].data.fd;
			evs=events[i].events;
			if (evfd == instance->sockfd) {
				printf("1...\n"); 
				instance->connfd = accept(instance->sockfd, (SA*)&cli, &len);
				if (instance->connfd < 0) { 
					printf("server acccept failed...\n"); 
					exit(0); 
				}
				printf("server acccept the client... %d\n", instance->connfd); 
				/*setnonblocking(connfd);*/
				instance->ev.events = EPOLLIN | EPOLLET;
				instance->ev.data.fd = instance->connfd;
				if (epoll_ctl(instance->epollfd, EPOLL_CTL_ADD, instance->connfd, &instance->ev) == -1) {
					perror("epoll_ctl: conn_sock");
					exit(EXIT_FAILURE);
				}
			        /*func(connfd); */
			} else {
				/*do_use_fd(events[i].data.fd);*/
				if(evs & EPOLLIN) {
					readReq(evfd);
					struct epoll_event event;
					event.data.fd = evfd;
					event.events = EPOLLOUT;
					epoll_ctl(instance->epollfd, EPOLL_CTL_MOD, evfd, &event);
				}
				if(evs & EPOLLOUT) {
					writeReq(evfd);
				}
			}
		}
    }
}