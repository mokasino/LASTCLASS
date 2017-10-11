//FontSet.cpp

#include "FontSet.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"

FontSet::FontSet() {
	this->classDiagramForm = 0;
}

FontSet::FontSet(ClassDiagramForm *classDiagramForm) {
	this->classDiagramForm = classDiagramForm;
	this->lf.lfHeight = 25;										// �۲��� ����
	this->lf.lfWidth = 0;										// �۲��� �ʺ�
	this->lf.lfEscapement = 0;									// ����
	this->lf.lfOrientation = 0;									// ȸ������
	this->lf.lfWeight = FW_NORMAL;								// ����
	this->lf.lfItalic = FALSE;									// ����Ӳ�
	this->lf.lfUnderline = FALSE;								// ����
	this->lf.lfStrikeOut = FALSE;								// ��Ҽ�
	this->lf.lfCharSet = DEFAULT_CHARSET;						// ���� ��Ʈ
	this->lf.lfOutPrecision = OUT_CHARACTER_PRECIS;				//��� ��Ȯ��
	this->lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;			// Ŭ���� ��Ȯ��
	this->lf.lfQuality = DEFAULT_QUALITY;						// ����� ��
	this->lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	// �ڰ�
	strcpy(this->lf.lfFaceName, _T("���� ���"));				//�۲��̸�
	this->cFont.CreateFontIndirect(&this->lf);
	classDiagramForm->SetFont(&this->cFont, TRUE);
}

FontSet::FontSet(const FontSet& source) {
}

LOGFONT& FontSet::RelationFontSet() {
	this->lf.lfHeight = 13;										// �۲��� ����
	this->lf.lfWidth = 0;										// �۲��� �ʺ�
	this->lf.lfEscapement = 0;									// ����
	this->lf.lfOrientation = 0;									// ȸ������
	this->lf.lfWeight = FW_NORMAL;								// ����
	this->lf.lfItalic = FALSE;									// ����Ӳ�
	this->lf.lfUnderline = FALSE;								// ����
	this->lf.lfStrikeOut = FALSE;								// ��Ҽ�
	this->lf.lfCharSet = DEFAULT_CHARSET;						// ���� ��Ʈ
	this->lf.lfOutPrecision = OUT_CHARACTER_PRECIS;				//��� ��Ȯ��
	this->lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;			// Ŭ���� ��Ȯ��
	this->lf.lfQuality = DEFAULT_QUALITY;						// ����� ��
	this->lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	// �ڰ�
	strcpy(this->lf.lfFaceName, _T("����"));					//�۲��̸�

	this->cFont.CreateFontIndirect(&this->lf);

	return this->lf;
}
LOGFONT& FontSet::ClassFontSet() {
	this->lf.lfHeight = 25;										// �۲��� ����
	this->lf.lfWidth = 0;										// �۲��� �ʺ�
	this->lf.lfEscapement = 0;									// ����
	this->lf.lfOrientation = 0;									// ȸ������
	this->lf.lfWeight = FW_NORMAL;								// ����
	this->lf.lfItalic = FALSE;									// ����Ӳ�
	this->lf.lfUnderline = FALSE;								// ����
	this->lf.lfStrikeOut = FALSE;								// ��Ҽ�
	this->lf.lfCharSet = DEFAULT_CHARSET;						// ���� ��Ʈ
	this->lf.lfOutPrecision = OUT_CHARACTER_PRECIS;				//��� ��Ȯ��
	this->lf.lfClipPrecision = CLIP_CHARACTER_PRECIS;			// Ŭ���� ��Ȯ��
	this->lf.lfQuality = DEFAULT_QUALITY;						// ����� ��
	this->lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;	// �ڰ�
	strcpy(this->lf.lfFaceName, _T("���� ���"));				//�۲��̸�

	this->cFont.CreateFontIndirect(&this->lf);

	return this->lf;
}

CFont& FontSet::SetFont(TextEdit *textEdit, CDC *pDC) {
	textEdit->SetFont(&this->cFont, TRUE);
	this->oldFont = pDC->SelectObject(&this->cFont);

	return static_cast<CFont&>(this->cFont);
}

FontSet::~FontSet() {
}