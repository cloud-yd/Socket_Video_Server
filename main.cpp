/*图像接收*/
#include "server.h"

#if 1
int socketConnect(int PORT)
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

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}

	SOCKET sockSrc = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(PORT);
	bind(sockSrc, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	listen(sockSrc, 5);

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	printf("开始等待客户端连接 。。。 \n");
	SOCKET sockConn = accept(sockSrc, (SOCKADDR*)&addrClient, &len);
	printf("客户端连接！！！！！！\n");

	int nRecvBuf = 1024 * 1024 * 10;
	setsockopt(sockConn, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	return 0;
}

#endif
#if 1
int main(int argc, char** argv)
{
	WinServer socketMat;

	socketMat.socketConnect(6000);
	//socketConnect(6000);
	

	cv::namedWindow("video", cv::WINDOW_AUTOSIZE);
	cv::Mat image;
	int i = 0;
	while (1)
	{
		//i++;
		if (socketMat.receive(image) > 0)
		{
			cv::imshow("video", image);
			cv::waitKey(30);
		}
		else
			std::cout << "no image" << std::endl;
	}
	socketMat.socketDisconnect();
	cv::destroyAllWindows();

	return 0;
}
#endif
