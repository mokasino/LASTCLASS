//LeftAlignMenuAction.h

#ifndef _LEFTALIGNMENUACTION_H
#define _LEFTALIGNMENUACTION_H

#include "MenuAction.h"

class LeftAlignMenuAction : public MenuAction {
public:
	LeftAlignMenuAction();
	virtual ~LeftAlignMenuAction();
	void MenuPress(LastClass* lastClass);
};

#endif // !_LEFTALIGNMENUACTION_H