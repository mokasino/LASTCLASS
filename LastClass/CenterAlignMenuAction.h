//CenterAlignMenuAction.h

#ifndef _CENTERALIGNMENUACTION_H
#define _CENTERALIGNMENUACTION_H

#include "MenuAction.h"

class CenterAlignMenuAction : public MenuAction {
public:
	CenterAlignMenuAction();
	virtual ~CenterAlignMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_CENTERALIGNMENUACTION_H