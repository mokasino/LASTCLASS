//PrintPreview.cpp

#include "PrintPreview.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "DrawingVisitor.h"
#include "WritingVisitor.h"
#include "Diagram.h"
#include "PrintPreviewState.h"
#include "ToolBar.h"

#include "PrintPreviewButton.h"
#include "PrintPreviewButtonAction.h"

#include <afxwin.h>
#include <afxdlgs.h>
#include <afxpriv.h>
using namespace std;

BEGIN_MESSAGE_MAP(PrintPreview, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(1, 5, OnCommandButton)
END_MESSAGE_MAP()

PrintPreview::PrintPreview(LastClass *lastClass) {
	this->lastClass = lastClass;
	this->printPreviewButton = NULL;

	this->nextButton = NULL;
	this->previousButton = NULL;
	this->printButton = NULL;
	this->printZoomIn = NULL;
	this->printZoomOut = NULL;

	this->horizontalPage = 0;
	this->verticalPage = 0;
	this->horizontalPageSize = 2000;
	this->verticalPageSize = 2000;
	this->zoomRate = 100;
}

int PrintPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) {
   CFrameWnd::OnCreate(lpCreateStruct);
   
   this->printPreviewButton = new PrintPreviewButton;

   this->ModifyStyle(0, WS_OVERLAPPEDWINDOW  );
   this->nextButton = new CButton;
   this->nextButton->Create("���� ������", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_CENTER|BS_VCENTER,CRect(50,100,200,140), this, 1);
   this->previousButton = new CButton;
   this->previousButton->Create("���� ������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(50, 150, 200, 190), this, 2);
   this->printButton = new CButton;
   this->printButton->Create("�μ��ϱ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(50, 200, 200, 240), this, 3);
   this->printZoomIn = new CButton;
   //this->printZoomIn->Create("Ȯ ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(50, 250, 200, 290), this, 4);
   this->printZoomOut = new CButton;
  // this->printZoomOut->Create("�� ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(50, 300, 200, 340), this, 5);

   this->SetFocus();
   this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

   this->SetScrollRange(SB_VERT, 0, 380);

   this->lastClass->EnableWindow(false);
   //this->lastClass->classDiagramForm->EnableWindow(false);
   
   Invalidate();
   
   return 0;
}
void PrintPreview::OnPaint() {
	
	CPaintDC dc(this);
	CRect rec;
	this->GetClientRect(&rec);
	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, 4000, 2000);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, 4000, 2000), RGB(255, 255, 255));
	CFont cFont;//CreateFont�� ��18�� textEdit�� rowHight�� �ٲ����
	cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "���� ���");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);
	DrawingVisitor drawingVisitor;
	this->lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
	WritingVisitor writingVisitor;
	this->lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);

	// ������ ������
	Long a = (rec.CenterPoint().x)* 5 / 8;
	Long b = (rec.CenterPoint().y)* 1 / 6;
	Long c = (rec.CenterPoint().x) * 11 / 8 - (rec.CenterPoint().x) * 5 / 8;
	Long d = (rec.CenterPoint().y) * 11 / 6 - (rec.CenterPoint().y) * 1 / 6;
	
	CBitmap *pOldBitmapOne;
	CBitmap bitmapOne;
	CDC memDCOne;
	memDCOne.CreateCompatibleDC(&dc);
	bitmapOne.CreateCompatibleBitmap(&dc, rec.Width(), rec.Height());
	pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
	//ȸ������ �غ�
	memDCOne.FillSolidRect(rec, RGB(153, 153, 153));
	//ȸ������ ��üȭ������ ���
	dc.BitBlt(0, 0, rec.Width(), rec.Height(), &memDCOne, 0, 0, SRCCOPY);
	////////////////////////////////////////////////////////////
	//ȸ������ �����ϰ�, Ȯ���� �����̿��� �̵� �����ϰ�
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(100, 100);
	dc.SetViewportExt(this->zoomRate, this->zoomRate);
	//dc.SetViewportOrg(220, 20);

	Long vertPos = this->GetScrollPos(SB_VERT);
	//Long horzPos = this->GetScrollPos(SB_HORZ);

	//������ ���
	memDCOne.StretchBlt(a,b - vertPos,c,d - vertPos,&memDC, this->horizontalPage, this->verticalPage, this->horizontalPageSize, this->verticalPageSize, SRCCOPY);

	//ȸ�������� ������ ���� ���
	dc.BitBlt(0, 0, rec.Width(), rec.Height(), &memDCOne, 0, 0, SRCCOPY);

	CString tempString = _T("");
	tempString.Format(_T("�ػ� (����:%d ����:%d), ����ͱ��� (����:%d ����:%d)"),
		dc.GetDeviceCaps(HORZRES),
		dc.GetDeviceCaps(VERTRES),
		dc.GetDeviceCaps(HORZSIZE),
		dc.GetDeviceCaps(VERTSIZE));
	dc.TextOutA(10, 10, tempString);

	memDC.SelectObject(oldFont);
	cFont.DeleteObject();
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
	memDCOne.SelectObject(pOldBitmap);
	bitmapOne.DeleteObject();
	memDCOne.DeleteDC();
	
}
void PrintPreview::OnDraw(CDC *cdc) {

}
void PrintPreview::OnPrint(CDC *cdc, CPrintInfo *pInfo, UINT page) {
	Long i[10] = { 0,2000,800,800,1600,1600,2400,2400,3200,3200 };
	Long j[10] = { 0,0,0,1000,0,1000,0,1000,0,1000 };
	Long k = page - 1;

	Long width = pInfo->m_rectDraw.Width();
	Long hegiht = pInfo->m_rectDraw.Height();
	CDC memDC;
	CRect rect;
	this->lastClass->classDiagramForm->GetClientRect(&rect);
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	
	CPaintDC dc(this);

	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, 4000, 2000);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, 4000, 2000), RGB(255, 255, 255));
	CFont cFont;//CreateFont�� ��18�� textEdit�� rowHight�� �ٲ����
	cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "���� ���");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);

	DrawingVisitor drawingVisitor;
	this->lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
	WritingVisitor writingVisitor;
	this->lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);


	CBitmap *pOldBitmapOne;
	CBitmap bitmapOne;
	CDC memDCOne;
	memDCOne.CreateCompatibleDC(&dc);
	bitmapOne.CreateCompatibleBitmap(&dc, 2000, 2000);
	pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
	memDCOne.FillSolidRect(CRect(0, 0, 2000, 2000), RGB(255, 255, 255));
	memDCOne.BitBlt(0, 0, 2000, 2000, &memDC, i[k], j[k], SRCCOPY);

	int mapMode = cdc->GetMapMode();
	memDCOne.SetMapMode(mapMode);
	cdc->SetStretchBltMode(COLORONCOLOR);

	cdc->SetMapMode(MM_ISOTROPIC);
	cdc->SetWindowExt(100, 100);
	cdc->SetViewportExt(this->zoomRate, this->zoomRate);

	cdc->StretchBlt(100, 100, width - 200, hegiht - 200, &memDCOne, 0, 0, 2000, 2000, SRCCOPY);

}

