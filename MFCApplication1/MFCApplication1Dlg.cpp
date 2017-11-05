
// MFCApplication1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv/cv.h"

#include <iostream>
using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊
int sliderInit = 0;
IplImage* image_14;
IplImage* image_142;
IplImage* result;
IplImage *dest_3;
int x1, yy1, x2, y2, x3, y3, x4, y4;
int counter = 0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 對話方塊



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication1Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication1Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCApplication1Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMFCApplication1Dlg::OnBnClickedButton11)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 訊息處理常式

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO:  在此加入額外的初始設定
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	//create IplImage object to read the image file
	IplImage* image;
	image = cvLoadImage("./res/dog.bmp");
	if (image == NULL)
	{
		cout << "Could not find this file" << endl;
	}
	int height = image->height;
	int width = image->width;
	cout << "Height = " << height << endl;
	cout << "Width = " << width << endl;
	cvNamedWindow("Display1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Display1", image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvDestroyWindow("Dispaly1");

}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	IplImage* image;
	IplImage *clone_image;
	//open the file
	image = cvLoadImage("./res/color.png");
	if (image == NULL)
	{
		cout << "Could not find this file" << endl;
		return;
	}
	int height = image->height;
	int width = image->width;
	
	//set the information of other image 
	CvSize size = cvSize(width, height);
	clone_image = cvCreateImage(size, IPL_DEPTH_8U, 3);

	//read the RGB and transform to BRG
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j< image->width; j++)
		{
			//read the RGB value by CvScalar
			CvScalar s ;
			//get the RGB data of the image which is relative to i,j coordinate
			s = cvGet2D(image, i, j);
			//rearrange the RGB value to BRG
			cvSet2D(clone_image, i, j, CV_RGB(s.val[0], s.val[2], s.val[1]));
		}
	}
	
	//display two frame 
	cvNamedWindow("Display2", CV_WINDOW_AUTOSIZE);
	cvShowImage("Display2", image);
	cvNamedWindow("Display3", CV_WINDOW_AUTOSIZE);
	cvShowImage("Display3", clone_image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvDestroyWindow("Dispaly2");
	cvReleaseImage(&clone_image);
	cvDestroyWindow("Dispaly3");
	
	


}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	IplImage* image;
	IplImage* clone;
	image = cvLoadImage("./res/dog.bmp");
	if (image == NULL)
	{
		cout << "Could not find this file" << endl;
	}
	int height = image->height;
	int width = image->width;
	CvSize size = cvSize(width, height);
	clone = cvCreateImage(size, IPL_DEPTH_8U, 3);
	//flip the image
	cvFlip(image, clone, 1);

	cvNamedWindow("Display4", CV_WINDOW_AUTOSIZE);
	cvShowImage("Display4", image);
	cvNamedWindow("Display5", CV_WINDOW_AUTOSIZE);
	cvShowImage("Display5", clone);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&clone);
	cvDestroyWindow("Dispaly4");
	cvDestroyWindow("Dispaly5");

	
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	
	image_14 = cvLoadImage("./res/dog.bmp");
	if (image_14 == NULL)
	{
		cout << "Could not find this file" << endl;
	}
	int height = image_14->height;
	int width = image_14->width;
	CvSize size = cvSize(width, height);
	image_142 = cvCreateImage(size, IPL_DEPTH_8U, 3);
	result = cvCreateImage(size, IPL_DEPTH_8U, 3);
	cvFlip(image_14, image_142, 1);

	cvNamedWindow("Display6", CV_WINDOW_AUTOSIZE);
	
	cvCreateTrackbar("bar", "Display6", &sliderInit, 100, onTrackbar);
	cvSetTrackbarPos("bar", "Display6", 100);
	
	onTrackbar(0);

	cvWaitKey(0);
	cvReleaseImage(&image_14);
	cvReleaseImage(&image_142);
	cvReleaseImage(&result);
	cvDestroyWindow("Dispaly6");
}
static void onTrackbar(int pos)
{
	
	double alpha = (double)sliderInit / 100;
	double beta = 1.0 - alpha;
	//cout << alpha << "  " << beta << endl;
	cvAddWeighted(image_14, alpha, image_142, beta, 0.0 , result);
	cvShowImage("Display6", result);
}

void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	IplImage* color;
	IplImage* gray;
	IplImage* Canny;
	color = cvLoadImage("./res/eye.jpg");
	if (color == NULL)
	{
		cout << "Could not find this file" << endl;
	}
	int height = color->height;
	int width = color->width;
	CvSize size = cvSize(width, height);

	//create one channel image object for gray and canny
	gray = cvCreateImage(size, IPL_DEPTH_8U, 1);
	Canny = cvCreateImage(size, IPL_DEPTH_8U, 1);
	if (gray == NULL)
	{
		cout << "error" << endl;
		return;
	}
	cvNamedWindow("Display7", CV_WINDOW_AUTOSIZE);
	//convert color RGB to gray
	cvCvtColor(color, gray, CV_BGR2GRAY);
	
	cvThreshold(gray, Canny, 70,255 , 0);
	//do canny filter
	cvCanny(Canny, Canny, 50, 120 , 3);
	cvShowImage("Display7", gray);
	cvShowImage("Display8", Canny);
	cvWaitKey(0);
	cvReleaseImage(&gray);
	cvDestroyWindow("Dispaly7");
	cvReleaseImage(&Canny);
	cvDestroyWindow("Dispaly8");
}


