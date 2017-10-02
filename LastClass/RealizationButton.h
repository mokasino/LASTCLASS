//RealizationButton.h
#ifndef _REALIZATIONBUTTON_H
#define _REALIZATIONBUTTON_H

#include"ButtonState.h"
class Selection;
class DrawingController;
class Diagram;
class Figure;
typedef signed long int Long;



class RealizationButton : public ButtonState {
public:

	RealizationButton();
	RealizationButton(const RealizationButton& source);
	virtual ~RealizationButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);


	RealizationButton& operator=(const RealizationButton& source);
};


#endif //_GENERALIZATIONBUTTON_H
