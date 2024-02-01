#include <stdio.h>
#include <unistd.h>			//sleep定时器的头文件
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h> 
#include <pthread.h>
#include "tcpuart.h"


/* 毫秒级 延时 */
void Sleep(int ms)
{
	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = ms * 1000; // 20 ms
	select(0, NULL, NULL, NULL, &delay);
}

int main(void)
{
	char senddat[16];
	int delaynum;
	tcpuart pt, pt1, pt2, pt3, pt4, pt5;

	senddat[0] = 0xAA;
	senddat[1] = 0x06;
	senddat[2] = 0x00;
	senddat[3] = 0x00;
	senddat[4] = 0x00;
	senddat[5] = 0x00;
	senddat[6] = 0x00;
	senddat[7] = 0x00;
	senddat[8] = 0x00;
	senddat[9] = 0x00;
	senddat[10] = 0x00;
	senddat[11] = 0x00;
	senddat[12] = 0x00;
	senddat[13] = 0x00;
	senddat[14] = 0x06;
	senddat[15] = 0x2F;

	pt.openUartPort("192.168.0.7", 23);
	pt1.openUartPort("192.168.0.7", 26);
	pt2.openUartPort("192.168.0.7", 29);
	pt3.openUartPort("192.168.0.7", 32);
	pt4.openUartPort("192.168.0.7", 35);
	pt5.openUartPort("192.168.0.7", 38);

	sleep(2);
	delaynum = 20;
	printf("test start ...6ch 10000byte delay = %dms\n",delaynum);

	while (1)
	{
		pt.writeUartPort(senddat, 16);
		pt1.writeUartPort(senddat, 16);
		pt2.writeUartPort(senddat, 16);
		pt3.writeUartPort(senddat, 16);
		pt4.writeUartPort(senddat, 16);
		pt5.writeUartPort(senddat, 16);

		Sleep(delaynum);
		if (pt.sendnum > 10000)
		{
			sleep(1);

			printf("\n");
			printf("main0 send rev :%4.0lf %4.0lf\n", pt.sendnum, pt.revnum);
			printf("main0 send-rev :%4.0lf\n", pt.sendnum - pt.revnum);
			printf("\n");
			pt.closeUartPort();

			printf("\n");
			printf("main1 send rev :%4.0lf %4.0lf\n", pt1.sendnum, pt1.revnum);
			printf("main1 send-rev :%4.0lf\n", pt1.sendnum - pt1.revnum);
			printf("\n");
			pt1.closeUartPort();

			printf("\n");
			printf("main2 send rev :%4.0lf %4.0lf\n", pt2.sendnum, pt2.revnum);
			printf("main2 send-rev :%4.0lf\n", pt2.sendnum - pt2.revnum);
			printf("\n");
			pt2.closeUartPort();

			printf("\n");
			printf("main3 send rev :%4.0lf %4.0lf\n", pt3.sendnum, pt3.revnum);
			printf("main3 send-rev :%4.0lf\n", pt3.sendnum - pt3.revnum);
			printf("\n");
			pt3.closeUartPort();

			printf("\n");
			printf("main4 send rev :%4.0lf %4.0lf\n", pt4.sendnum, pt4.revnum);
			printf("main4 send-rev :%4.0lf\n", pt4.sendnum - pt4.revnum);
			printf("\n");
			pt4.closeUartPort();

			printf("\n");
			printf("main5 send rev :%4.0lf %4.0lf\n", pt5.sendnum, pt5.revnum);
			printf("main5 send-rev :%4.0lf\n", pt5.sendnum - pt5.revnum);
			printf("\n");
			pt5.closeUartPort();

			_exit(0);
		}
	}
}
