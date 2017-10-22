//Relation.cpp

#include "Relation.h"
#include "Figure.h"

Relation::Relation(Long capacity) :FigureComposite() {
}

Relation::Relation(const Relation& source) : FigureComposite(source) {
}

Relation::Relation(Long x, Long y, Long width, Long height) : FigureComposite() {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Relation::~Relation() {
}

Long Relation::Add(Figure *figure) {
	Long index;
	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, figure);
	}
	else {
		index = this->figures.AppendFromRear(figure);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Relation::Move(Long index, CPoint cPoint) {
}

Figure* Relation::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}

Long Relation::Remove(Long index) {
	this->length--;
	this->capacity--;
	return this->points.Delete(index);
}
void Relation::MergePoints(Long selectIndex, CPoint cPoint) {
	Long index = -1;
	bool ret;
	Finder finder;
	CRect cRect1(cPoint.x - 5, cPoint.y - 5, cPoint.x + 5, cPoint.y + 5);
	CPoint compare;
	compare.x = this->x;
	compare.y = this->y;

	CRect cRect(compare.x - 5, compare.y - 5, compare.x + 5, compare.y + 5);
	ret = finder.FindRectangleByArea(cRect1, cRect);
	if (ret == true) {
		index = 0;
	}
	Long i = 0;
	while (i < this->length && index == -1) {
		compare.x = this->GetAt(i).x;
		compare.y = this->GetAt(i).y;
		CRect cRect2(compare.x - 5, compare.y - 5, compare.x + 5, compare.y + 5);
		ret = finder.FindRectangleByArea(cRect1, cRect2);
		if (ret == true) {
			index = i + 1;
		}
		i++;
	}
	if (index == -1) {
		compare.x = this->x + this->width;
		compare.y = this->y + this->height;
		CRect cRect3(compare.x - 5, compare.y - 5, compare.x + 5, compare.y + 5);
		ret = finder.FindRectangleByArea(cRect1, cRect3);
		if (ret == true)
		{
			index = this->length + 1;

		}
	}

	Long startIndex = selectIndex;
	Long currentIndex = index;
	if (currentIndex != -1) {
		if (startIndex > currentIndex) {
			Long i = 0;
			Long count = startIndex - currentIndex;
			while (i < count) {
				this->Remove(currentIndex + 1);
				i++;
			}
		}
		if (startIndex < currentIndex) {
			Long i = 0;
			Long count = currentIndex - startIndex;
			while (i < count) {
				this->Remove(startIndex);
				i++;
			}
		}
	}
}

void Relation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}

void Relation::MovePaste(Long distanceX, Long distanceY) {
	this->x = this->x + distanceX;
	this->y = this->y + distanceY;
}

Relation& Relation::operator=(const Relation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

Figure* Relation::operator [] (Long index) {
	return this->figures[index];
}

Figure* Relation::Clone() const {
	return new Relation(*this);
}