void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	IplImage* color;
	IplImage* gray;
	IplImage* res;
	color = cvLoadImage("./res/eye.jpg");
	if (color == NULL)
	{
		cout << "Could not find this file" << endl;
	}
	int height = color->height;
	int width = color->width;
	CvSize size = cvSize(width, height);
	CvMemStorage* store = cvCreateMemStorage(0);
	//create one channel image for gray picture
	gray = cvCreateImage(size, IPL_DEPTH_8U, 1);
	res  = cvCreateImage(size, IPL_DEPTH_8U, 3);
	if (gray == NULL)
	{
		cout << "error" << endl;
		return;
	}
	cvNamedWindow("Display9", CV_WINDOW_AUTOSIZE);
	//convert RGB to Gray
	cvCvtColor(color, gray, CV_BGR2GRAY);
	cvThreshold(gray, gray, 70, 255, 0);
	cvCanny(gray, gray, 50, 100, 3);
	//merge the gray 1 channel image to 3 channel image
	cvMerge(gray, gray, gray, NULL, res);
	//find the circles
	CvSeq* circles = cvHoughCircles(gray, store,
		CV_HOUGH_GRADIENT, 2,width/4 ,80,100);
	//draw the circle
	for (int i = 0; i < circles->total; i++ )
	{
		float *p = (float*)cvGetSeqElem(circles, i);
		CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
		cvCircle(res, pt, cvRound(p[2]),
			CV_RGB(255, 0, 0), 2, 8, 0);
	}
	

	cvShowImage("Display9", res);
	cvWaitKey(0);
	cvReleaseImage(&gray);
	cvReleaseImage(&res);
	cvDestroyWindow("Dispaly9");
}


void CMFCApplication1Dlg::OnBnClickedButton7()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	IplImage* image;
	IplImage* gray;
	IplImage* dest_x,*dest_y;
	CvScalar x,y;
	int sobel_x[3][3] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	int sobel_y[3][3] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	image = cvLoadImage("./res/chessboard.bmp");
	if (image == NULL)
	{
		cout << "Could not find this file" << endl;
		return;
	}
	int height = image->height;
	int width = image->width;
	gray = cvCreateImage(cvSize(width, height),IPL_DEPTH_8U,1);
	dest_x = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	dest_y = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	
	cvCvtColor(image, gray, CV_BGR2GRAY);
	//calculate x and y axis sobel filter
	for (int i = 1; i < height - 1; i ++ )
	{
		for (int j = 1; j < width - 1; j ++ )
		{
			int sum_x = 0;
			int sum_y = 0;
			int a = 0, b = 0;
			for (int p = 0; p < 3; p++)
			{
				for (int q = 0; q < 3; q++)
				{
					x = cvGet2D(gray, i+ p -1 , j + q -1 );
					sum_x += (int)x.val[0] * sobel_x[ q ][ p ];
					sum_y += (int)x.val[0] * sobel_y[ q ][ p ];
				}
			}
			//reduce noise
			sum_x = abs(sum_x);
			sum_x = (sum_x > 255) ? 255 : sum_x;
			sum_x = (sum_x < 150) ? 0 : sum_x;
			//reduce noise
			sum_y = abs(sum_y);
			sum_y = (sum_y > 255) ? 255 : sum_y;
			sum_y = (sum_y < 150) ? 0 : sum_y;

			//push the result into IplImage
			x.val[0] = sum_x;
			y.val[0] = sum_y;
		    cvSet2D(dest_x, i, j, x);
			cvSet2D(dest_y, i, j, y);
		}
	}
	//render the result
	cvNamedWindow("Display10", CV_WINDOW_AUTOSIZE);
	cvShowImage("Display10", dest_x);
	cvNamedWindow("Display11", CV_WINDOW_AUTOSIZE);
	cvShowImage("Display11", dest_y);
	cvWaitKey(0);
	cvReleaseImage(&dest_x);
	cvDestroyWindow("Dispaly10");
	cvReleaseImage(&dest_y);
	cvDestroyWindow("Dispaly11");
}


