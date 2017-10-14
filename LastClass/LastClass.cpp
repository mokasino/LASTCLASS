//LastClass.cpp

#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Menu.h"
#include "menuAction.h"
#include "Scroll.h"
#include "HistoryGraphic.h"
#include "StatusBar.h"
#include "ToolBar.h"
#include "PrintPreview.h"
#include "resource.h"
#include <afxdlgs.h>
#include <afxext.h>
#include <afxstatusbar.h>
#include "resource.h"
#include <afxcmn.h>
using namespace std;

BEGIN_MESSAGE_MAP(LastClass, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(100, 126, OnMyMenu)
	ON_COMMAND_RANGE(40002, 40016, OnMyToolBar)
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

LastClass::LastClass() {
	this->classDiagramForm = NULL;
	this->menu = NULL;
	this->toolBar = NULL;
	this->statusBar = NULL;
	this->printPreview = NULL;
}

int LastClass::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct); //�ڵ����� �������̵� //��ӿ���
	CRect rect;
	this->GetClientRect(&rect);

	this->statusBar = new StatusBar;
	this->toolBar = new ToolBar;
	rect.top += 45;
	//rect.left += 60;
	//rect.right -= 60;
	rect.bottom -= 73;
	this->classDiagramForm = new ClassDiagramForm(this);
	this->classDiagramForm->Create(NULL, "classDiagramForm", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, rect, this, 100000);
	this->menu = new Menu(this);

	//this->toolBar->MakeToolBar(this->GetSafeHwnd());
	//this->toolBar->MakeAnotherToolBar(this->GetSafeHwnd());
	//this->statusBar->MakeStatusBar(this, this->GetSafeHwnd(), NULL, NULL, 5);

	return 0;
}

void LastClass::OnMyMenu(UINT parm_control_id) {

	MenuAction* menuAction = this->menu->MenuSelected(parm_control_id);
	if (menuAction != 0) {
		menuAction->MenuPress(this);
	}
}

void LastClass::OnKillFocus(CWnd *pNewWnd) {
	//CFrameWnd::OnKillFocus(pNewWnd);
}

void LastClass::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
}

void LastClass::OnSetFocus(CWnd* pOldWnd) {
	CFrameWnd::OnSetFocus(pOldWnd);
	CWnd::SetFocus();
	Invalidate(false);
}

void LastClass::OnSize(UINT nType, int cx, int cy) {
	//ModifyStyle(0, WS_CLIPCHILDREN);
	CFrameWnd::OnSize(nType, cx, cy);
	CRect rect;
	this->GetClientRect(&rect);
	this->toolBar->DestroyToolBar();
	this->toolBar->MakeToolBar(this->GetSafeHwnd());
	//this->toolBar->MakeAnotherToolBar(this->GetSafeHwnd());
	this->statusBar->DestroyStatus();
	this->statusBar->MakeStatusBar(this, this->GetSafeHwnd(), NULL, NULL, 5);

	this->toolBar->ChangeToolBarSize(&rect);
	//this->toolBar->ChangeAnotherToolBarSize(&rect);
	//this->statusBar->ChangeStatusBarSize(&rect);
	rect.top += 45;
	//rect.left += 60;
	//rect.right -= 60;
	rect.bottom -= 73;
	//this->classDiagramForm->MoveWindow(rect.left, rect.top, rect.right, rect.bottom, 1);
	this->classDiagramForm->SetWindowPos(this, rect.left, rect.top, rect.right, rect.bottom, SWP_NOMOVE | SWP_NOZORDER);
	this->RedrawWindow();
	this->classDiagramForm->Invalidate(FALSE);

	CRect rect1;
	this->GetClientRect(&rect1);
	rect1.top = rect1.bottom - 20;
	//rect1.right = rect1.left + 10;
	this->InvalidateRect(rect1);

	//ModifyStyle(WS_CLIPCHILDREN, 0);
}

BOOL LastClass::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	return false;
}

void LastClass::OnLButtonDown(UINT nFlags, CPoint point) {
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void LastClass::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CFrameWnd::OnLButtonDblClk(nFlags, point);
}

void LastClass::OnLButtonUp(UINT nFlags, CPoint point) {
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void LastClass::OnMouseMove(UINT nFlags, CPoint point) {
	CFrameWnd::OnMouseMove(nFlags, point);
}
void LastClass::OnMyToolBar(UINT parm_control_id) {
	CClientDC dc(this);
	this->toolBar->ButtonSelected(parm_control_id, this, this->classDiagramForm, &dc);
}
void LastClass::OnClose() {
	//6.2. ���̾�׷��� �����.
	int messageBox = IDNO;
	INT_PTR int_ptr = IDOK;
	if (this->classDiagramForm->historyGraphic->undoGraphicArray->GetLength() != 0 
		|| this->classDiagramForm->historyGraphic->redoGraphicArray->GetLength() != 0) {
		if (this->classDiagramForm->fileName == "") {
			messageBox = MessageBox(_T("���� ������ ���� ������ �����Ͻðڽ��ϱ�?"), "ClassDiagram", MB_YESNOCANCEL);

			if (messageBox == IDYES) {
				CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "�ؽ�Ʈ ����(*.txt)");
				int_ptr = dlgFile.DoModal();
				if (int_ptr == IDOK) {
					this->classDiagramForm->fileName = dlgFile.GetPathName();
					this->classDiagramForm->Save();
				}
				//else {
				//return;  //����
				//}
			}
		}
		else {
			CString object;
			object = "���泻���� ";
			object.Append(this->classDiagramForm->fileName);
			object.Append("�� �����Ͻðڽ��ϱ�?");
			messageBox = MessageBox(object, "ClassDiagram", MB_YESNOCANCEL);
			if (messageBox == IDYES) {
				this->classDiagramForm->Save();
			}
		}
	}
	//6.2. ���̾�׷��� �����.
	if (messageBox != IDCANCEL && int_ptr == IDOK) {//== IDYES || messageBox == IDNO ) {
		if (this->classDiagramForm != NULL) {
			this->classDiagramForm->OnClose();
			delete this->classDiagramForm;
			this->classDiagramForm = NULL;
		}
		if (this->menu != NULL) {
			delete this->menu;
			this->menu = NULL;
		}
		if (this->toolBar != NULL) {
			delete this->toolBar;
			this->toolBar = NULL;
		}
		if (this->statusBar != NULL) {
			delete this->statusBar;
			this->statusBar = NULL;
		}
		if (this->printPreview != NULL) {
			this->printPreview->OnClose();
			this->printPreview = NULL;
		}
		CFrameWnd::OnClose(); // ��������`�� �ڵ�����
	}
}