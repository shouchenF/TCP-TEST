#pragma once

#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>			//sleep定时器的头文件
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h> 

struct tcpThreadData
{
	int* sock;
	double* sendnum;
	double* revnum;
};

class tcpuart
{
public:
	tcpuart(void);
	~tcpuart();
	int openUartPort(char* strptr, uint16_t port);
	ssize_t writeUartPort(void* senddat, size_t len);
	int closeUartPort(void);
	double revnum;
	double sendnum;
private:
	tcpThreadData threaddata;
	int sock;
	pthread_t id;
	static void* tcp_rev_thread(void* p);
};

