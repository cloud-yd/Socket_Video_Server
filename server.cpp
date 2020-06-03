#include "server.h"


SOCKET sockConn;
struct recvbuf data;

WinServer::WinServer(void)
{
}


WinServer::~WinServer(void)
{
	printf("œ˙ªŸ¡À \n");
}


int WinServer::socketConnect(int PORT)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0)
	{
		return -1;
	}
#if 1
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}
#endif

	SOCKET sockSrc = socket(AF_INET, SOCK_STREAM, 0);
	

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);

	if(bind(sockSrc, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR))  == SOCKET_ERROR)
	{
		printf("bind  error\n");
	}
	printf("sockSrc = %d \n", sockSrc);
	if (listen(sockSrc, 5) == SOCKET_ERROR)
	{
		printf("listen  error\n");
	}

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR_IN);

	assert(sockSrc != INVALID_SOCKET);

	sockConn = accept(sockSrc, (SOCKADDR*)&addrClient, &len);
	
	int nRecvBuf = 1024 * 1024 * 10;
	setsockopt(sockConn, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	return 0;
}


void WinServer::socketDisconnect(void)
{
	closesocket(sockConn);

}

int WinServer::receive(cv::Mat& image)
{
	cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));

	int needRecv = sizeof(recvbuf);
	int count = 0;

		for (int i = 0; i < 32; i++)
		{
			int pos = 0;
			int len0 = 0;

			while (pos < needRecv)
			{
				len0 = recv(sockConn, (char*)(&data) + pos, needRecv - pos, 0);
				if (len0 < 0)
				{
					printf("Server Recieve Data Failed!\n");
					return -1;
				}
				pos += len0;
			}

			count = count + data.flag;

			int num1 = IMG_HEIGHT / 32 * i;
			for (int j = 0; j < IMG_HEIGHT / 32; j++)
			{
				int num2 = j * IMG_WIDTH * 3;
				uchar* ucdata = img.ptr<uchar>(j + num1);
				for (int k = 0; k < IMG_WIDTH * 3; k++)
				{
					ucdata[k] = data.buf[num2 + k];
				}
			}

			if (data.flag == 2)
			{
				if (count == 33)
				{
					image = img;
					return 1;
					count = 0;
				}
				else
				{
					count = 0;
					i = 0;
				}
			}
		}
	
	return 0;
}
