/*
 * EpollTest.cpp
 *
 *  Created on: Mar 13, 2014
 *      Author: From network  http://blog.csdn.net/sparkliang/article/details/4770655
 */




#include "Define.h"
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace std;

#define MAX_EVENTS 1024

struct myevent_s
{
	int fd;
	void (*call_back)(int fd, int events, void *arg);
	int events;
	void *arg;
	int status;  // 1: in epoll wait list, 0 not in
	char buff[128]; // recv data buffer
	int len;
//	int s_offset;
//	long last_active; // last active time
};

void EventSet(myevent_s *ev, int fd, void (*call_back)(int, int, void*), void *arg)
{
	ev->fd = fd;
	ev->call_back = call_back;
	ev->events = 0;
	ev->status = 0;
	bzero(ev->buff, sizeof(ev->buff));
//	ev->s_offset = 0;
	ev->len = 0;
//	ev->last_active = time(NULL);
}


// add/mod an event to epoll
void EventAdd(int epollFd, int events, myevent_s *ev)
{
	struct epoll_event epv = {0, {0}};
	int op;
	epv.data.ptr = ev;
	epv.events = ev->events = events;

	if(ev->status == 1)
	{
		op = EPOLL_CTL_MOD;
	}
	else
	{
		op = EPOLL_CTL_ADD;
		ev->status = 1;
	}

	if(epoll_ctl(epollFd, op, ev->fd, &epv) < 0)
	{
		cout << "EventAdd failed" << endl;
	}
	else
	{
		cout << "EventAdd OK" << endl;
	}
}


// delete an event from epoll
void EventDel(int epollFd, myevent_s *ev)
{
	struct epoll_event epv = {0, {0}};
	if(ev->status != 1)
	{
		return;
	}

	epv.data.ptr = ev;
	ev->status = 0;

	epoll_ctl(epollFd, EPOLL_CTL_DEL, ev->fd, &epv);
}



int g_epollFd;
myevent_s g_Events[MAX_EVENTS+1];    // g_Events[MAX_EVENTS] is used by listen fd

void RecvData(int fd, int events, void *args);
void SendData(int fd, int events, void *args);


// accept new connections from clients
void AcceptConn(int fd, int events, void *arg)
{
	struct sockaddr_in sin;
	socklen_t len = sizeof(struct sockaddr_in);
	int nfd, i;

	if((nfd = accept(fd, (struct sockaddr*)&sin, &len)) == -1)
	{
		cout << "accept error" << endl;
		return;
	}

	do
	{
		for(i=0; i<MAX_EVENTS; i++)
		{
			if(g_Events[i].status == 0)
			{
				break;
			}
		}
		if(i == MAX_EVENTS)
		{
			cout << "max connecton limit" << endl;
			close(nfd);
			break;
		}

		int iret = 0;
		if((iret = fcntl(nfd, F_SETFL, O_NONBLOCK)) < 0)
		{
			cout << "fcntl nonblocking failed" << endl;
			break;
		}

		// add a read event for receive data
		EventSet(&g_Events[i], nfd, RecvData, &g_Events[i]);
		EventAdd(g_epollFd, EPOLLIN, &g_Events[i]);
	}while(0);
}

void RecvData(int fd, int events, void *arg)
{
	struct myevent_s *ev = (struct myevent_s*)arg;
	int len;

	len = recv(fd, ev->buff+ev->len, sizeof(ev->buff)-1-ev->len, 0);
	EventDel(g_epollFd, ev);

	if(len > 0)
	{
		ev->len += len;
		ev->buff[len] = '\0';

		printf("C[%d]: %s \n", fd, ev->buff);

		EventSet(ev, fd, SendData, ev);
		EventAdd(g_epollFd, EPOLLOUT, ev);
	}
	else if(len == 0)
	{
		close(ev->fd);
		cout << "closed gracefully" << endl;
	}
	else
	{
		close(ev->fd);
		cout << "recv error" << endl;
	}
}

void SendData(int fd, int events, void *arg)
{
	struct myevent_s *ev = (struct myevent_s*)arg;
	int len;

//	len = send(fd, ev->buff + ev->s_offset, ev->len - ev->s_offset, 0);
	len = send(fd, ev->buff, ev->len, 0);
	if(len > 0)
	{
		EventSet(ev, fd, RecvData, ev);
		EventAdd(g_epollFd, EPOLLIN, ev);
//		ev->s_offset += len;
//		if(ev->s_offset == ev->len)
//		{
////			EventDel(g_epollFd, ev);
//			EventSet(ev, fd, RecvData, ev);
//			EventAdd(g_epollFd, EPOLLIN, ev);
//		}
	}
	else
	{
		close(ev->fd);
		EventDel(g_epollFd, ev);
		printf("send error");
	}
}


void InitListenSocket(int epollFd, short port)
{
	int listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenFd == -1)
	{
		cout << "socket() error" << endl;
		return;
	}

	fcntl(listenFd, F_SETFL, O_NONBLOCK);

	EventSet(&g_Events[MAX_EVENTS], listenFd, AcceptConn, &g_Events);
	EventAdd(epollFd, EPOLLIN, &g_Events[MAX_EVENTS]);

	sockaddr_in sin;
	bzero(&sin, sizeof(sin));

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	bind(listenFd, (const sockaddr*)&sin, sizeof(sin));

	listen(listenFd, 5);
}


void epoll_test()
{
	unsigned int port = 3333;

	g_epollFd = epoll_create(MAX_EVENTS);
	if(g_epollFd <= 0)
	{
		printf("epoll_create() error");
		return;
	}

	InitListenSocket(g_epollFd, port);

	struct epoll_event events[MAX_EVENTS];

	while(1)
	{
		int fds = epoll_wait(g_epollFd, events, MAX_EVENTS, 1000);
		if(fds < 0)
		{
			cout << "epoll_wait() error" << endl;
			break;
		}

		for(int i=0; i<fds; i++)
		{
			myevent_s *ev = (struct myevent_s*)events[i].data.ptr;

			if((events[i].events & EPOLLIN) && (ev->events & EPOLLIN))
			{
				ev->call_back(ev->fd, events[i].events, ev->arg);
			}
			if((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT))
			{
				ev->call_back(ev->fd, events[i].events, ev->arg);
			}
		}
	}

	close(g_epollFd);

	cout << endl << "end of epoll_test()" << endl;
}


