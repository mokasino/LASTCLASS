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

	fontDialog.m_cf.Flags = fontDialog.m_cf.Flags | CF_INITTOLOGFONTSTRUCT;//속성값 설정
	fontDialog.m_cf.lpLogFont = current_lf; //로그폰트 등록

	if (IDOK == fontDialog.DoModal()) {
		//fontDialog.GetWeight;
		//fontDialog.GetFaceName;
		//fontDialog.IsItalic;
		//fontDialog.IsBold;
		//fontDialog.IsStrikeOut;
		//fontDialog.IsUnderline;
		fontDialog.GetCurrentFont(current_lf);	//폰트 대화상자의 폰트 획득;
		current_lf->lfHeight = (-(current_lf->lfHeight) * 100) / 72;
	}											// 로그폰트의 높이(current_lf.lfHeight) = (-(폰트크기(9,10,11,12,13...) * 100 ) / 72
}