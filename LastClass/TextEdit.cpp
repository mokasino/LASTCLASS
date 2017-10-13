//TextEdit.cpp

#include "LastClass.h"
#include "TextEdit.h"
#include "ClassDiagramForm.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Figure.h"
#include "Caret.h"
#include "KeyBoard.h"
#include "KeyAction.h"
#include "EndKey.h"
#include "TextAreaSelected.h"
#include "HistoryText.h"
#include "WritingVisitor.h"   
#include "DeleteTextArea.h"
#include "WriteKoreanText.h"
#include "DoubleClickTextArea.h"
#include "FontSet.h"
#include "Selection.h"
#include "EditResizerBlocker.h"
#include "Class.h"
#include "Relation.h"
#include "SelfRelation.h"
#include "StatusBar.h"

//#include <iostream>

BEGIN_MESSAGE_MAP(TextEdit, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	ON_WM_KILLFOCUS()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()

	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_IME_NOTIFY, OnIMENotify)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TextEdit::TextEdit(ClassDiagramForm *classDiagramForm, Figure *figure, LOGFONT lf, Long rollNameBoxIndex) {
	this->classDiagramForm = classDiagramForm;
	this->text = NULL;
	this->caret = NULL;
	this->keyBoard = NULL;
	this->historyText = NULL;
	this->textAreaSelected = NULL;
	this->figure = figure;
	this->rollNameBoxIndex = rollNameBoxIndex;
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
	this->flagSelection = 0;
	this->currentX = 0;
	this->copyBuffer = "";
	this->criteriaWidth = figure->GetWidth();
	this->criteriaHeight = figure->GetHeight();
	this->criteriaX = figure->GetX();

	if (figure->lf.lfHeight == 0) {
		this->lf = lf;
	}
	else {
		this->lf = figure->lf;
	}
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct); //override
	CWnd::SetFocus();

	this->text = new Text;
	this->caret = new Caret;
	this->keyBoard = new KeyBoard;
	this->historyText = new HistoryText;
	this->textAreaSelected = new TextAreaSelected;

	this->cFont.CreateFontIndirect(&this->lf);
	SetFont(&this->cFont, TRUE);

	if (this->rollNameBoxIndex == -1) {
		this->text->SprayString(this->figure->GetContent());
	}
	else if (dynamic_cast<Relation*>(this->figure)) {
		this->text->SprayString(static_cast<Relation*>(this->figure)->rollNames->GetAt(this->rollNameBoxIndex));
	}
	else if (dynamic_cast<SelfRelation*>(this->figure)) {
		this->text->SprayString(static_cast<SelfRelation*>(this->figure)->rollNames->GetAt(this->rollNameBoxIndex));
	}
	if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
		this->numLockFlag = 0;
	}
	else {
		this->numLockFlag = 1;
	}

	Invalidate(false);
	return 0;
}

void TextEdit::OnPaint() {
	CPaintDC dc(this);

	RECT rt;
	this->GetClientRect(&rt);

	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rt.right, rt.bottom);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, rt.right, rt.bottom), RGB(255, 255, 255));
	WritingVisitor writingVisitor;

	memDC.SelectObject(&this->cFont);

	if (this->flagSelection == 1) {
		this->textAreaSelected->SelectTextArea(this, &memDC);
	}
	this->text->Accept(writingVisitor, &memDC);

	dc.BitBlt(0, 0, rt.right, rt.bottom, &memDC, 0, 0, SRCCOPY);

	this->caret->MoveToIndex(this, &memDC);

	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN &&
		nChar != VK_SPACE && nChar != VK_TAB && nChar != 10 && GetKeyState(VK_CONTROL) >= 0) {

		if (flagSelection == 1) {
			DeleteTextArea *deleteArea = DeleteTextArea::Instance();
			deleteArea->DeleteArea(this);
		}

		this->historyText->PushUndo(this->text, this->caret);

		char nCharacter = nChar;
		SingleByteCharacter singleByteCharacter(nCharacter);
		if (this->caret->GetCharacterIndex() == this->text->GetAt(this->caret->GetRowIndex())->GetLength()) {
			this->text->GetAt(this->caret->GetRowIndex())->Add(singleByteCharacter.Clone());
		}
		else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 0) {
			this->text->GetAt(this->caret->GetRowIndex())->Insert(this->caret->GetCharacterIndex(), singleByteCharacter.Clone());
		}
		else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 1) {
			this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex(), singleByteCharacter.Clone());
		}
		this->caret->MoveForwardCharacterIndex();
	}
	
	CClientDC dc(this);
	dc.SelectObject(&cFont);

	EditResizerBlocker editResizer;
	editResizer.Block(this, &dc);

	CWnd::HideCaret();

	Invalidate(false);
}

