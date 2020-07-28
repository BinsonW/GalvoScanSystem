#include "StdAfx.h"
#include "drawpath.h"


void on_mouse(int event, int x, int y, int flags, void* a)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���  
{
	static Point pre_pt = { -1, -1 };//��ʼ����  
	datastruct b = *(datastruct*)a;
	Mat& img = b.img;
	vector<Point>& pxy = b.pxy;

	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN)//������£���ȡ��ʼ���꣬����ͼ���ϸõ㴦��Բ  
	{
		sprintf_s(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		pxy.push_back(pre_pt);
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//��Բ  
		imshow("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//���û�а��µ����������ƶ��Ĵ�����  
	{
		//sprintf_s(temp, "(%d,%d)", x, y);
		//cur_pt = Point(x, y);
		//pxy[k] = pre_pt;
		//k++;
		//imshow("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//�������ʱ������ƶ�������ͼ���ϻ�Բ
	{
		sprintf_s(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		pxy.push_back(pre_pt);
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//��Բ   
		imshow("img", img);
	}
	else if (event == CV_EVENT_LBUTTONUP)//����ɿ�������ͼ���ϻ�Բ  
	{
		sprintf_s(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		pxy.push_back(pre_pt);
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//��Բ 
		imshow("img", img);
	}
}
void drawpath(vector<Point>& pxy)
{
	Mat M(600, 600, CV_8UC1);//����һ����400����200�ĻҶ�ͼ��Mat����

	for (int i = 0;i < M.rows;i++)        //����ÿһ��ÿһ�в�����������ֵ
	{
		for (int j = 0;j < M.cols;j++)
		{
			M.at<uchar>(i, j) = 100;
		}
	}
	//org = imread("2.jpg");

	namedWindow("img");//����һ��img����  
	datastruct a = { M,pxy };
	setMouseCallback("img", on_mouse, &a);//���ûص�����  
	imshow("img", M);
	cv::waitKey(0);
	destroyWindow("img");
}

