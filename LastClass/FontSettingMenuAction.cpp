#include "FontSettingMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Class.h"

#include <afxdlgs.h>
FontSettingMenuAction::FontSettingMenuAction() {
}
FontSettingMenuAction::~FontSettingMenuAction() {
}
void FontSettingMenuAction::MenuPress(LastClass* lastClass) {
	CFontDialog fontDialog;
	LOGFONT *current_lf = &lastClass->classDiagramForm->lf;

	fontDialog.m_cf.Flags = fontDialog.m_cf.Flags | CF_INITTOLOGFONTSTRUCT;//�Ӽ��� ����
	fontDialog.m_cf.lpLogFont = current_lf; //�α���Ʈ ���

	if (IDOK == fontDialog.DoModal()) {
		//fontDialog.GetWeight;
		//fontDialog.GetFaceName;
		//fontDialog.IsItalic;
		//fontDialog.IsBold;
		//fontDialog.IsStrikeOut;
		//fontDialog.IsUnderline;
		fontDialog.GetCurrentFont(current_lf);	//��Ʈ ��ȭ������ ��Ʈ ȹ��;
		current_lf->lfHeight = (-(current_lf->lfHeight) * 100) / 72;
	}											// �α���Ʈ�� ����(current_lf.lfHeight) = (-(��Ʈũ��(9,10,11,12,13...) * 100 ) / 72
}