Long TextEdit::OnComposition(WPARAM wParam, LPARAM lParam) {
	HIMC hIMC = ImmGetContext(GetSafeHwnd());

	if (flagSelection == 1) {
		DeleteTextArea *deleteArea = DeleteTextArea::Instance();
		deleteArea->DeleteArea(this);
	}

	WriteKoreanText *writeHanguel = WriteKoreanText::Instance();
	writeHanguel->WriteHanguel(wParam, lParam, hIMC, this);

	ImmReleaseContext(GetSafeHwnd(), hIMC);

	CClientDC dc(this);
	dc.SelectObject(&cFont);

	EditResizerBlocker editResizer;
	editResizer.Block(this, &dc);

	CWnd::HideCaret();

	Invalidate(false);
	return 0;
}

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {
	CClientDC dc(this);
	dc.SelectObject(&cFont);

	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;

	SetTimer(1, 1, NULL);
	while (elapseTime < dblclkTime) {
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
			KillTimer(1);
		}
		elapseTime++;
	}

	if (GetKeyState(VK_SHIFT) < 0) { // Ŭ���ߴµ� ����Ʈ�� �������� ��
		if (this->flagSelection == 0) { // flag �� �ȴ���������
			this->flagSelection = 1; // flag �� �����ش�
			this->selectedX = this->caret->GetCharacterIndex(); // selectedX, Y �� ���� ��ġ ĳ�� ��� ��ǥ�� �����Ѵ�
			this->selectedY = this->caret->GetRowIndex();
		}
	}
	else {
		if (this->flagSelection == 1) { // ����Ʈ �ȴ����ִµ� flag �� ���������� flag ������ش�
			this->flagSelection = 0;
		}
	}

	this->caret->MoveToPoint(this, &dc, point); // �ű� ��ġ�� ĳ���� �̵������ش�
	
	SetCapture();

	KillTimer(1);
	Invalidate(false);
}

void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {

	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
		return;
	}

	KillTimer(1);

	ReleaseCapture();

	Invalidate(false);
}

void TextEdit::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {
		CClientDC dc(this);
		dc.SelectObject(&cFont);

		if (this->flagSelection == 0 && this->currentX != 0) {// �޸��콺 �����ִµ� �̵��ÿ� flag ���������� Ȯ���ؼ�
			this->flagSelection = 1; // flag ������ �ƴϸ� ���������� �ٲٰ�
			this->selectedX = this->caret->GetCharacterIndex(); // ���� �ѹ� selectedX, Y ��
			this->selectedY = this->caret->GetRowIndex();
		}
		this->caret->MoveToPoint(this, &dc, point); // ���ο� ��ġ�� ĳ�� �̵��Ѵ�

		Invalidate(false);
	}
	this->currentX = point.x;
}

