//DownArrowKey.cpp

#include "DownArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"
#include "FontSet.h"
#include "ClassDiagramForm.h"

DownArrowKey::DownArrowKey() {
}

DownArrowKey::DownArrowKey(const DownArrowKey& source) {
}

DownArrowKey::~DownArrowKey() {
}

void DownArrowKey::KeyPress(TextEdit *textEdit) {
	CClientDC dc(textEdit);
	dc.SelectObject(&textEdit->cFont);

	if (GetKeyState(VK_SHIFT) >= 0) {
		if (textEdit->flagSelection == 1) {
			textEdit->flagSelection = 0;
		}
	}
	else {
		if (textEdit->flagSelection == 0) {
			textEdit->flagSelection = 1;
			textEdit->selectedX = textEdit->caret->GetCharacterIndex();
			textEdit->selectedY = textEdit->caret->GetRowIndex();
		}
	}

	Long x = textEdit->caret->GetCurrentCaretX();
	Long y = textEdit->caret->GetCurrentCaretY();
	Long previousCharacterIndex = textEdit->caret->GetCharacterIndex();
	Long previousRowIndex = textEdit->caret->GetRowIndex();

	Long rowIndex = y + textEdit->lf.lfHeight;

	textEdit->caret->MoveToPoint(textEdit, &dc, CPoint(x, rowIndex));
	if (previousCharacterIndex == textEdit->text->GetAt(previousRowIndex)->GetLength() &&
		previousRowIndex < textEdit->text->GetLength()) {
		textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
	}
}

void DownArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}