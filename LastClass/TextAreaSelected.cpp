//TextAreaSelected.cpp

#include "TextAreaSelected.h"
#include "TextAreaSelectedProcess.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Caret.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "Figure.h"
#include "FontSet.h"
#include "WritingVisitor.h"

TextAreaSelected::TextAreaSelected() {
	this->selected = new TextAreaSelectedProcess;
}
TextAreaSelected::TextAreaSelected(const TextAreaSelected& source) {
}
TextAreaSelected::~TextAreaSelected() {
	if (this->selected != 0) {
		delete selected;
	}
}
void TextAreaSelected::SelectTextArea(TextEdit *textEdit, CDC *pDC) {
	
	CString TopCstr;
	CString middleCstr;
	CString BottomCstr;
	CRect rt;
	CBrush cBrush;
	CBrush *oldBrush;
	cBrush.CreateSolidBrush(RGB(51, 153, 255));
	CPen cPen;
	CPen *oldPen;
	cPen.CreatePen(PS_NULL, 0, RGB(51, 153, 255));

	oldBrush = pDC->SelectObject(&cBrush);
	oldPen = pDC->SelectObject(&cPen);
	pDC->SelectObject(&textEdit->cFont);

	selected->GetRange(textEdit);
	if (textEdit->selectedY == textEdit->caret->GetRowIndex()) {
		this->selected->SingleLineSelected(textEdit, pDC, &TopCstr, &rt);
		pDC->Rectangle(rt);
	}
	else {
		this->selected->FirstMultiLineSelected(textEdit, pDC, &TopCstr, &rt);
		pDC->Rectangle(&rt);
		if (this->selected->GetStartRowIndex() + 1 < this->selected->GetEndRowIndex()) {
			this->selected->MiddleMultiLineSelected(textEdit, pDC, &middleCstr, &rt);
			pDC->Rectangle(&rt);
		}
		this->selected->EndMultiLineSelected(textEdit, pDC, &BottomCstr, &rt);
		pDC->Rectangle(&rt);
	}
	pDC->SelectObject(oldBrush);
	cBrush.DeleteObject();
	pDC->SelectObject(oldPen);
	cPen.DeleteObject();
	
	textEdit->copyBuffer = TopCstr + middleCstr + BottomCstr;

}