void CMFCApplication1Dlg::OnBnClickedButton9()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	IplImage* image;
	image = cvLoadImage("./res/QrCode.jpg");
	if (image == NULL)
	{
		cout << "Could not find this file" << endl;
		return;
	}
	int height = image->height;
	int width = image->width;
		
	
	cvNamedWindow("Display12", CV_WINDOW_AUTOSIZE);
	
	setMouseCallback("Display12", onMouse, image);
	cvShowImage("Display12", image);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&dest_3);
	cvDestroyWindow("Dispaly12");
	cvDestroyWindow("Dispaly13");

}
void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cout << "x : " << x << endl;
		cout << "y : " << y << endl;
		counter++;
		//record the mouse click position
		switch (counter){
			case 1 :
				x1 = x;
				yy1 = y;
				break;
			case 2:
				x2 = x;
				y2 = y;
				break;
			case 3:
				x3 = x;
				y3 = y;
				break;
			case 4:
				x4 = x;
				y4 = y;
				break;
			default:
				break;
		}
	}
	//if click four times, then get the subframe to transform the QRCode
	if (counter == 4)
	{
		int left , right;
		int top, bottom;
		CvPoint2D32f srcQuad[4], dstQuad[4];
		CvMat* warp_matrix = cvCreateMat(3, 3, CV_32F);
		IplImage* image = (IplImage*)param;
		IplImage* dst;
		left = ( x1 < x4 ) ? x1 : x4;
		right = ( x2 > x3 ) ? x2 : x3;
		top = ( yy1 < y2 ) ? yy1 : y2;
		bottom = ( y3 > y4 ) ? y3 : y4;
		dest_3 = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 3);
		for (int i = top; i < bottom; i++)
		{
			for (int j = left; j < right; j++)
			{
				CvScalar s;
				s = cvGet2D(image, i, j);
				cvSet2D(dest_3, i, j, s);
			}
		}
		//dst = cvCloneImage(dest_3);
		//dst->origin = dest_3->origin;
		//cvZero(dst);
		dst = cvCreateImage(cvSize(right, right), IPL_DEPTH_8U, 3);
		//set the params of warp Perspective thransformation
		srcQuad[0].x = x1; //src Top left
		srcQuad[0].y = yy1;
		srcQuad[1].x = x2; //src Top right
		srcQuad[1].y = y2;
		srcQuad[2].x = x4; //src Bottom left
		srcQuad[2].y = y4;
		srcQuad[3].x = x3; //src Bot right
		srcQuad[3].y = y3;

		dstQuad[0].x = 0; //dst Top left
		dstQuad[0].y = 0;
		dstQuad[1].x = right; //dst Top right
		dstQuad[1].y = 0;
		dstQuad[2].x = 0; //dst Bottom left
		dstQuad[2].y = right;
		dstQuad[3].x = right; //dst Bot right
		dstQuad[3].y = right;
		
		cvGetPerspectiveTransform(
			srcQuad,
			dstQuad,
			warp_matrix
		);

		cvWarpPerspective(dest_3, dst, warp_matrix);

		counter = 0;
		cvNamedWindow("Display13", CV_WINDOW_AUTOSIZE);
		cvShowImage("Display13", dst);	
		cvReleaseImage(&dst);
		cvDestroyWindow("Dispaly13");
	}
	
}

void CMFCApplication1Dlg::OnBnClickedButton10()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	IplImage* image;
	IplImage* threshold;
	image = cvLoadImage("./res/shoes.jpg");
	if (!image)
	{
		cout << "Cannot find this file" << endl;
		return;
	}

	threshold = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U,1);
	cvCvtColor(image, threshold, CV_BGR2GRAY);

	cvThreshold(threshold, threshold, 150, 240, CV_THRESH_BINARY);
	
	cvNamedWindow("Display14", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Global Threshold", CV_WINDOW_AUTOSIZE);
	cvShowImage("Display14", image);
	cvShowImage("Global Threshold", threshold);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&threshold);
	cvDestroyWindow("Dispaly14");
	cvDestroyWindow("Dispaly15");
}


void CMFCApplication1Dlg::OnBnClickedButton11()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	IplImage* image;
	IplImage* gray;
	IplImage* threshold;
	IplImage* guassian;
	IplImage* mean;
	image = cvLoadImage("./res/shoes.jpg");
	if (!image)
	{
		cout << "Cannot find this file" << endl;
		return;
	}
	gray = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	//do local threshold 
	threshold = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	//do guassian smooth
	guassian = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	//do median smooth
	mean = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	cvCvtColor(image, gray, CV_BGR2GRAY);
	
	cvAdaptiveThreshold(gray, threshold, 200, 0, CV_THRESH_BINARY, 501,-10);

	cvSmooth(threshold, guassian, CV_GAUSSIAN, 5 , 5);

	cvSmooth(guassian, mean, CV_MEDIAN, 5);
	cvNamedWindow("Origin", 0);
	cvResizeWindow("Origin", 800, 600);
	cvNamedWindow("Local Threshold", 0);
	cvResizeWindow("Local Threshold", 800, 600);
	cvNamedWindow("Guassian", 0);
	cvResizeWindow("Guassian", 800, 600);
	cvNamedWindow("Median", 0);
	cvResizeWindow("Median", 800, 600);
	cvShowImage("Origin", image);
	cvShowImage("Local Threshold", threshold);
	cvShowImage("Guassian", guassian);
	cvShowImage("Median", mean);
	cvWaitKey(0);
	cvReleaseImage(&image);
	cvReleaseImage(&threshold);
	cvReleaseImage(&guassian);
	cvDestroyWindow("Origin");
	cvDestroyWindow("Local Threshold");
	cvDestroyWindow("Guassian");
	cvDestroyWindow("Median");
}
