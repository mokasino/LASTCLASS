
//Class.h

#ifndef _CLASS_H
#define _CLASS_H

#include "FigureComposite.h"
#include "DrawingVisitor.h"

class Class : public FigureComposite {
public:
	Class(Long capacity = 64);  // 관리는 Line을 하고
	Class(Long x, Long y, Long width, Long height); // 본인 그림(클래스다이어그램 기호)
	Class(const Class& source);
	virtual ~Class();

	Class& operator = (const Class& source);
	Figure* operator [] (Long index);


	Long Add(Long x, Long y, Long width, Long height);
	Figure* Move(Long distanceX, Long distanceY);
	void Initialize();

	Long AddGeneralization(Long x, Long y, Long width, Long height);
	Long AddRealization(Long x, Long y, Long width, Long height);
	Long AddDependency(Long x, Long y, Long width, Long height);
	Long AddAssociation(Long x, Long y, Long width, Long height);
	Long AddDirectedAssociation(Long x, Long y, Long width, Long height);
	Long AddAggregation(Long x, Long y, Long width, Long height);
	Long AddAggregations(Long x, Long y, Long width, Long height);
	Long AddComposition(Long x, Long y, Long width, Long height);
	Long AddCompositions(Long x, Long y, Long width, Long height);
	
	Long AddAttribute(Diagram *diagram);
	Long AddMethod(Diagram *diagram);
	Long AddReception(Diagram *diagram);
	Long AddTemplate(Long x, Long y, Long width, Long height);

	Long RemoveAttribute();
	Long RemoveMethod();
	Long RemoveReception();
	Long RemoveTemplate();
	


	virtual Long Add(Figure *figure);
	virtual Long Remove(Long index);

	virtual Figure* GetAt(Long index);


	virtual Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetAttributePosition()const;
	Long GetMethodPosition()const;
	Long GetReceptionPosition() const;
	Long GetTempletePosition() const;

private:
	Long attributePosition;
	Long methodPosition;
	Long receptionPosition;
	Long templetePosition;
};
inline Long Class::GetAttributePosition()const {
	return this->attributePosition;
}
inline Long Class::GetMethodPosition()const {
	return this->methodPosition;
}
inline Long Class::GetReceptionPosition()const {
	return this->receptionPosition;
}
inline Long Class::GetTempletePosition() const {
	return this->templetePosition;
}

#endif //_CLASS_H