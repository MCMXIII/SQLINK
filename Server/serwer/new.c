#include<sys/types.h>
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
#define PORT 8080 
#define SA struct sockaddr 
int sockfd, nclients = 0; 
int active[100];
pthread_mutex_t nCDefender;
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
// Function designed for chat between client and server. 
void* func(void* tid) 
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
    int fd, i, connfd;
    int resSize = 0;
    int readBytes;
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
	printf("server acccept failed...\n"); 
	pthread_mutex_lock(&nCDefender);
	nclients--;
	active[*(int*)tid] = 0;
	pthread_mutex_unlock(&nCDefender);
	return NULL; 
    }
    ret = read(connfd, buff, sizeof(buff)); 
    buff[ret] = 0;
    path[0] = '.';
    for(i = 1; i < 512; i++)
	path[i] = '\0';
    strncpy(&path[1], &buff[4], strchr(&buff[4], ' ') - &buff[4]);
    printf("From client:\n%s\n%s\n", buff,path); 
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
	if(strlen(path) == 2 && path[1] == '/')
	{
		strcpy(&response[strlen(response)], homePage);
	}
	else
	{
        	resSize = strlen(response);
		printf("%d\n", resSize);
		readBytes=read(fd, &response[resSize], 1048576 - resSize);
        	resSize+=readBytes;
		printf("%d\n",readBytes);
	        response[resSize] = '\0';
		printf("%d\n", resSize);
		close(fd);
	}
    }
    ret = write(connfd, response, strlen(response));
    close(connfd);
    pthread_mutex_lock(&nCDefender);
    nclients--;
    active[*(int*)tid] = 0;
    pthread_mutex_unlock(&nCDefender);
        /*// if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } */
    /*} */
    return NULL;
} 
  
// Driver function 
int main() 
{ 
    pthread_t clients[100];
    int ids[100];
    int len, i;
    struct sockaddr_in servaddr, cli; 
    for(i = 0; i < 100; i++)
    {
	active[i] = 0;
	ids[i] = i;
    }
    // socket create and verification 
    pthread_mutex_init(&nCDefender, NULL);
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
	/*connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	}*/
	printf("server acccept the client...\n"); 
	// Function for chatting between client and server
	while(nclients == 100){}
	pthread_mutex_lock(&nCDefender);
	for(i = 0; i < 100; i++)
	{
		if(active[i] == 0)
		{
			nclients++;
			active[i] = 1;
			pthread_create(&clients[i], NULL, func, (void*)ids[i]);
			break;
		}
	}
	pthread_mutex_unlock(&nCDefender); 
    }
    // After chatting close the socket 
    close(sockfd); 
    pthread_mutex_destroy(&nCDefender);
} 

