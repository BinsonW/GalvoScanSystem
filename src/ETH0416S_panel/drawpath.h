#include "StdAfx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h> 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>


using namespace std;
using namespace cv;

struct datastruct {
	Mat& img;
	vector<Point>& pxy;
};
void on_mouse(int event, int x, int y, int flags, void* a);
void drawpath(vector<Point>& pxy);
