#include "StdAfx.h"
#include "drawpath.h"


void on_mouse(int event, int x, int y, int flags, void* a)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号  
{
	static Point pre_pt = { -1, -1 };//初始坐标  
	datastruct b = *(datastruct*)a;
	Mat& img = b.img;
	vector<Point>& pxy = b.pxy;

	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
	{
		sprintf_s(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		pxy.push_back(pre_pt);
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//划圆  
		imshow("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//左键没有按下的情况下鼠标移动的处理函数  
	{
		//sprintf_s(temp, "(%d,%d)", x, y);
		//cur_pt = Point(x, y);
		//pxy[k] = pre_pt;
		//k++;
		//imshow("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//左键按下时，鼠标移动，则在图像上划圆
	{
		sprintf_s(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		pxy.push_back(pre_pt);
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//划圆   
		imshow("img", img);
	}
	else if (event == CV_EVENT_LBUTTONUP)//左键松开，将在图像上划圆  
	{
		sprintf_s(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		pxy.push_back(pre_pt);
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//划圆 
		imshow("img", img);
	}
}
void drawpath(vector<Point>& pxy)
{
	Mat M(600, 600, CV_8UC1);//创建一个高400，宽200的灰度图的Mat对象

	for (int i = 0;i < M.rows;i++)        //遍历每一行每一列并设置其像素值
	{
		for (int j = 0;j < M.cols;j++)
		{
			M.at<uchar>(i, j) = 100;
		}
	}
	//org = imread("2.jpg");

	namedWindow("img");//定义一个img窗口  
	datastruct a = { M,pxy };
	setMouseCallback("img", on_mouse, &a);//调用回调函数  
	imshow("img", M);
	cv::waitKey(0);
	destroyWindow("img");
}

