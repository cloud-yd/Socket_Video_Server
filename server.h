#pragma once

/* ����OpenCV��Winsock��ͼ���䣨���գ�*/

#include <stdio.h>
#include <Winsock2.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cassert>

//using namespace std;
//using namespace cv;

#pragma warning(disable:4996)
#pragma comment(lib, "WS2_32") //���ӵ�WS2_32.lib

//������ͼ��Ĭ�ϴ�СΪ 640*480�����޸�
#define IMG_WIDTH 640	// �贫��ͼ��Ŀ�
#define IMG_HEIGHT 480	// �贫��ͼ��ĸ�
//Ĭ�ϸ�ʽΪCV_8UC3
#define BUFFER_SIZE IMG_WIDTH*IMG_HEIGHT*3/32

struct recvbuf
{
	char buf[BUFFER_SIZE];
	int flag;
};


class WinServer
{
public:
	WinServer(void);
	~WinServer(void);

private:


public:

	// ��socket����
	// params :	PORT	����˿�
	// return : -1		����ʧ��
	//			1		���ӳɹ�
	int socketConnect(int PORT);


	// ����ͼ��
	// params : image	������ͼ��
	// return : -1		����ʧ��
	//			1		���ճɹ�
	int receive(cv::Mat& image);


	// �Ͽ�socket����
	void socketDisconnect(void);
};



