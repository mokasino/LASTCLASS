//DrawingVisitor.cpp
#include "ClassDiagramForm.h"
#include "DrawingVisitor.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Template.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoLine.h"
#include "SelfGeneralization.h"
#include "SelfDependency.h"
#include "SelfAggregation.h"
#include "SelfAssociation.h"
#include "SelfAggregations.h"
#include "SelfDirectedAssociation.h"
#include "SelfComposition.h"
#include "SelfCompositions.h"
#include <iostream>
#include "Scroll.h"
#include "DrawRollNameBoxes.h"

using namespace std;

DrawingVisitor::DrawingVisitor() {
}
DrawingVisitor::~DrawingVisitor() {
}
void DrawingVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
}
void DrawingVisitor::Visit(Class *object, CDC* pDC) { //template
	//ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)(CFrameWnd::FindWindow(NULL, "classDiagram"));
	//Long vPos = classDiagramForm->verticalScrollBar->GetScrollPos();
	Long x = object->GetX();
	Long y = object->GetY();
	Long width = object->GetWidth();
	Long height = object->GetHeight();
	
	pDC->Rectangle(x, y, x + width, y + height);
}
void DrawingVisitor::Visit(MemoBox *memoBox, CDC *pDC) {
	Long x = memoBox->GetX();
	Long y = memoBox->GetY();;
	Long width = memoBox->GetWidth();
	Long height = memoBox->GetHeight();

	CPoint pts2[5];
	pts2[0].x = static_cast<LONG>(x + 15); // ����
	pts2[0].y = static_cast<LONG>(y);

	pts2[1].x = static_cast<LONG>(x); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(y + 15);

	pts2[2].x = static_cast<LONG>(x); // �Ʒ���
	pts2[2].y = static_cast<LONG>(y + height);

	pts2[3].x = static_cast<LONG>(x + width); // ����
	pts2[3].y = static_cast<LONG>(y + height);

	pts2[4].x = static_cast<LONG>(x + width); // ����
	pts2[4].y = static_cast<LONG>(y);

	pDC->Polygon(pts2, 5);

	pDC->MoveTo(pts2[0].x, pts2[0].y);
	pDC->LineTo(pts2[0].x, pts2[0].y + 15);

	pDC->MoveTo(pts2[1].x, pts2[1].y);
	pDC->LineTo(pts2[0].x, pts2[0].y + 15);
}
void DrawingVisitor::Visit(Selection *selection, CDC *pDC) {
	Long i = 0;
	while (i < selection->GetLength()) {
		if (dynamic_cast<Class*>(selection->GetAt(i))) {
			Class *object = static_cast<Class*>(selection->GetAt(i));
			if (object->GetTempletePosition() == -1) {
				pDC->Rectangle(//�»�
					object->GetX() - 3,
					object->GetY() - 3,
					object->GetX() + 6,
					object->GetY() + 6);
				pDC->Rectangle(//���
					object->GetX() + object->GetWidth() - 6,
					object->GetY() - 3,
					object->GetX() + object->GetWidth() + 3,
					object->GetY() + 6);
				pDC->Rectangle(//�߻�
					object->GetX() + object->GetWidth() / 2 - 4,
					object->GetY() - 3,
					object->GetX() + object->GetWidth() / 2 + 5,
					object->GetY() + 6);
				pDC->Rectangle(//����
					object->GetX() + object->GetWidth() / 2 - 4,
					object->GetY() + object->GetHeight() - 6,
					object->GetX() + object->GetWidth() / 2 + 5,
					object->GetY() + object->GetHeight() + 3);
				pDC->Rectangle(//����
					object->GetX() - 3,
					object->GetY() + object->GetHeight() / 2 - 4,
					object->GetX() + 6,
					object->GetY() + object->GetHeight() / 2 + 5);
				pDC->Rectangle(//����
					object->GetX() + object->GetWidth() - 6,
					object->GetY() + object->GetHeight() / 2 - 4,
					object->GetX() + object->GetWidth() + 3,
					object->GetY() + object->GetHeight() / 2 + 5);
				pDC->Rectangle(//����
					object->GetX() - 3,
					object->GetY() + object->GetHeight() - 6,
					object->GetX() + 6,
					object->GetY() + object->GetHeight() + 3);
				pDC->Rectangle(//����
					object->GetX() + object->GetWidth() - 6,
					object->GetY() + object->GetHeight() - 6,
					object->GetX() + object->GetWidth() + 3,
					object->GetY() + object->GetHeight() + 3);

			}
			else {
				Long j = 0;
				while (j < object->GetLength()) {
					if (dynamic_cast<Template*>(object->GetAt(j))) {
						Template *templete = static_cast<Template*>(object->GetAt(j));
						CPen pen;
						pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
						CPen *oldPen = pDC->SelectObject(&pen);
						pDC->SetBkMode(TRANSPARENT);
						pDC->MoveTo(object->GetX(), templete->GetY());
						pDC->LineTo(templete->GetX(), templete->GetY());

						pDC->MoveTo(object->GetX(), templete->GetY());
						pDC->LineTo(object->GetX(), object->GetY());

						pDC->MoveTo(templete->GetX() + templete->GetWidth(), templete->GetY() + templete->GetHeight());
						pDC->LineTo(templete->GetX() + templete->GetWidth(), object->GetY() + object->GetHeight());

						pDC->MoveTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());
						pDC->LineTo(templete->GetX() + templete->GetWidth(), object->GetY() + object->GetHeight());
						pDC->SelectObject(oldPen);
						pen.DeleteObject();

						pDC->Rectangle(//�»�
							object->GetX() - 3,
							templete->GetY() - 3,
							object->GetX() + 6,
							templete->GetY() + 6);
						pDC->Rectangle(//���
							templete->GetX() + templete->GetWidth() - 6,
							templete->GetY() - 3,
							templete->GetX() + templete->GetWidth() + 3,
							templete->GetY() + 6);
						pDC->Rectangle(//����
							object->GetX() - 3,
							object->GetY() + object->GetHeight() - 6,
							object->GetX() + 6,
							object->GetY() + object->GetHeight() + 3);
						pDC->Rectangle(//����
							templete->GetX() + templete->GetWidth() - 6,
							object->GetY() + object->GetHeight() - 6,
							templete->GetX() + templete->GetWidth() + 3,
							object->GetY() + object->GetHeight() + 3);

						pDC->Rectangle(//�߻�
							object->GetX() + (templete->GetX() + templete->GetWidth() - object->GetX()) / 2 - 4,
							templete->GetY() - 3,
							object->GetX() + (templete->GetX() + templete->GetWidth() - object->GetX()) / 2 + 5,
							templete->GetY() + 6);
						pDC->Rectangle(//����
							object->GetX() + (templete->GetX() + templete->GetWidth() - object->GetX()) / 2 - 4,
							object->GetY() + object->GetHeight() - 6,
							object->GetX() + (templete->GetX() + templete->GetWidth() - object->GetX()) / 2 + 5,
							object->GetY() + object->GetHeight() + 3);
						pDC->Rectangle(//����
							object->GetX() - 3,
							templete->GetY() + (object->GetY() + object->GetHeight() - templete->GetY()) / 2 - 4,
							object->GetX() + 6,
							templete->GetY() + (object->GetY() + object->GetHeight() - templete->GetY()) / 2 + 5);
						pDC->Rectangle(//����
							templete->GetX() + templete->GetWidth() - 6,
							templete->GetY() + (object->GetY() + object->GetHeight() - templete->GetY()) / 2 - 4,
							templete->GetX() + templete->GetWidth() + 3,
							templete->GetY() + (object->GetY() + object->GetHeight() - templete->GetY()) / 2 + 5);
					}
					j++;

				}

			}
		}

		if (dynamic_cast<MemoBox*>(selection->GetAt(i))) {
			MemoBox *memoBox = static_cast<MemoBox*>(selection->GetAt(i));
			pDC->Rectangle(//�»�
				memoBox->GetX() - 3,
				memoBox->GetY() - 3,
				memoBox->GetX() + 6,
				memoBox->GetY() + 6);
			pDC->Rectangle(//���
				memoBox->GetX() + memoBox->GetWidth() - 6,
				memoBox->GetY() - 3,
				memoBox->GetX() + memoBox->GetWidth() + 3,
				memoBox->GetY() + 6);
			pDC->Rectangle(//�߻�
				memoBox->GetX() + memoBox->GetWidth() / 2 - 4,
				memoBox->GetY() - 3,
				memoBox->GetX() + memoBox->GetWidth() / 2 + 5,
				memoBox->GetY() + 6);
			pDC->Rectangle(//����
				memoBox->GetX() + memoBox->GetWidth() / 2 - 4,
				memoBox->GetY() + memoBox->GetHeight() - 6,
				memoBox->GetX() + memoBox->GetWidth() / 2 + 5,
				memoBox->GetY() + memoBox->GetHeight() + 3);
			pDC->Rectangle(//����
				memoBox->GetX() - 3,
				memoBox->GetY() + memoBox->GetHeight() / 2 - 4,
				memoBox->GetX() + 6,
				memoBox->GetY() + memoBox->GetHeight() / 2 + 5);
			pDC->Rectangle(//����
				memoBox->GetX() + memoBox->GetWidth() - 6,
				memoBox->GetY() + memoBox->GetHeight() / 2 - 4,
				memoBox->GetX() + memoBox->GetWidth() + 3,
				memoBox->GetY() + memoBox->GetHeight() / 2 + 5);
			pDC->Rectangle(//����
				memoBox->GetX() - 3,
				memoBox->GetY() + memoBox->GetHeight() - 6,
				memoBox->GetX() + 6,
				memoBox->GetY() + memoBox->GetHeight() + 3);
			pDC->Rectangle(//����
				memoBox->GetX() + memoBox->GetWidth() - 6,
				memoBox->GetY() + memoBox->GetHeight() - 6,
				memoBox->GetX() + memoBox->GetWidth() + 3,
				memoBox->GetY() + memoBox->GetHeight() + 3);
		}
		Long j = 0;
		//���������̴� ���� �����ؾ���
		if (dynamic_cast<Relation*>(selection->GetAt(i))) {
			if (static_cast<Relation*>(selection->GetAt(i))->GetLength() == 0) {
				pDC->Rectangle(selection->GetAt(i)->GetX() - 5,
					selection->GetAt(i)->GetY() - 5,
					selection->GetAt(i)->GetX() + 5,
					selection->GetAt(i)->GetY() + 5);
				pDC->Rectangle(selection->GetAt(i)->GetX() + (selection->GetAt(i)->GetWidth() / 2) - 5,
					selection->GetAt(i)->GetY() + (selection->GetAt(i)->GetHeight() / 2) - 5,
					selection->GetAt(i)->GetX() + (selection->GetAt(i)->GetWidth() / 2) + 5,
					selection->GetAt(i)->GetY() + (selection->GetAt(i)->GetHeight() / 2) + 5);
				pDC->Rectangle(selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() - 5,
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() - 5,
					selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() + 5,
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() + 5);
			}
			else {
				pDC->Rectangle(selection->GetAt(i)->GetX() - 5,
					selection->GetAt(i)->GetY() - 5,
					selection->GetAt(i)->GetX() + 5,
					selection->GetAt(i)->GetY() + 5);
				pDC->Rectangle(selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() - 5,
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() - 5,
					selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() + 5,
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() + 5);
				while (j < static_cast<Relation*>(selection->GetAt(i))->GetLength()) {
					CPoint cPoint = static_cast<Relation*>(selection->GetAt(i))->GetAt(j);
					pDC->Rectangle(cPoint.x - 5,
						cPoint.y - 5,
						cPoint.x + 5,
						cPoint.y + 5);
					j++;
				}
			}
			DrawRollNameBoxes *drawRollNameBoxes = DrawRollNameBoxes::Instance();
			CPoint cPoint;
			Relation* relationLine = static_cast<Relation*>(selection->GetAt(i));
			if (!dynamic_cast<MemoLine*>(relationLine)) {
				if (relationLine->GetLength() > 0) { // ���μ��� ������
					drawRollNameBoxes->DrawFirstRollNameBox(relationLine, pDC);
					drawRollNameBoxes->DrawSecondRollNameBox(relationLine, pDC);
					drawRollNameBoxes->DrawThirdRollNameBox(relationLine, pDC);
					drawRollNameBoxes->DrawFourthRollNameBox(relationLine, pDC);
					drawRollNameBoxes->DrawFifthRollNameBox(relationLine, pDC);
				}
				else { // ���μ��� ������
					drawRollNameBoxes->DrawBoxesWithoutCurvedLine(relationLine, pDC);
				}
			}
		}

		if (dynamic_cast<SelfRelation*>(selection->GetAt(i))) {
			SelfRelation *selfRelation = static_cast<SelfRelation*>(selection->GetAt(i));
			Long x;
			Long y;
			Long x1;
			Long y1;

			x = selfRelation->GetX() - 5;
			y = selfRelation->GetY() - 45;
			x1 = selfRelation->GetX() + 5;
			y1 = selfRelation->GetY() - 35;
			pDC->Rectangle(x, y, x1, y1);

			x = selfRelation->GetX() + 75;
			y = selfRelation->GetY() - 45;
			x1 = selfRelation->GetX() + 85;
			y1 = selfRelation->GetY() - 35;
			pDC->Rectangle(x, y, x1, y1);

			x = selfRelation->GetX() + 75;
			y = selfRelation->GetY() + 35;
			x1 = selfRelation->GetX() + 85;
			y1 = selfRelation->GetY() + 45;
			pDC->Rectangle(x, y, x1, y1);

			DrawRollNameBoxes *drawRollNameBoxes = DrawRollNameBoxes::Instance();
			CPoint cPoint;
			SelfRelation* selfRelationLine = static_cast<SelfRelation*>(selection->GetAt(i));
			drawRollNameBoxes->DrawSelfRelationRollNameBox(selfRelationLine, pDC);
		}
		i++;
	}
}

