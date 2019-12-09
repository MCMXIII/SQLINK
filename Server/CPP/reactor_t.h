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
#ifndef REACTOR_T_H
#define REACTOR_T_H
#define MAX 4096
#define PORT 8080 
#define SA struct sockaddr

	using namespace std;
		/*struct Compare {
  			const bool operator() (const float& a, const float& b) const {return a<b;}
		};*/
		class Reactor_t {
			public:
				~Reactor_t(){close(sockfd); close(epollfd);}
				void run();
				static Reactor_t* getInstance(){return Reactor_t::instance;}
				static void init(const int& mevents);
			private:
				Reactor_t(const int& mevents):max_events(mevents){}
				Reactor_t(const Reactor_t& other):max_events(0){}
				Reactor_t& operator=(const Reactor_t& other){return *this;}
				int connfd;
				int sockfd;
				int epollfd;
				int read_descriptors[1000];
				const int max_events;
				struct sockaddr_in servaddr;
				struct epoll_event ev;
				static const char* notFound;/* = "<html>\n" \
				"<body>\n" \
				"<h1>404: Error - not found</h1>\n" \
				"<p>The requested page was not found!</p>\n" \
				"</body>\n" \
				"</html>\n";*/
				static const char* homePage;/* = "<html>\n" \
				"<body>\n" \
				"<h1>Home page</h1>\n" \
				"<p>Enter a relevant address of a page</p>\n" \
				"</body>\n" \
				"</html>\n";*/
				static Reactor_t* instance;
				void readReq(const int& rfd);
				void writeReq(const int& wfd);
		};
#endif