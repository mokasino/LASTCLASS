//FontSet.cpp

#include "FontSet.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"

#pragma warning(disable:4996)

FontSet::FontSet() {
	this->lf = { 0, };
}

FontSet::FontSet(LOGFONT *lf) { // ClassDiagramForm->OnCreate
	//Set Default
	lf->lfHeight = 19;										// �۲��� ����
	lf->lfWidth = 0;										// �۲��� �ʺ�
	lf->lfEscapement = 0;									// ����
	lf->lfOrientation = 0;									// ȸ������
	lf->lfWeight = FW_NORMAL;								// ����
	lf->lfItalic = FALSE;									// ����Ӳ�
	lf->lfUnderline = FALSE;								// ����
	lf->lfStrikeOut = FALSE;								// ��Ҽ�
	lf->lfCharSet = DEFAULT_CHARSET;						// ���� ��Ʈ
	lf->lfOutPrecision = OUT_CHARACTER_PRECIS;				//��� ��Ȯ��
	lf->lfClipPrecision = CLIP_CHARACTER_PRECIS;			// Ŭ���� ��Ȯ��
	lf->lfQuality = DEFAULT_QUALITY;						// ����� ��
	lf->lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;		// �ڰ�
	strcpy(lf->lfFaceName, _T("���� ���"));				//�۲��̸�
}

FontSet::FontSet(const FontSet& source) {
	this->lf = source.lf;
}

LOGFONT& FontSet::RelationFontSet() {
	//Set Default
	lf.lfHeight = 15;										// �۲��� ����
	lf.lfWidth = 0;											// �۲��� �ʺ�
	lf.lfEscapement = 0;									// ����
	lf.lfOrientation = 0;									// ȸ������
	lf.lfWeight = FW_NORMAL;								// ����
	lf.lfItalic = FALSE;									// ����Ӳ�
	lf.lfUnderline = FALSE;									// ����
	lf.lfStrikeOut = FALSE;									// ��Ҽ�
	lf.lfCharSet = DEFAULT_CHARSET;							// ���� ��Ʈ
	lf.lfOutPrecision = OUT_CHARACTER_PRECIS;				//��� ��Ȯ��
	lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;				// Ŭ���� ��Ȯ��
	lf.lfQuality = DEFAULT_QUALITY;							// ����� ��
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;		// �ڰ�
	strcpy(lf.lfFaceName, _T("����"));					//�۲��̸�

	return lf;
}

CFont* FontSet::SetFont(const LOGFONT& lf, CDC *pDC) {
	this->cFont.CreateFontIndirect(&lf);
	return pDC->SelectObject(&this->cFont);
}

void FontSet::ApplyFont(TextEdit *textEdit) {
	CDC *pDC = textEdit->GetDC();
	pDC->SetBkMode(TRANSPARENT);
	this->p_oldFont = pDC->SelectObject(&textEdit->cFont);
	pDC->SelectObject(this->p_oldFont);
	textEdit->cFont.DeleteObject();
	textEdit->cFont.CreateFontIndirect(&textEdit->lf);
	pDC->SelectObject(&textEdit->cFont);
	textEdit->ReleaseDC(pDC);
}

FontSet::~FontSet() {
	this->cFont.DeleteObject();
}