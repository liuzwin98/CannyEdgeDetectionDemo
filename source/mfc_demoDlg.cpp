
// mfc_demoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "mfc_demo.h"
#include "mfc_demoDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;

CRect rect;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcdemoDlg 对话框



CmfcdemoDlg::CmfcdemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CmfcdemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CmfcdemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CmfcdemoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON5, &CmfcdemoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CmfcdemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CmfcdemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CmfcdemoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_GETDATA, &CmfcdemoDlg::OnBnClickedGetdata)
END_MESSAGE_MAP()


// CmfcdemoDlg 消息处理程序

BOOL CmfcdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// TODO: 在此添加额外的初始化代码
	CWnd  *pWnd1 = GetDlgItem(IDC_STATIC);//CWnd是MFC窗口类的基类,提供了微软基础类库中所有窗口类的基本功能。修改参数为窗口ID
	pWnd1->GetClientRect(&rect);//GetClientRect为获得控件相自身的坐标大小
	namedWindow("src", WINDOW_AUTOSIZE);//设置窗口名
	HWND hWndl = (HWND)cvGetWindowHandle("src");//hWnd 表示窗口句柄,获取窗口句柄
	HWND hParent1 = ::GetParent(hWndl);//GetParent函数一个指定子窗口的父窗口句柄
	::SetParent(hWndl, GetDlgItem(IDC_STATIC)->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmfcdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmfcdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 定义图像变量
Mat srcImg, blurImg, gradientImg, nmsImg, outImg;
float low, high;

void CmfcdemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("图片文件 (*.bmp;*.png;*.jpg;*.tif)|*.bmp;*.png;*.jpg;*.tif|All Files (*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;
	
	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		USES_CONVERSION;
		char *s = T2A(strFilePath);
		srcImg = imread(s);
		resize(srcImg, srcImg, Size(rect.Width(), rect.Height()));
		
		imshow("src", srcImg);
	}

}


void CmfcdemoDlg::OnBnClickedButton2()  //保存图像按钮
{
	// TODO: 在此添加控件通知处理程序代码
	if (blurImg.data)  cv::imwrite("blurImg.jpg", blurImg);          //有数据则保存在当前目录
	if (gradientImg.data)  cv::imwrite("gradientImg.jpg", gradientImg);
	if (nmsImg.data)  cv::imwrite("nmsImg.jpg", nmsImg);
	if (outImg.data)  cv::imwrite("cannyImg.jpg", outImg);
}


void CmfcdemoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CmfcdemoDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	// 高斯模糊

	cvtColor(srcImg, blurImg, COLOR_BGR2GRAY);
	GaussianBlur(blurImg, blurImg, cv::Size(3, 3), 40, 40);
	resize(blurImg, blurImg, Size(rect.Width(), rect.Height()));

	imshow("高斯模糊", blurImg);

}


void CmfcdemoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	cv::Mat_<float> angle;     // to store angle while calculating image gradient
	cvtColor(srcImg, blurImg, COLOR_BGR2GRAY);
	GaussianBlur(blurImg, blurImg, cv::Size(3, 3), 40, 40);
	Gradient_image(blurImg, gradientImg, angle);
	
	imshow("梯度幅值", gradientImg);
}

void CmfcdemoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	cv::Mat_<float> angle;     // to store angle while calculating image gradient
	cvtColor(srcImg, blurImg, COLOR_BGR2GRAY);
	GaussianBlur(blurImg, blurImg, cv::Size(3, 3), 40, 40);
	Gradient_image(blurImg, gradientImg, angle);
	non_maximum_suppression(gradientImg, angle);
	nmsImg = gradientImg;

	imshow("非极大值抑制", nmsImg);
}


void CmfcdemoDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	
	cvtColor(srcImg, blurImg, COLOR_BGR2GRAY);
	GaussianBlur(blurImg, blurImg, cv::Size(3, 3), 40, 40);
	Canny(blurImg, outImg, low, high);
	imshow("Canny边缘检测", outImg);
}


////////////////////*********************************************/////////////////
//                    此处为canny算法实现代码
//////////////////***********************************************/////////////////

// * defind degree threshold
// @ ====================================================
bool __45_degree(const float& Angle) {
	return ((Angle > 0) && (Angle <= 45)) || ((Angle > 180) && (Angle <= 225));
}

bool __90_degree(const float& Angle) {
	return ((Angle > 45) && (Angle <= 90)) || ((Angle > 225) && (Angle <= 270));
}

bool __135_degree(const float& Angle) {
	return ((Angle > 90) && (Angle <= 135)) || ((Angle > 270) && (Angle <= 315));
}

bool __180_degree(const float& Angle) {
	return (Angle == 0) || ((Angle > 135) && (Angle <= 180)) || ((Angle > 315) && (Angle <= 360));
}
// @ ====================================================

