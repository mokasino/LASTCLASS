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
	//pDC->SetTextColor(RGB(255, 255, 255));
	//pDC->SetBkColor(RGB(51, 153, 255));
	//pDC->SetBkMode(OPAQUE);//�ؽ�Ʈ ����� SetBkColor ���

	selected->GetRange(textEdit);
	if (textEdit->selectedY == textEdit->caret->GetRowIndex()) {
		this->selected->SingleLineSelected(textEdit, pDC, &TopCstr, &rt);
		oldBrush = pDC->SelectObject(&cBrush);
		oldPen = pDC->SelectObject(&cPen);
		pDC->Rectangle(rt);
		//pDC->DrawText(TopCstr, &rt, DT_NOCLIP | DT_EXPANDTABS);
	}
	else {
		this->selected->FirstMultiLineSelected(textEdit, pDC, &TopCstr, &rt);
		//pDC->DrawText(TopCstr, &rt, DT_NOCLIP | DT_EXPANDTABS);
		if (this->selected->GetStartRowIndex() + 1 < this->selected->GetEndRowIndex()) {
			this->selected->MiddleMultiLineSelected(textEdit, pDC, &middleCstr, &rt);
			pDC->SelectObject(&cBrush);
			pDC->Rectangle(&rt);
			//pDC->DrawText(middleCstr, &rt, DT_NOCLIP | DT_EXPANDTABS);
		}
		pDC->SelectObject(&textEdit->cFont);
		this->selected->EndMultiLineSelected(textEdit, pDC, &BottomCstr, &rt);
		oldBrush = pDC->SelectObject(&cBrush);
		pDC->Rectangle(&rt);
		//pDC->DrawText(BottomCstr, &rt, DT_NOCLIP | DT_EXPANDTABS);
	}
	pDC->SelectObject(oldBrush);
	cBrush.DeleteObject();
	
	textEdit->copyBuffer = TopCstr + middleCstr + BottomCstr;

}