void DrawingVisitor::Visit(Template *object, CDC *pDC) {
	Long x = object->GetX();
	Long y = object->GetY();;
	Long width = object->GetWidth();
	Long height = object->GetHeight();

	pDC->Rectangle(x, y, x + width, y + height);
}
void DrawingVisitor::Visit(ClassName* className, CDC* pDC) {
}
void DrawingVisitor::Visit(Attribute* attribute, CDC* pDC) {
}
void DrawingVisitor::Visit(Method* method, CDC* pDC) {
}
void DrawingVisitor::Visit(Reception* reception, CDC* pDC) {
}
void DrawingVisitor::Visit(Line *line, CDC* pDC) {
	Long x = line->GetX();
	Long  y = line->GetY();;
	Long width = line->GetWidth();

	pDC->MoveTo(x, y);
	pDC->LineTo(x + width, y);
}
void DrawingVisitor::Visit(Generalization *generalization, CDC* pDC) {


	Long startX = generalization->GetX();
	Long startY = generalization->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < generalization->GetLength()) {
		endX = generalization->GetAt(i).x;
		endY = generalization->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = generalization->GetWidth() + generalization->GetX();
	endY = generalization->GetHeight() + generalization->GetY();

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����

	CPoint pts[3];

	pts[0].x = (endX); //���콺 ������ġ ��
	pts[0].y = (endY);

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->SelectObject(&white);
	pDC->Polygon(pts, 3);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Realization *realization, CDC* pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);


	Long startX = realization->GetX();
	Long startY = realization->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < realization->GetLength()) {
		endX = realization->GetAt(i).x;
		endY = realization->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = realization->GetWidth() + realization->GetX();
	endY = realization->GetHeight() + realization->GetY();

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����

	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->SelectObject(&white);
	pDC->Polygon(pts, 3);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Dependency *dependency, CDC* pDC) {

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);

	Long startX = dependency->GetX();
	Long startY = dependency->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < dependency->GetLength()) {
		endX = dependency->GetAt(i).x;
		endY = dependency->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = dependency->GetWidth() + dependency->GetX();
	endY = dependency->GetHeight() + dependency->GetY();

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����

	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);
}
void DrawingVisitor::Visit(Association *association, CDC* pDC) {

	Long startX = association->GetX();
	Long startY = association->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < association->GetLength()) {
		endX = association->GetAt(i).x;
		endY = association->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = association->GetWidth() + association->GetX();
	endY = association->GetHeight() + association->GetY();
	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);
}
void DrawingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* pDC) {

	Long startX = directedAssociation->GetX();
	Long startY = directedAssociation->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < directedAssociation->GetLength()) {
		endX = directedAssociation->GetAt(i).x;
		endY = directedAssociation->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = directedAssociation->GetWidth() + directedAssociation->GetX();
	endY = directedAssociation->GetHeight() + directedAssociation->GetY();
	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����

	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);
}
void DrawingVisitor::Visit(Aggregation *aggregation, CDC* pDC) {

	Long startX = aggregation->GetX();
	Long startY = aggregation->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < aggregation->GetLength()) {
		endX = aggregation->GetAt(i).x;
		endY = aggregation->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = aggregation->GetWidth() + aggregation->GetX();
	endY = aggregation->GetHeight() + aggregation->GetY();

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);
	//�������� ����ġ
	startX = aggregation->GetX();
	startY = aggregation->GetY();

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	startX = aggregation->GetX();
	startY = aggregation->GetY();
	if (aggregation->GetLength() != 0) {
		endX = aggregation->GetAt(0).x;
		endY = aggregation->GetAt(0).y;
	}
	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(9 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (startY)-(9 * (startY - endY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (endX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - endY) / distance);


	pDC->SelectObject(&white);
	pDC->Polygon(pts2, 4);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Aggregations *aggregations, CDC* pDC) {

	Long startX = aggregations->GetX();
	Long startY = aggregations->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < aggregations->GetLength()) {
		endX = aggregations->GetAt(i).x;
		endY = aggregations->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = aggregations->GetWidth() + aggregations->GetX();
	endY = aggregations->GetHeight() + aggregations->GetY();


	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	//�������� ����ġ
	if (aggregations->GetLength() != 0) {
		startX = aggregations->GetAt(aggregations->GetLength() - 1).x;
		startY = aggregations->GetAt(aggregations->GetLength() - 1).y;
	}
	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����

	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);


	//������� ȭ��ǥ �������� ������
	startX = aggregations->GetX();
	startY = aggregations->GetY();
	if (aggregations->GetLength() != 0) {
		endX = aggregations->GetAt(0).x;
		endY = aggregations->GetAt(0).y;
	}
	degree = atan2(endX - startX, startY - endY);
	distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	dX = (startX)+(9 * (endX - startX) / distance); //�ڷ� �� ������ x
	dY = (startY)-(9 * (startY - endY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];
	//�� �� ��:�� �� ��
	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(startX); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(startY);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (endX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - endY) / distance);

	pDC->SelectObject(&white);
	pDC->Polygon(pts2, 4);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Composition *composition, CDC* pDC) {
	Long startX = composition->GetX();
	Long startY = composition->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < composition->GetLength()) {
		endX = composition->GetAt(i).x;
		endY = composition->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = composition->GetWidth() + composition->GetX();
	endY = composition->GetHeight() + composition->GetY();

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	//�������� ����ġ
	startX = composition->GetX();
	startY = composition->GetY();

	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	startX = composition->GetX();
	startY = composition->GetY();
	if (composition->GetLength() != 0) {
		endX = composition->GetAt(0).x;
		endY = composition->GetAt(0).y;
	}

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(9 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (startY)-(9 * (startY - endY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (endX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - endY) / distance);

	pDC->SelectObject(&black);
	pDC->Polygon(pts2, 4);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Compositions *compositions, CDC* pDC) {

	Long startX = compositions->GetX();
	Long startY = compositions->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < compositions->GetLength()) {
		endX = compositions->GetAt(i).x;
		endY = compositions->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = compositions->GetWidth() + compositions->GetX();
	endY = compositions->GetHeight() + compositions->GetY();

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	//�������� ����ġ
	if (compositions->GetLength() != 0) {
		startX = compositions->GetAt(compositions->GetLength() - 1).x;
		startY = compositions->GetAt(compositions->GetLength() - 1).y;
	}

	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // ����


	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����
	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);

	//������� ȭ��ǥ �������� ������


	startX = compositions->GetX();
	startY = compositions->GetY();
	if (compositions->GetLength() != 0) {
		endX = compositions->GetAt(0).x;
		endY = compositions->GetAt(0).y;
	}
	degree = atan2(endX - startX, startY - endY);
	distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	dX = (startX)+(9 * (endX - startX) / distance); //�ڷ� �� ������ x
	dY = (startY)-(9 * (startY - endY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];
	//�� �� ��:�� �� ��
	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(startX); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(startY);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (endX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - endY) / distance);

	pDC->SelectObject(&black);
	pDC->Polygon(pts2, 4);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(MemoLine *memoLine, CDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);

	Long startX = memoLine->GetX();
	Long startY = memoLine->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < memoLine->GetLength()) {
		endX = memoLine->GetAt(i).x;
		endY = memoLine->GetAt(i).y;
		pDC->MoveTo(startX, startY);
		pDC->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = memoLine->GetWidth() + memoLine->GetX();
	endY = memoLine->GetHeight() + memoLine->GetY();

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}
void DrawingVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *pDC) {

	pDC->MoveTo(selfGeneralization->GetX(), selfGeneralization->GetY());
	pDC->LineTo(selfGeneralization->GetX(), selfGeneralization->GetY() - 40);

	pDC->MoveTo(selfGeneralization->GetX(), selfGeneralization->GetY() - 40);
	pDC->LineTo(selfGeneralization->GetX() + 80, selfGeneralization->GetY() - 40);

	pDC->MoveTo(selfGeneralization->GetX() + 80, selfGeneralization->GetY() - 40);
	pDC->LineTo(selfGeneralization->GetX() + 80, selfGeneralization->GetY() + 40);

	pDC->MoveTo(selfGeneralization->GetX() + 80, selfGeneralization->GetY() + 40);
	pDC->LineTo(selfGeneralization->GetX() + 30, selfGeneralization->GetY() + 40);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	Long startX = selfGeneralization->GetX() + 60;
	Long startY = selfGeneralization->GetY() + 40;
	Long endX = selfGeneralization->GetX() + 30;
	Long endY = selfGeneralization->GetY() + 40;

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����
	CPoint pts[3];

	pts[0].x = (endX); //���콺 ������ġ ��
	pts[0].y = (endY);

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->SelectObject(&white);
	pDC->Polygon(pts, 3);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(SelfDependency *selfDependency, CDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);

	pDC->MoveTo(selfDependency->GetX(), selfDependency->GetY());
	pDC->LineTo(selfDependency->GetX(), selfDependency->GetY() - 40);

	pDC->MoveTo(selfDependency->GetX(), selfDependency->GetY() - 40);
	pDC->LineTo(selfDependency->GetX() + 80, selfDependency->GetY() - 40);

	pDC->MoveTo(selfDependency->GetX() + 80, selfDependency->GetY() - 40);
	pDC->LineTo(selfDependency->GetX() + 80, selfDependency->GetY() + 40);

	pDC->MoveTo(selfDependency->GetX() + 80, selfDependency->GetY() + 40);
	pDC->LineTo(selfDependency->GetX() + 30, selfDependency->GetY() + 40);

	Long startX = selfDependency->GetX() + 60;
	Long startY = selfDependency->GetY() + 40;
	Long endX = selfDependency->GetX() + 30;
	Long endY = selfDependency->GetY() + 40;

	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����
	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);
}
void DrawingVisitor::Visit(SelfAggregation *selfAggregation, CDC *pDC) {
	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	pDC->MoveTo(selfAggregation->GetX(), selfAggregation->GetY());
	pDC->LineTo(selfAggregation->GetX(), selfAggregation->GetY() - 40);

	pDC->MoveTo(selfAggregation->GetX(), selfAggregation->GetY() - 40);
	pDC->LineTo(selfAggregation->GetX() + 80, selfAggregation->GetY() - 40);

	pDC->MoveTo(selfAggregation->GetX() + 80, selfAggregation->GetY() - 40);
	pDC->LineTo(selfAggregation->GetX() + 80, selfAggregation->GetY() + 40);

	pDC->MoveTo(selfAggregation->GetX() + 80, selfAggregation->GetY() + 40);
	pDC->LineTo(selfAggregation->GetX() + 30, selfAggregation->GetY() + 40);

	Long startX = selfAggregation->GetX();
	Long startY = selfAggregation->GetY();
	Long endX = selfAggregation->GetX();
	Long endY = selfAggregation->GetY() - 30;

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(9 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (startY)-(9 * (startY - endY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (endX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - endY) / distance);

	pDC->SelectObject(&white);
	pDC->Polygon(pts2, 4);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}

void DrawingVisitor::Visit(SelfAssociation *selfAssociation, CDC *pDC) {

	pDC->MoveTo(selfAssociation->GetX(), selfAssociation->GetY());
	pDC->LineTo(selfAssociation->GetX(), selfAssociation->GetY() - 40);

	pDC->MoveTo(selfAssociation->GetX(), selfAssociation->GetY() - 40);
	pDC->LineTo(selfAssociation->GetX() + 80, selfAssociation->GetY() - 40);

	pDC->MoveTo(selfAssociation->GetX() + 80, selfAssociation->GetY() - 40);
	pDC->LineTo(selfAssociation->GetX() + 80, selfAssociation->GetY() + 40);

	pDC->MoveTo(selfAssociation->GetX() + 80, selfAssociation->GetY() + 40);
	pDC->LineTo(selfAssociation->GetX() + 30, selfAssociation->GetY() + 40);
}

void DrawingVisitor::Visit(SelfAggregations *selfAggregations, CDC *pDC) {
	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	pDC->MoveTo(selfAggregations->GetX(), selfAggregations->GetY());
	pDC->LineTo(selfAggregations->GetX(), selfAggregations->GetY() - 40);

	pDC->MoveTo(selfAggregations->GetX(), selfAggregations->GetY() - 40);
	pDC->LineTo(selfAggregations->GetX() + 80, selfAggregations->GetY() - 40);

	pDC->MoveTo(selfAggregations->GetX() + 80, selfAggregations->GetY() - 40);
	pDC->LineTo(selfAggregations->GetX() + 80, selfAggregations->GetY() + 40);

	pDC->MoveTo(selfAggregations->GetX() + 80, selfAggregations->GetY() + 40);
	pDC->LineTo(selfAggregations->GetX() + 30, selfAggregations->GetY() + 40);

	Long startX = selfAggregations->GetX() + 60;
	Long startY = selfAggregations->GetY() + 40;
	Long endX = selfAggregations->GetX() + 30;
	Long endY = selfAggregations->GetY() + 40;

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����
	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);

	//������� ȭ��ǥ �������� ������
	//����
	startX = selfAggregations->GetX();
	startY = selfAggregations->GetY();
	endX = selfAggregations->GetX();
	endY = selfAggregations->GetY() - 30;

	degree = atan2(endX - startX, startY - endY); // ����

	distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	dX = (startX)+(9 * (endX - startX) / distance); //�ڷ� �� ������ x
	dY = (startY)-(9 * (startY - endY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (endX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - endY) / distance);

	pDC->SelectObject(&white);
	pDC->Polygon(pts2, 4);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *pDC) {

	pDC->MoveTo(selfDirectedAssociation->GetX(), selfDirectedAssociation->GetY());
	pDC->LineTo(selfDirectedAssociation->GetX(), selfDirectedAssociation->GetY() - 40);

	pDC->MoveTo(selfDirectedAssociation->GetX(), selfDirectedAssociation->GetY() - 40);
	pDC->LineTo(selfDirectedAssociation->GetX() + 80, selfDirectedAssociation->GetY() - 40);

	pDC->MoveTo(selfDirectedAssociation->GetX() + 80, selfDirectedAssociation->GetY() - 40);
	pDC->LineTo(selfDirectedAssociation->GetX() + 80, selfDirectedAssociation->GetY() + 40);

	pDC->MoveTo(selfDirectedAssociation->GetX() + 80, selfDirectedAssociation->GetY() + 40);
	pDC->LineTo(selfDirectedAssociation->GetX() + 30, selfDirectedAssociation->GetY() + 40);

	Long startX = selfDirectedAssociation->GetX() + 60;
	Long startY = selfDirectedAssociation->GetY() + 40;
	Long endX = selfDirectedAssociation->GetX() + 30;
	Long endY = selfDirectedAssociation->GetY() + 40;

	pDC->MoveTo(startX, startY);
	pDC->LineTo(endX, endY);

	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����
	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);
}
void DrawingVisitor::Visit(SelfComposition *selfComposition, CDC *pDC) {
	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	pDC->MoveTo(selfComposition->GetX(), selfComposition->GetY());
	pDC->LineTo(selfComposition->GetX(), selfComposition->GetY() - 40);

	pDC->MoveTo(selfComposition->GetX(), selfComposition->GetY() - 40);
	pDC->LineTo(selfComposition->GetX() + 80, selfComposition->GetY() - 40);

	pDC->MoveTo(selfComposition->GetX() + 80, selfComposition->GetY() - 40);
	pDC->LineTo(selfComposition->GetX() + 80, selfComposition->GetY() + 40);

	pDC->MoveTo(selfComposition->GetX() + 80, selfComposition->GetY() + 40);
	pDC->LineTo(selfComposition->GetX() + 30, selfComposition->GetY() + 40);

	Long startX = selfComposition->GetX();
	Long startY = selfComposition->GetY();
	Long endX = selfComposition->GetX();
	Long endY = selfComposition->GetY() - 30;
	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(9 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (startY)-(9 * (startY - endY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (endX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - endY) / distance);

	pDC->SelectObject(&black);
	pDC->Polygon(pts2, 4);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(SelfCompositions *selfCompositions, CDC *pDC) {

	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	pDC->MoveTo(selfCompositions->GetX(), selfCompositions->GetY());
	pDC->LineTo(selfCompositions->GetX(), selfCompositions->GetY() - 40);

	pDC->MoveTo(selfCompositions->GetX(), selfCompositions->GetY() - 40);
	pDC->LineTo(selfCompositions->GetX() + 80, selfCompositions->GetY() - 40);

	pDC->MoveTo(selfCompositions->GetX() + 80, selfCompositions->GetY() - 40);
	pDC->LineTo(selfCompositions->GetX() + 80, selfCompositions->GetY() + 40);

	pDC->MoveTo(selfCompositions->GetX() + 80, selfCompositions->GetY() + 40);
	pDC->LineTo(selfCompositions->GetX() + 30, selfCompositions->GetY() + 40);

	Long startX = selfCompositions->GetX() + 60;
	Long startY = selfCompositions->GetY() + 40;
	Long endX = selfCompositions->GetX() + 30;
	Long endY = selfCompositions->GetY() + 40;
	double degree = atan2(endX - startX, startY - endY); // ����

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (endX)-(10 * (endX - startX) / distance); //�ڷ� �� ������ x
	double dY = (endY)+(10 * (startY - endY) / distance); //�ڷ� �� ������ y

														  // ���� ����
	CPoint pts[3];

	pts[0].x = endX; //���콺 ������ġ ��
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);

	//������� ȭ��ǥ �������� ������
	//����
	startX = selfCompositions->GetX();
	startY = selfCompositions->GetY();
	endX = selfCompositions->GetX();
	endY = selfCompositions->GetY() - 30;

	degree = atan2(endX - startX, startY - endY); // ����

	distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	dX = (startX)+(9 * (endX - startX) / distance); //�ڷ� �� ������ x
	dY = (startY)-(9 * (startY - endY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (endX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - endY) / distance);

	pDC->SelectObject(&black);
	pDC->Polygon(pts2, 4);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(SelfRelation *selfRelation, CDC *cPaintDc) {
}
void DrawingVisitor::Visit(Relation *relation, CDC *cPaintDc) {
}
void DrawingVisitor::Visit(Text* text, CDC* pDC) {
}