//CenterAlignMenuAction.cpp

#include "CenterAlignMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"

CenterAlignMenuAction::CenterAlignMenuAction() {
}
CenterAlignMenuAction::~CenterAlignMenuAction() {
}
void CenterAlignMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit != 0) {
		lastClass->classDiagramForm->textEdit->text->align = DT_CENTER;
		lastClass->classDiagramForm->textEdit->Invalidate();
	}
}