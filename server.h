#pragma once

/* 基于OpenCV和Winsock的图像传输（接收）*/

#include <stdio.h>
#include <Winsock2.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cassert>

//using namespace std;
//using namespace cv;

#pragma warning(disable:4996)
#pragma comment(lib, "WS2_32") //链接到WS2_32.lib

//待传输图像默认大小为 640*480，可修改
#define IMG_WIDTH 640	// 需传输图像的宽
#define IMG_HEIGHT 480	// 需传输图像的高
//默认格式为CV_8UC3
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

	// 打开socket连接
	// params :	PORT	传输端口
	// return : -1		连接失败
	//			1		连接成功
	int socketConnect(int PORT);


	// 传输图像
	// params : image	待接收图像
	// return : -1		接收失败
	//			1		接收成功
	int receive(cv::Mat& image);


	// 断开socket连接
	void socketDisconnect(void);
};



