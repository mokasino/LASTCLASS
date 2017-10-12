//UpArrowKey.cpp

#include "UpArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"
#include "FontSet.h"
#include "ClassDiagramForm.h"

UpArrowKey::UpArrowKey() {
}

UpArrowKey::UpArrowKey(const UpArrowKey& source) {
}

UpArrowKey::~UpArrowKey() {
}

void UpArrowKey::KeyPress(TextEdit *textEdit) {
	CClientDC dc(textEdit);
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
	CFont cFont;
	cFont.CreateFontIndirect(&textEdit->lf);
	textEdit->p_oldFont = dc.SelectObject(&cFont);

	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작

	Long x = textEdit->caret->GetCurrentCaretX();
	Long y = textEdit->caret->GetCurrentCaretY();
	Long previousCharacterIndex = textEdit->caret->GetCharacterIndex();
	Long previousRowIndex = textEdit->caret->GetRowIndex();

	Long rowIndex = y - textEdit->lf.lfHeight;

	textEdit->caret->MoveToPoint(textEdit, &dc, CPoint(x, rowIndex));
	if (previousCharacterIndex == textEdit->text->GetAt(previousRowIndex)->GetLength() &&
		previousRowIndex > 0) {
		textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
	}
	dc.SelectObject(textEdit->p_oldFont);
	cFont.DeleteObject(); // 폰트
}

void UpArrowKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}