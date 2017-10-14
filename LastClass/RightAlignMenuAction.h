//RightAlignMenuAction.h

#ifndef _RIGHTALIGNMENUACTION_H
#define _RIGHTALIGNMENUACTION_H

#include "MenuAction.h"

class RightAlignMenuAction : public MenuAction {
public:
	RightAlignMenuAction();
	virtual ~RightAlignMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_RIGHTALIGNMENUACTION_H