//Relation.h

#ifndef _RELATION_H
#define _RELATION_H

#include "FigureComposite.h"
#include "WritingVisitor.h"
#include "Array.h"
#include <afxwin.h>

typedef signed long int Long;

class Relation : public FigureComposite {
public:
	Relation(Long capacity = 1);
	Relation(const Relation& source);
	Relation(Long x, Long y, Long width, Long height);
	virtual ~Relation();
	Relation& operator = (const Relation& source);
	Figure* operator [] (Long index);
	Figure* Clone() const;

	//선 점구하는거
	Long Move(Long index, CPoint cPoint);
	Figure* GetAt(Long index);
	Long Add(Figure *figure);
	Long Remove(Long index);
	void MergePoints(Long selectIndex, CPoint cPoint);

	void Accept(Visitor& visitor, CDC *cPaintDc);

	void MovePaste(Long distanceX, Long distanceY);
	Long Correct(Long index, CPoint point);

	Long GetCapacity() const;
	Long GetLength() const;
private:
	Long type;
	Long directionFlag; //방향성 0:시작 1:끝
	Array<CPoint> points;
};
inline Long Relation::GetCapacity() const {
	return this->capacity;
}
inline Long Relation::GetLength() const {
	return this->length;
}
#endif // !_RELATION_H