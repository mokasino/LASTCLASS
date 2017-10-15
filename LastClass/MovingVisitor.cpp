//MovingVisitor.cpp
#include "SelfRelation.h"
#include"MovingVisitor.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Template.h"
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
#include <iostream>
#include "RollNameBox.h"
using namespace std;

MovingVisitor::MovingVisitor() {
}
MovingVisitor::~MovingVisitor() {
}
void MovingVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
	Long length = selection->GetLength();
	Long i = 0;
	Long j;
	Long k = 0;
	Long l = 0;
	Figure *figure;
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	while (i < length) {
		figure = selection->GetAt(i);

		if (dynamic_cast<FigureComposite*>(figure)) { //Ŭ������ �޸��
			Long startX = figure->GetX();
			Long startY = figure->GetY();
			Long endX = figure->GetX() + figure->GetWidth();
			Long endY = figure->GetY() + figure->GetHeight();
			figure->Move(distanceX, distanceY); // �ش� Ŭ������ �޸� �̵�
			FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // ����ȯ
			j = 0;
			while (j < figureComposite->GetLength()) { // ����ȯ �Ѱ� �����ϸ� �迭 ��������
				figure = figureComposite->GetAt(j);
				figure->Move(distanceX, distanceY);
				if (dynamic_cast<Relation*>(figure)) {
					Relation *relation = static_cast<Relation*>(figure);
					RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
					if (relation->GetLength() == 0) {
						CPoint startPoint(figure->GetX(), figure->GetY());
						CPoint endPoint(figure->GetX() + figure->GetWidth(), figure->GetY() + figure->GetHeight());
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(3, cPoint4);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(4, cPoint5);
						cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(1, cPoint2);
					}
					else if (relation->GetLength() > 0) {
						CPoint startPoint(figure->GetX(), figure->GetY());
						CPoint endPoint(relation->GetAt(0).x, relation->GetAt(0).y);
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(3, cPoint4);

					}

				}
				else if (dynamic_cast<SelfRelation*>(figure)) {
					SelfRelation *selfRelation = static_cast<SelfRelation*>(figure);
					CPoint cPoint1(selfRelation->rollNamePoints->GetAt(0).x + distanceX, selfRelation->rollNamePoints->GetAt(0).y + distanceY);
					CPoint cPoint2(selfRelation->rollNamePoints->GetAt(1).x + distanceX, selfRelation->rollNamePoints->GetAt(1).y + distanceY);
					CPoint cPoint3(selfRelation->rollNamePoints->GetAt(2).x + distanceX, selfRelation->rollNamePoints->GetAt(2).y + distanceY);
					CPoint cPoint4(selfRelation->rollNamePoints->GetAt(3).x + distanceX, selfRelation->rollNamePoints->GetAt(3).y + distanceY);
					CPoint cPoint5(selfRelation->rollNamePoints->GetAt(4).x + distanceX, selfRelation->rollNamePoints->GetAt(4).y + distanceY);
					selfRelation->rollNamePoints->Modify(0, cPoint1);
					selfRelation->rollNamePoints->Modify(1, cPoint2);
					selfRelation->rollNamePoints->Modify(2, cPoint3);
					selfRelation->rollNamePoints->Modify(3, cPoint4);
					selfRelation->rollNamePoints->Modify(4, cPoint5);
				}
				j++;
			}
			k = 0;
			while (k < diagram->GetLength()) {
				figureComposite = static_cast<FigureComposite*>(diagram->GetAt(k));
				l = 0;
				while (l < figureComposite->GetLength()) {
					if (dynamic_cast<Relation*>(figureComposite->GetAt(l))) {
						figure = figureComposite->GetAt(l);
						Long relationEndX = figure->GetX() + figure->GetWidth();
						Long relationEndY = figure->GetY() + figure->GetHeight();
						if (startX <= relationEndX &&  relationEndX <= endX &&
							startY <= relationEndY &&  relationEndY <= endY) {
							figure->EndPointMove(distanceX, distanceY);

							RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
							Relation *relation = static_cast<Relation*>(figure);
							if (relation->GetLength() == 0) {
								CPoint startPoint(figure->GetX(), figure->GetY());
								CPoint endPoint(figure->GetX() + figure->GetWidth(), figure->GetY() + figure->GetHeight());
								cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
								cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
								cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
								cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
								relation->rollNamePoints->Modify(0, cPoint1);
								relation->rollNamePoints->Modify(3, cPoint4);
								relation->rollNamePoints->Modify(2, cPoint3);
								relation->rollNamePoints->Modify(4, cPoint5);
								cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
								relation->rollNamePoints->Modify(1, cPoint2);
							}
							else {
								CPoint startPoint(relation->GetAt(relation->GetLength() - 1).x, relation->GetAt(relation->GetLength() - 1).y);
								CPoint  endPoint(figure->GetX() + figure->GetWidth(), figure->GetY() + figure->GetHeight());
								cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
								cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
								relation->rollNamePoints->Modify(2, cPoint3);
								relation->rollNamePoints->Modify(4, cPoint5);

							}
						}
					}
					l++;
				}
				k++;
			}

		}
		i++;
	}
}
void MovingVisitor::Visit(Class *object, CDC* pDC) {
}
void MovingVisitor::Visit(MemoBox *memoBox, CDC *pDC) {
}
void MovingVisitor::Visit(Selection *selection, CDC *pDC) {
}
void MovingVisitor::Visit(Template *object, CDC *pDC) {
}
void MovingVisitor::Visit(ClassName* className, CDC* pDC) {
}
void MovingVisitor::Visit(Attribute* attribute, CDC* pDC) {;
}
void MovingVisitor::Visit(Method* method, CDC* pDC) {
}
void MovingVisitor::Visit(Reception* reception, CDC* pDC) {
}
void MovingVisitor::Visit(Line *line, CDC* pDC) {
}
void MovingVisitor::Visit(Generalization *generalization, CDC* pDC) {
}
void MovingVisitor::Visit(Realization *realization, CDC* pDC) {
}
void MovingVisitor::Visit(Dependency *dependency, CDC* pDC) {
}
void MovingVisitor::Visit(Association *association, CDC* pDC) {
}
void MovingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* pDC) {
}
void MovingVisitor::Visit(Aggregation *aggregation, CDC* pDC) {
}
void MovingVisitor::Visit(Aggregations *aggregations, CDC* pDC) {
}
void MovingVisitor::Visit(Composition *composition, CDC* pDC) {
}
void MovingVisitor::Visit(Compositions *compositions, CDC* pDC) {
}
void MovingVisitor::Visit(MemoLine *memoLine, CDC *pDC) {
}
void MovingVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *pDC) {
}
void MovingVisitor::Visit(SelfDependency *selfDependency, CDC *pDC) {
}
void MovingVisitor::Visit(SelfAggregation *selfAggregation, CDC *pDC) {
}
void MovingVisitor::Visit(SelfAssociation *selfAssociation, CDC *pDC) {
}
void MovingVisitor::Visit(SelfAggregations *selfAggregations, CDC *pDC) {
}
void MovingVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *pDC) {
}
void MovingVisitor::Visit(SelfComposition *selfComposition, CDC *pDC) {
}
void MovingVisitor::Visit(SelfCompositions *selfCompositions, CDC *pDC) {
}
void MovingVisitor::Visit(SelfRelation *selfRelation, CDC *cPaintDc) {
}
void MovingVisitor::Visit(Relation *relation, CDC *cPaintDc) {
}
void MovingVisitor::Visit(Text* text, RECT& rt, CDC* pDC) {
}