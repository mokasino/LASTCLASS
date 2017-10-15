//RightAlignMenuAction.cpp

#include "RightAlignMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"

RightAlignMenuAction::RightAlignMenuAction() {
}
RightAlignMenuAction::~RightAlignMenuAction() {
}
void RightAlignMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit != 0) {
		lastClass->classDiagramForm->textEdit->text->align = DT_RIGHT;
		lastClass->classDiagramForm->textEdit->Invalidate(false);
	}
}