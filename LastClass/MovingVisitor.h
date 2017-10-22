//MovingVisitor.h

#ifndef _MOVINGVISITOR_H
#define _MOVINGVISITOR_H

#include"Visitor.h"

typedef signed long  int Long;
class MovingVisitor :public Visitor {
public:
	MovingVisitor();
	~MovingVisitor();

	void Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY);
	void Visit(Class *object, CDC* pDC);
	void Visit(MemoBox* memoBox, CDC* pDC);
	void Visit(Selection *selection, CDC *pDC);

	void Visit(Template *object, CDC *pDC);
	void Visit(ClassName* className, CDC* pDC);
	void Visit(Attribute* attribute, CDC* pDC);
	void Visit(Method* method, CDC* pDC);
	void Visit(Reception* reception, CDC* pDC);
	void Visit(Line *line, CDC* pDC);

	void Visit(Generalization *generalization, CDC* pDC); //�Ϲ�ȭ
	void Visit(Realization * realization, CDC* pDC);		//��üȭ
	void Visit(Dependency *dependency, CDC* pDC);		//����
	void Visit(Association *association, CDC* pDC);		//����ȭ
	void Visit(DirectedAssociation *directedAssociation, CDC* pDC);		//��������
	void Visit(Aggregation *aggregation, CDC* pDC);		//����
	void Visit(Aggregations *aggregations, CDC* pDC);		//���տ���
	void Visit(Composition *composition, CDC* pDC);		//�ռ�
	void Visit(Compositions *compositions, CDC* pDC);		//���տ���
	void Visit(MemoLine* memobox, CDC *pDC); //�޸�
	void Visit(SelfGeneralization *selfGeneralization, CDC *pDC);
	void Visit(SelfAggregation *selfAggregation, CDC *pDC);
	void Visit(SelfDependency *selfdependency, CDC *pDC);
	void Visit(SelfAssociation *selfAssociation, CDC *pDC);
	void Visit(SelfAggregations *selfAggregations, CDC *pDC);
	void Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *pDC);
	void Visit(SelfComposition *selfComposition, CDC *pDC);
	void Visit(SelfCompositions *selfCompositions, CDC *pDC);

	void Visit(SelfRelation *selfRelation, CDC *cPaintDc);
	void Visit(Relation *relation, CDC *cPaintDc);
	//moving
	void Visit(Class *object, Long distanceX, Long distanceY);
	void Visit(MemoBox *memoBox, Long distanceX, Long distanceY);
	//writing
	void Visit(Text* text, CDC* pDC);

	void Visit(Diagram *diagram, Long zoomRate);
	void Visit(Class *object, Long zoomRate);
	void Visit(Relation *relation, Long zoomRate);
	void Visit(MemoBox *memoBox, Long zoomRate);
	void Visit(Line *line, Long zoomRate);
	void Visit(SelfRelation *selfRelation, Long zoomRate);
	void Visit(ClassName *className, Long zoomRate);
	void Visit(Attribute *attribute, Long zoomRate);
	void Visit(Method *method, Long zoomRate);
	void Visit(Reception *reception, Long zoomRate);
	void Visit(Template *object, Long zoomRate);

	//�������� �ؽ�Ʈ
	void Visit(Text *text, Long zoomRate);
};



#endif //_MOVINGVISITOR_H