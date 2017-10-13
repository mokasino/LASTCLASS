#include "FontSettingMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Class.h"
#include <afxdlgs.h>
FontSettingMenuAction::FontSettingMenuAction() {
}
FontSettingMenuAction::~FontSettingMenuAction() {
}
void FontSettingMenuAction::MenuPress(LastClass* lastClass) {
	CFontDialog fontDialog;
	fontDialog.DoModal();
}