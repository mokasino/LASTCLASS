//ToolBar.cpp

#include "ToolBar.h"
#include "resource.h"
#include "ToolBarProcess.h"

ToolBar::ToolBar() {
	this->hTool1 = 0;
	this->hTool2 = 0;
}
ToolBar::ToolBar(const ToolBar& source) {
}
ToolBar::~ToolBar() {
}
void ToolBar::MakeToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | TBSTYLE_FLAT | WS_VISIBLE | CCS_NORESIZE | WS_BORDER | TBSTYLE_TRANSPARENT, 0, 0, 1361, 45,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	this->hTool1 = hTool;
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[30];
	TBADDBITMAP tbab;
	Long iNew, iopen, iSave, iredo, iundo, iLeftAlign, iCenterAlign, iRightAlign, idelete_, icut, icopy, ipaste, iprint, iprintpre, ihelp;
	TCHAR newfile[10] = "������";
	TCHAR open[10] = "����";
	TCHAR save[10] = "�����ϱ�";
	TCHAR redo[10] = "�����";
	TCHAR undo[10] = "�ǵ�����";
	TCHAR leftAlign[10] = "���� ����";
	TCHAR centerAlign[12] = "��� ����";
	TCHAR rightAlign[12] = "������ ����";
	TCHAR delete_[10] = "�����";
	TCHAR cut[10] = "�ڸ���";
	TCHAR copy[10] = "�����ϱ�";
	TCHAR paste[10] = "�ٿ��ֱ�";
	TCHAR print[10] = "�μ��ϱ�";
	TCHAR printpre[10] = "�̸�����";
	TCHAR help[10] = "����";

	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_SMALL_COLOR;
	SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);
	iNew = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)newfile);
	iopen = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)open);
	iSave = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)save);
	iredo = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)redo);
	iundo = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)undo);
	iLeftAlign = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)leftAlign);
	iCenterAlign = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)centerAlign);
	iRightAlign = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)rightAlign);
	idelete_ = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)delete_);
	icut = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)cut);
	icopy = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)copy);
	ipaste = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)paste);
	iprint = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)print);
	iprintpre = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)printpre);
	ihelp = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)help);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = STD_FILENEW;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_BUTTON40001;
	tbb[0].iString = iNew;
	tbb[1].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[2].iBitmap = STD_FILEOPEN;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_BUTTON40002;
	tbb[2].iString = iopen;
	tbb[3].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[4].iBitmap = STD_FILESAVE;
	tbb[4].fsState = TBSTATE_ENABLED;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = ID_BUTTON40003;
	tbb[4].iString = iSave;
	tbb[5].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[6].iBitmap = STD_UNDO;
	tbb[6].fsState = TBSTATE_ENABLED;
	tbb[6].fsStyle = TBSTYLE_BUTTON;
	tbb[6].idCommand = ID_BUTTON40005;
	tbb[6].iString = iundo;
	tbb[7].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[8].iBitmap = STD_REDOW;
	tbb[8].fsState = TBSTATE_ENABLED;
	tbb[8].fsStyle = TBSTYLE_BUTTON;
	tbb[8].idCommand = ID_BUTTON40006;
	tbb[8].iString = iredo;
	tbb[9].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	//tbb[10].iBitmap = ;
	tbb[10].fsState = TBSTATE_ENABLED;
	tbb[10].fsStyle = TBSTYLE_BUTTON;
	tbb[10].idCommand = ID_BUTTON40007;
	tbb[10].iString = iLeftAlign;
	tbb[11].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	//tbb[12].iBitmap = ;
	tbb[12].fsState = TBSTATE_ENABLED;
	tbb[12].fsStyle = TBSTYLE_BUTTON;
	tbb[12].idCommand = ID_BUTTON40008;
	tbb[12].iString = iCenterAlign;
	tbb[13].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	//tbb[14].iBitmap = ;
	tbb[14].fsState = TBSTATE_ENABLED;
	tbb[14].fsStyle = TBSTYLE_BUTTON;
	tbb[14].idCommand = ID_BUTTON40009;
	tbb[14].iString = iRightAlign;
	tbb[15].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[16].iBitmap = STD_DELETE;
	tbb[16].fsState = TBSTATE_ENABLED;
	tbb[16].fsStyle = TBSTYLE_BUTTON;
	tbb[16].idCommand = ID_BUTTON40010;
	tbb[16].iString = ipaste;
	tbb[17].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[18].iBitmap = STD_CUT;
	tbb[18].fsState = TBSTATE_ENABLED;
	tbb[18].fsStyle = TBSTYLE_BUTTON;
	tbb[18].idCommand = ID_BUTTON40011;
	tbb[18].iString = iprint;
	tbb[19].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[20].iBitmap = STD_COPY;
	tbb[20].fsState = TBSTATE_ENABLED;
	tbb[20].fsStyle = TBSTYLE_BUTTON;
	tbb[20].idCommand = ID_BUTTON40012;
	tbb[20].iString = iprintpre;
	tbb[21].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[22].iBitmap = STD_PASTE;
	tbb[22].fsState = TBSTATE_ENABLED;
	tbb[22].fsStyle = TBSTYLE_BUTTON;
	tbb[22].idCommand = ID_BUTTON40013;
	tbb[22].iString = ihelp;
	tbb[23].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[24].iBitmap = STD_PRINT;
	tbb[24].fsState = TBSTATE_ENABLED;
	tbb[24].fsStyle = TBSTYLE_BUTTON;
	tbb[24].idCommand = ID_BUTTON40014;
	tbb[24].iString = iprint;
	tbb[25].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[26].iBitmap = STD_PRINTPRE;
	tbb[26].fsState = TBSTATE_ENABLED;
	tbb[26].fsStyle = TBSTYLE_BUTTON;
	tbb[26].idCommand = ID_BUTTON40015;
	tbb[26].iString = iprintpre;
	tbb[27].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	tbb[28].iBitmap = STD_HELP;
	tbb[28].fsState = TBSTATE_ENABLED;
	tbb[28].fsStyle = TBSTYLE_BUTTON;
	tbb[28].idCommand = ID_BUTTON40016;
	tbb[28].iString = ihelp;
	tbb[29].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;


	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);
}
void ToolBar::MakeAnotherToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | CCS_VERT | CCS_NORESIZE | WS_BORDER, 0, 45, 60, 614,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	this->hTool2 = hTool;
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[5];
	SendMessage(hTool, TB_SETBUTTONSIZE, 0, MAKELPARAM(58, 47));
	SendMessage(hTool, TB_SETBITMAPSIZE, 0, (LPARAM)MAKELPARAM(50, 44));
	DWORD backgroundColor = GetSysColor(COLOR_BTNFACE);///�������
	COLORMAP colorMap;
	colorMap.from = RGB(0, 0, 0);
	colorMap.to = backgroundColor;
	//HBITMAP hbm = CreateMappedBitmap(NULL, IDB_BITMAP2, 0, &colorMap, 1);
	/*BITMAP bitInfo;
	CBitmap bmp;
	bmp.LoadBitmapA(IDB_BITMAP2);
	bmp.GetBitmap(&bitInfo);
	HBITMAP hbm = bmp.operator HBITMAP(); */
	TBADDBITMAP tb;
	tb.hInst = NULL;
	//tb.nID = (UINT_PTR)hbm;
	int index = SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tb);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = index;
	tbb[0].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_BUTTON40001;

	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);
}

