//Figure.cpp

#include "Figure.h"
#include "Relation.h"

Figure::Figure() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->content = "";
	this->minimumWidth = 120;
	this->minimumHeight = 29;
	this->lf = { 0, };
	this->align = DT_LEFT;
}

Figure::Figure(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->content = "";
	this->minimumWidth = 120;
	this->minimumHeight = 29;
	this->lf = { 0, };
	this->align = DT_LEFT;
}

Figure::Figure(Long x, Long y, Long width, Long height, string content) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->content = content;
	this->minimumWidth = 120; //���⵵
	this->minimumHeight = 29; // �Է¹��� ���ڿ��� �°� �� ����ϴµ�
	this->lf = { 0, };
	this->align = DT_LEFT;
}

Figure::Figure(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->content = content;
	this->minimumWidth = minimumWidth;
	this->minimumHeight = minimumHeight;
	this->lf = { 0, };
	this->align = DT_LEFT;
}

Figure::Figure(const Figure& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;
	this->minimumWidth = source.minimumWidth;
	this->minimumHeight = source.minimumHeight;
	this->lf = source.lf;
	this->align = source.align;
}

Long Figure::GetRowCount(string object) {
	Long count = 0;
	Long i = 0;
	while (object[i] != '\0') {
		if (object[i] == '\n') {
			count++;
		}
		i++;
	}
	//if (i != 0) {
		count++; // ������ �����Ǳ⶧���� ��������.
//	}
	return count;
}

void Figure::ReplaceString(string content, LOGFONT lf, Long align) {
	this->content = content;
	this->lf = lf;
	this->align = align;
}
void Figure::SetX(Long x) {
	this->x = x;
}
void Figure::SetY(Long y) {
	this->y = y;
}
void Figure::SetWidth(Long width) {
	this->width = width;
}
void Figure::SetHeight(Long height) {
	this->height = height;
}
void Figure::SetMinimumWidth(Long minimumWidth) {
	this->minimumWidth = minimumWidth;
}
void Figure::SetMinimumHeight(Long minimumHeight) {
	this->minimumHeight = minimumHeight;
}
Figure* Figure::Move(Long distanceX, Long distanceY) {
	this->x = this->x + distanceX;
	this->y = this->y + distanceY;
	if (dynamic_cast<Relation*>(this)) {
		this->width = this->width - distanceX;
		this->height = this->height - distanceY;
	}
	return this;
}
Figure *Figure::EndPointMove(Long distanceX, Long distanceY) {
	this->width = this->width + distanceX;
	this->height = this->height + distanceY;
	return this;
}

Figure* Figure::Modify(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	return this;
}

Figure& Figure::operator = (const Figure& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->minimumWidth = source.minimumWidth;
	this->minimumHeight = source.minimumHeight;
	this->lf = source.lf;
	this->align = align;

	return *this;
}

Figure::~Figure() {
}
