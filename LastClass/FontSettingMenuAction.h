
#ifndef _FONTSETTINGMENUACTION_H
#define _FONTSETTINGMENUACTION_H
#include "MenuAction.h"

class FontSettingMenuAction : public MenuAction {
public:
	FontSettingMenuAction();
	virtual ~FontSettingMenuAction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_FONTSETTINGMENUACTION_H
