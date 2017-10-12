//WritingVIsitor.cpp

#include "WritingVisitor.h"
#include "Text.h"
#include "MemoBox.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "Template.h"
#include "ClassDiagramForm.h"
#include <afxwin.h>
#include"SelfRelation.h"
#include "Relation.h"

WritingVisitor::WritingVisitor() {
}
WritingVisitor::~WritingVisitor() {
}
void WritingVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
}
void WritingVisitor::Visit(Class *object, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Text* text, CDC* cPaintDc) {
	
	Long fontHeight = cPaintDc->GetTextExtent("��").cy; // rowHeight ���ϴ¹��
	Long textWidth = text->MaxWidth(cPaintDc);
	
	RECT rt = { 0 , 0, textWidth, text->GetLength() * fontHeight };
	cPaintDc->DrawText((CString)text->MakeText().c_str(), &rt, DT_NOCLIP | DT_EXPANDTABS);
}

void  WritingVisitor::Visit(SelfRelation *selfRelation, CDC *cPaintDc) {
	CFont font;
	font.CreateFont(13, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	CFont*  oldFont;
	oldFont = cPaintDc->SelectObject(&font);
	Long i = 0;
	while (i < 5) {
		if (i == 0) {
			RECT rt = { selfRelation->rollNamePoints->GetAt(i).x - 10 , selfRelation->rollNamePoints->GetAt(i).y - 10,
				selfRelation->rollNamePoints->GetAt(i).x + 20,  selfRelation->rollNamePoints->GetAt(i).y + 10 };
			cPaintDc->DrawText((CString)selfRelation->rollNames->GetAt(i).c_str(), &rt, DT_EXPANDTABS);
		}
		else if (i == 1) {
			RECT rt = { selfRelation->rollNamePoints->GetAt(i).x - 30  , selfRelation->rollNamePoints->GetAt(i).y - 10,
				selfRelation->rollNamePoints->GetAt(i).x + 30,  selfRelation->rollNamePoints->GetAt(i).y + 10 };
			cPaintDc->DrawText((CString)selfRelation->rollNames->GetAt(i).c_str(), &rt, DT_EXPANDTABS);
		}
		else {
			RECT rt = { selfRelation->rollNamePoints->GetAt(i).x - 20 , selfRelation->rollNamePoints->GetAt(i).y - 10,
				selfRelation->rollNamePoints->GetAt(i).x + 10,  selfRelation->rollNamePoints->GetAt(i).y + 10 };
			cPaintDc->DrawText((CString)selfRelation->rollNames->GetAt(i).c_str(), &rt, DT_EXPANDTABS);
		}
		i++;
	}
	cPaintDc->SelectObject(oldFont);
	font.DeleteObject();
}

void  WritingVisitor::Visit(Relation *relation, CDC *pDC) {
	CFont font;
	font.CreateFont(13, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	CFont*  oldFont;
	oldFont = pDC->SelectObject(&font);
	Long i = 0;
	while (i < 5) {
		if (i == 1) {
			RECT rt = { relation->rollNamePoints->GetAt(i).x - 40, relation->rollNamePoints->GetAt(i).y - 10 ,
				relation->rollNamePoints->GetAt(i).x + 40,  relation->rollNamePoints->GetAt(i).y + 10 };
			pDC->DrawText((CString)relation->rollNames->GetAt(i).c_str(), &rt, DT_EXPANDTABS);
		}
		else {
			RECT rt = { relation->rollNamePoints->GetAt(i).x - 20, relation->rollNamePoints->GetAt(i).y - 10,
				relation->rollNamePoints->GetAt(i).x + 20,  relation->rollNamePoints->GetAt(i).y + 10 - GabX };
			pDC->DrawText((CString)relation->rollNames->GetAt(i).c_str(), &rt, DT_EXPANDTABS);
		}
		i++;
	}
	pDC->SelectObject(oldFont);
	font.DeleteObject();
}

void WritingVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) { //�����κоƷ��� ������
	RECT rt = { memoBox->GetX() + GabX , memoBox->GetY() + MemoGab + GabY, memoBox->GetX() + memoBox->GetWidth() - GabX, memoBox->GetY() + memoBox->GetHeight() - GabY };
	cPaintDc->DrawText((CString)memoBox->GetContent().c_str(), &rt, DT_NOCLIP | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Selection *selection, CDC *cPaintDc) {
}
void WritingVisitor::Visit(Template *object, CDC *cPaintDc) {
	RECT rt = { object->GetX() + GabX , object->GetY() + GabY, object->GetX() + object->GetWidth() - GabX, object->GetY() + object->GetHeight() - GabY };
	cPaintDc->DrawText((CString)object->GetContent().c_str(), &rt, DT_NOCLIP | DT_EXPANDTABS);
}

void WritingVisitor::Visit(ClassName* className, CDC* cPaintDc) {
	RECT rt = { className->GetX() + GabX , className->GetY() + MemoGab + GabY, className->GetX() + className->GetWidth() - GabX, className->GetY() + className->GetHeight() - GabY };
	cPaintDc->DrawText((CString)className->GetContent().c_str(), &rt, DT_NOCLIP | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {
	RECT rt = { attribute->GetX() + GabX , attribute->GetY() + GabY, attribute->GetX() + attribute->GetWidth() - GabX, attribute->GetY() + attribute->GetHeight() - GabY };
	cPaintDc->DrawText((CString)attribute->GetContent().c_str(), &rt, DT_NOCLIP | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Method* method, CDC* cPaintDc) {
	RECT rt = { method->GetX() + GabX , method->GetY() + GabY, method->GetX() + method->GetWidth() - GabX, method->GetY() + method->GetHeight() - GabY };
	cPaintDc->DrawText((CString)method->GetContent().c_str(), &rt, DT_NOCLIP | DT_EXPANDTABS);
}
void WritingVisitor::Visit(Reception* reception, CDC* cPaintDc) {
	RECT rt = { reception->GetX() + GabX , reception->GetY() + GabY, reception->GetX() + reception->GetWidth() - GabX, reception->GetY() + reception->GetHeight() - GabX };
	cPaintDc->DrawText((CString)reception->GetContent().c_str(), &rt, DT_NOCLIP | DT_EXPANDTABS);
}

void WritingVisitor::Visit(Line *line, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Generalization *generalization, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Realization *realization, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Dependency *dependency, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Association *association, CDC* cPaintDc) {
}
void WritingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Aggregation *aggregation, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Aggregations *aggregations, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Composition *composition, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Compositions *compositions, CDC* cPaintDc) {
}
void WritingVisitor::Visit(MemoLine *memoLine, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfDependency *selfDependency, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfAggregation *selfAggregation, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfAssociation *selfAssociation, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfAggregations *selfAggregations, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfComposition *selfComposition, CDC *cPaintDc) {
}
void WritingVisitor::Visit(SelfCompositions *selfCompositions, CDC *cPaintDc) {
}
