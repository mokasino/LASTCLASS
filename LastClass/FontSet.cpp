//FontSet.cpp

#include "FontSet.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"

FontSet::FontSet() {
	this->lf = { 0, };
}

FontSet::FontSet(LOGFONT *lf) { // ClassDiagramForm->OnCreate
	//Set Default
	lf->lfHeight = 25;										// �۲��� ����
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
}

LOGFONT& FontSet::RelationFontSet() {
	//Set Default
	lf.lfHeight = 13;										// �۲��� ����
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

FontSet::~FontSet() {
}