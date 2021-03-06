
// mfc_demoDlg.h: 头文件
//

#pragma once


// CmfcdemoDlg 对话框
class CmfcdemoDlg : public CDialogEx
{
// 构造
public:
	CmfcdemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedGetdata();
};

#include <iostream>  
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/highgui/highgui_c.h>

void Gradient_image(const cv::Mat& image_source,
	cv::Mat& image_output,      // an empty matrix to store result
	cv::Mat_<float>& angle);     // an empty matrix to store arctan(Gy / Gx)
	
void non_maximum_suppression(cv::Mat& image_output,   // image has been gradiented first
	const cv::Mat_<float>& angle);					 // image which store angel
	
void double_threshold(cv::Mat& image_output, const float& low, const float& high);
	
void Canny(const cv::Mat& image_source, cv::Mat& image_output,
	const float& low_threshold, const float& high_threshold);
