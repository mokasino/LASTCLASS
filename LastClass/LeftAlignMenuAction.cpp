//LeftAlignMenuAction.cpp

#include "LeftAlignMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"

LeftAlignMenuAction::LeftAlignMenuAction() {
}
LeftAlignMenuAction::~LeftAlignMenuAction() {
}
void LeftAlignMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit != 0) {
		lastClass->classDiagramForm->textEdit->text->align = DT_LEFT;
		lastClass->classDiagramForm->textEdit->Invalidate();
	}
}