void TextEdit::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CClientDC dc(this);

	DoubleClickTextArea *DoubleClick = DoubleClickTextArea::Instance();
	DoubleClick->FindDoubleClickAreaIndex(this);

	Invalidate(false);
}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CClientDC dc(this);
	dc.SelectObject(&cFont);

	this->koreanEnglish = 1;
	KeyAction *keyAction = this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
	if (keyAction != 0) {
		keyAction->KeyPress(this);
	}
	this->koreanEnglish = 0;
	if (nChar == VK_NUMLOCK) {
		if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
			this->numLockFlag = 0;
		}
		else {
			this->numLockFlag = 1;
		}
		this->classDiagramForm->lastClass->statusBar->DestroyStatus();
		this->classDiagramForm->lastClass->statusBar->MakeStatusBar(this->classDiagramForm->lastClass, this->classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);
	}
	else if (nChar == VK_CAPITAL) {
		if (this->classDiagramForm->capsLockFlag == 0) {
			this->classDiagramForm->capsLockFlag = 1;
		}
		else if (this->classDiagramForm->capsLockFlag == 1) {
			this->classDiagramForm->capsLockFlag = 0;
		}
		this->classDiagramForm->lastClass->statusBar->DestroyStatus();
		this->classDiagramForm->lastClass->statusBar->MakeStatusBar(this->classDiagramForm->lastClass, this->classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);
	}

	if (nChar != VK_RETURN && nChar != VK_ESCAPE && nChar != VK_F1 && nChar != 0x46 && nChar != 0x50 && nChar != 0x4F && nChar != 0x4E) {


		EditResizerBlocker editResizer;
		editResizer.Block(this, &dc);

		CWnd::HideCaret();

		Invalidate(false);
	}
}

LRESULT TextEdit::OnIMENotify(WPARAM wParam, LPARAM lParam) {
	if (wParam == IMN_SETCONVERSIONMODE) {
		if (this->koreanEnglish == 0) {
			this->koreanEnglish = 1;
		}
		else {
			this->koreanEnglish = 0;
		}
	}
	return 0;
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {
	if (this->rollNameBoxIndex == -1) {
		string content(this->text->MakeText());
		this->figure->ReplaceString(content, this->lf);
	}
	else if (dynamic_cast<Relation*>(this->figure)) {
		string rollNameText(this->text->MakeText());
		static_cast<Relation*>(this->figure)->ReplaceString(rollNameText, this->rollNameBoxIndex, this->lf);
	}
	else if (dynamic_cast<SelfRelation*>(this->figure)) {
		string rollNameText(this->text->MakeText());
		static_cast<SelfRelation*>(this->figure)->ReplaceString(rollNameText, this->rollNameBoxIndex, this->lf);
	}

	CWnd::OnKillFocus(pNewWnd);
	CWnd::HideCaret();
	::DestroyCaret();


	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->historyText != NULL) {
		delete this->historyText;
	}
	if (this->textAreaSelected != NULL) {
		delete this->textAreaSelected;
	}
	if (this != NULL) {
		delete this;
	}
}

void TextEdit::OnClose() {
	CWnd::HideCaret();
	::DestroyCaret();

	CDC *pDC = GetDC();
	CFont *oldFont = pDC->SelectObject(&this->cFont);
	this->cFont.DeleteObject();
	ReleaseDC(pDC);

	if (this->rollNameBoxIndex == -1) {
		string content(this->text->MakeText());
		this->figure->ReplaceString(content, this->lf);
	}
	else if (dynamic_cast<Relation*>(this->figure)) {
		string rollNameText(this->text->MakeText());
		static_cast<Relation*>(this->figure)->ReplaceString(rollNameText, this->rollNameBoxIndex, this->lf);
	}
	else if (dynamic_cast<SelfRelation*>(this->figure)) {
		string rollNameText(this->text->MakeText());
		static_cast<SelfRelation*>(this->figure)->ReplaceString(rollNameText, this->rollNameBoxIndex, this->lf);
	}

	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->historyText != NULL) {
		delete this->historyText;
	}
	if (this->textAreaSelected != NULL) {
		delete this->textAreaSelected;
	}
	if (this != NULL) {
		delete this;
	}
}
