#include "tcpuart.h"

tcpuart::tcpuart(void)
{
	revnum = 0;
	sendnum = 0;

	threaddata.sock = &sock;
	threaddata.revnum = &revnum;
}

tcpuart::~tcpuart(void)
{
	close(sock);
}

void* tcpuart::tcp_rev_thread(void* p)
{
	char revdat[20];
	ssize_t ret;

	tcpThreadData threaddata = *(tcpThreadData*)p;

	while (1)
	{
		ret = read(*threaddata.sock, revdat, 16);
		if (ret > 0)
		{
// 			for (int i = 0; i < ret; i++)
// 			{
// 				printf("%02X \t", revdat[i]);
// 			}
// 			printf("\n");
			if (ret == 16)
			{
				if ((revdat[0] == 0xAA) && (revdat[15] == 0x2F))
				{
					*threaddata.revnum += (double)ret;
				}
			}
		}
		else if (ret < 0)
		{
			printf("tcp_rev_thread error %s(errno :%d)\n", strerror(errno), errno);
			pthread_exit(NULL);
		}

		usleep(100);
	}
}

int tcpuart::openUartPort(char* strptr,uint16_t port)
{
	int ret = 0;
	revnum = 0;

	sock = socket(AF_INET, SOCK_STREAM, 0);					//协议域，type socket种类，指定协议 0 = IPPROTO_IP 
	if (sock < 0)
	{
		printf("socket crteat fail\n");
		return -1;
	}

	struct sockaddr_in sever_addr;							//创建ip、端口结构体
	memset(&sever_addr, 0, sizeof(sever_addr));				//清空结构体
	sever_addr.sin_family = AF_INET;
	sever_addr.sin_addr.s_addr = inet_addr(strptr);			//服务器IP
	sever_addr.sin_port = htons(port);						//端口号

	if (connect(sock, (struct sockaddr*)&sever_addr, sizeof(sever_addr)) < 0)	//链接服务器
	{
		printf("socket error: %s(errno :%d)\n", strerror(errno), errno);
		return -2;
	}

	ret = pthread_create(&id, NULL, tcp_rev_thread, &threaddata);
	if (ret != 0) {
		printf("Create pthread error!\n");
		return -3;
	}

	return 0;
}

ssize_t tcpuart::writeUartPort(void* senddat,size_t len)
{
	ssize_t ret = 0;
	ret = write(sock, senddat, len);
	sendnum += (double)ret;
	return ret;
}

int tcpuart::closeUartPort(void)
{
	return close(sock);
}