BOOL PrintPreview::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	CFrameWnd::SetFocus();
	SetFocus();
	bool ret = false;

	// nWheelScrollLines �� �ѹ��� �̵��ϴ� �� �� (Reg���� �о� �´�)
	HKEY hKey = 0;
	DWORD dwType = REG_BINARY;
	DWORD dwSize = 10;
	BYTE* pByte = new BYTE[dwSize];

	ZeroMemory(pByte, dwSize);

	RegOpenKey(HKEY_CURRENT_USER, "Control Panel\\Desktop", &hKey);
	RegQueryValueEx(hKey, "WheelScrollLines", NULL, &dwType, pByte, &dwSize);
	RegCloseKey(hKey);

	int nWheelScrollLines = atoi((char*)pByte);
	delete pByte;

	int vertCurPos = GetScrollPos(SB_VERT);

	if (GetKeyState(VK_CONTROL) >= 0) {
		if (zDelta <= 0) { //���콺 �� �ٿ�
			vertCurPos += nWheelScrollLines * 20;
		}
		else {  //���콺 �� ��
			vertCurPos -= nWheelScrollLines * 20;
		}
		ret = true;
	}
	else {
		if (zDelta <= 0) { //���콺 �� �ٿ�
			this->zoomRate -= 10;
			if (this->zoomRate < 50) {
				this->zoomRate = 50;
			}
		}
		else {  //���콺 �� ��
			this->zoomRate += 10;
			if (this->zoomRate > 190) {
				this->zoomRate = 190;
			}
		}
		ret = true;
	}
	SetScrollPos(SB_VERT, vertCurPos);
	Invalidate(false);

	return ret;
}

void PrintPreview::OnClose() {
	this->lastClass->EnableWindow(true);
	if (this->nextButton != 0) {
		delete this->nextButton;
	}
	if (this->printButton != 0) {
		delete this->printButton;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
	}
	if (this->printZoomIn != 0) {
		delete this->printZoomIn;
	}
	if (this->printZoomOut != 0) {
		delete this->printZoomOut;
	}
	if (this != 0) {
		this->lastClass->printPreview = NULL;
		delete this;
	}
}

void PrintPreview::OnBeginPrinting(CDC *pDc, CPrintInfo *pInfo) {
	
}

void PrintPreview::OnEndPrinting(CDC *pDc, CPrintInfo *pInfo) {
	this->lastClass->EnableWindow(true);
	if (this->nextButton != 0) {
		delete this->nextButton;
	}
	if (this->printPreviewButton != 0) {
		delete this->printPreviewButton;
	}
	if (this->printButton != 0) {
		delete this->printButton;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
	}
	if (this->printZoomIn != 0) {
		delete this->printZoomIn;
	}
	if (this->printZoomOut != 0) {
		delete this->printZoomOut;
	}
	if (this != 0) {
		this->lastClass->printPreview = NULL;
		delete this;
	}
}

void PrintPreview::OnSize(UINT nType, int cx, int cy) {
	Invalidate(false);
}
BOOL PrintPreview::DoModal() {
	if (this->GetParent()) {
		this->GetParent()->EnableWindow(FALSE);
		RunModalLoop(MLF_SHOWONIDLE);
		DestroyWindow();
	}
	return TRUE;
}

void PrintPreview::OnCommandButton(UINT idNumber) {
	PrintPreviewButtonAction *buttonPressed = this->printPreviewButton->ButtonPressed(idNumber);
	if (buttonPressed != 0) {
		buttonPressed->ButtonPress(this);
	}
}