void Gradient_image(const cv::Mat& image_source,
	cv::Mat& image_output,      // an empty matrix to store result
	cv::Mat_<float>& angle)     // an empty matrix to store arctan(Gy / Gx)
{
	angle = cv::Mat_<float>::zeros(image_source.size());
	image_output = cv::Mat::zeros(image_source.size(), CV_8UC1);
	int row_minus_1 = image_source.rows - 1;
	int col_minus_1 = image_source.cols - 1;

	int row = image_source.rows;
	int col = image_source.cols;

	auto point = image_source.data;
	int step = image_source.step;

	for (int i = 1; i < row_minus_1; ++i) {
		for (int j = 1; j < col_minus_1; ++j) {
			uchar pixel_00 = point[(i - 1) * step + j - 1];
			uchar pixel_01 = point[(i - 1) * step + j];
			uchar pixel_02 = point[(i - 1) * step + j + 1];
			uchar pixel_10 = point[i * step + j - 1];
			uchar pixel_11 = point[i * step + j];
			uchar pixel_12 = point[i * step + j + 1];
			uchar pixel_20 = point[(i + 1) * step + j - 1];
			uchar pixel_21 = point[(i + 1) * step + j];
			uchar pixel_22 = point[(i + 1) * step + j + 1];

			// float grad_x = (-1 * pixel_00) + (-2 * pixel_10) + (-1 * pixel_20) + (1 * pixel_02) + (2 * pixel_12) + (1 * pixel_22);
			float grad_x = pixel_02 + (2 * pixel_12) + pixel_22 - pixel_00 - (2 * pixel_10) - pixel_20;

			//float grad_y = (1 * pixel_00) + (2 * pixel_01) + (1 * pixel_02) + (-1 * pixel_20) + (-2 * pixel_21) + (-1 * pixel_22);
			float grad_y = pixel_00 + (2 * pixel_01) + pixel_02 - pixel_20 - (2 * pixel_21) - pixel_22;

			angle.at<float>(i, j) = atan(grad_y / (grad_x == 0 ? 0.00001 : grad_x));
			image_output.at<uchar>(i, j) = sqrt(grad_x * grad_x + grad_y * grad_y);
		}
	}
}

void non_maximum_suppression(cv::Mat& image_output,            // image has been gradiented first
	const cv::Mat_<float>& angle)     // image which store angel
{
	int row_minus_1 = image_output.rows - 1;
	int col_minus_1 = image_output.cols - 1;

	for (int i = 1; i < row_minus_1; ++i) {
		for (int j = 1; j < col_minus_1; ++j) {
			float Angle = angle.at<float>(i, j);
			uchar& value = image_output.at<uchar>(i, j);
			uchar previous = 1, next = 1;

			if (__45_degree(Angle)) {
				previous = image_output.at<uchar>(i - 1, j + 1);     // pixel_02
				next = image_output.at<uchar>(i + 1, j - 1);         // pixel_20
			}
			else if (__90_degree(Angle)) {
				previous = image_output.at<uchar>(i - 1, j);     // pixel_01
				next = image_output.at<uchar>(i + 1, j);         // pixel_21
			}
			else if (__135_degree(Angle)) {
				previous = image_output.at<uchar>(i - 1, j - 1);     // pixel_00
				next = image_output.at<uchar>(i + 1, j + 1);         // pixel_22
			}
			else if (__180_degree(Angle)) {
				previous = image_output.at<uchar>(i, j - 1);     // pixel_10
				next = image_output.at<uchar>(i, j + 1);         // pixel_12
			}

			if (value < previous || value < next)
				value = 0;
		}
	}
}

void double_threshold(cv::Mat& image_output, const float& low, const float& high) {
	assert(low >= 0);     // if (low < 0) or (high < 0) or (low > high), exit this function immediately
	assert(high >= 0);
	assert(low < high);
	int row_minus_1 = image_output.rows - 1;
	int col_minus_1 = image_output.cols - 1;
	for (int i = 1; i < row_minus_1; ++i) {
		for (int j = 1; j < col_minus_1; ++j) {
			uchar& value = image_output.at<uchar>(i, j);
			bool changed = false;
			if (value < low)
				value = 0;
			else if (value > high)
				value = 255;
			else {
				for (int m = -1; m <= 1; ++m) {
					for (int n = -1; n <= 1; ++n) {
						if (m == 0 && n == 0)
							continue;
						if (image_output.at<uchar>(i + m, j + n) > high) {
							value = 255;
							changed = true;
							break;
						}
					}
					if (changed)
						break;
				}
				if (!changed)
					value = 0;
			}
		}
	}
}

void Canny(const cv::Mat& image_source, cv::Mat& image_output, const float& low_threshold, const float& high_threshold) {
	assert(low_threshold <= high_threshold);
	cv::Mat_<float> angle;     // to store angle while calculating image gradient
	Gradient_image(image_source, image_output, angle);
	non_maximum_suppression(image_output, angle);
	double_threshold(image_output, low_threshold, high_threshold);
}




void CmfcdemoDlg::OnBnClickedGetdata()
{
	// TODO: 在此添加控件通知处理程序代码
 
	// modifing "low" and "high" to get the appropriate threshold
	CString strEDIT1, strEDIT2;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strEDIT1);
	GetDlgItem(IDC_EDIT2)->GetWindowText(strEDIT2);

	low = _ttof(strEDIT1);
	high = _ttof(strEDIT2);

}