void ToolBar::ButtonSelected(UINT parm_control_id, LastClass *lastClass, ClassDiagramForm *classDiagramForm, CDC *cdc) {
	ToolBarProcess toolBarProcess;
	switch (parm_control_id) {
	case 40002:toolBarProcess.OnOpenClicked(lastClass);
		break;
	case 40003:toolBarProcess.OnSaveFileClicked(lastClass);
		break;
	case 40004:toolBarProcess.OnNewFileClicked(lastClass);
		break;
	case 40005:toolBarProcess.OnUndoFileClicked(lastClass);
		break;
	case 40006:toolBarProcess.OnRedoFileClicked(lastClass);
		break;
	case 40007:toolBarProcess.OnLeftAlignClicked(lastClass);
		break;
	case 40008:toolBarProcess.OnCenterAlignClicked(lastClass);
		break;
	case 40009:toolBarProcess.OnRightAlignClicked(lastClass);
		break;
	case 40010:toolBarProcess.OnFinishFileClicked(lastClass);
		break;
	case 40011:toolBarProcess.OnCutFileClicked(lastClass);
		break;
	case 40012:toolBarProcess.OnCopyFileClicked(lastClass);
		break;
	case 40013:toolBarProcess.OnPasteFileClicked(lastClass);
		break;
	case 40014:toolBarProcess.OnPrintFileClicked(lastClass);
		break;
	case 40015:toolBarProcess.OnPrintPreFileClicked(lastClass);
		break;
	case 40016:toolBarProcess.OnSupportFileClicked(lastClass);
		break;
	default:
		break;
	}
}

void ToolBar::ChangeToolBarSize(RECT *rect) {
	CWnd *cwnd = CWnd::FromHandle(this->hTool1);
	cwnd->SetWindowPos(cwnd, 0, 0, rect->right - 1, 45, SWP_NOMOVE | SWP_NOZORDER);
}
void ToolBar::ChangeAnotherToolBarSize(RECT *rect) {
	CWnd *cwnd = CWnd::FromHandle(this->hTool2);
	cwnd->SetWindowPos(cwnd, 0, 45, 60, rect->bottom - 66, SWP_NOMOVE | SWP_NOZORDER);
}

void ToolBar::DestroyToolBar() {
	DestroyWindow(this->hTool1);
	this->hTool1 = 0;
}