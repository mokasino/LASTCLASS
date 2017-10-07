#include "OpenMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include "Diagram.h"
#include "Selection.h"
#include "HistoryGraphic.h"
#include "VerticalScrollBar.h"
#include "HorizontalScrollBar.h"
#include "KeyBoard.h"

#include <afxdlgs.h>
using namespace std;

OpenMenuAction::OpenMenuAction() {
}
OpenMenuAction::~OpenMenuAction() {
}
void OpenMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	CFileDialog  dlgFile(true, "txt", "*.txt", NULL, "텍스트 문서(*.txt)");
	if (dlgFile.DoModal() == IDOK)
	{	
		if (classDiagramForm->diagram != NULL) {
			delete classDiagramForm->diagram;
		}
		if (classDiagramForm->selection != NULL) {
			delete classDiagramForm->selection;
		}
		if (classDiagramForm->mouseLButton != NULL) {
			delete classDiagramForm->mouseLButton;
		}
		if (classDiagramForm->keyBoard != NULL) {
			delete classDiagramForm->keyBoard;
		}
		if (classDiagramForm->historyGraphic != NULL) {
			delete classDiagramForm->historyGraphic;
		}
		if (classDiagramForm->verticalScrollBar != NULL) {
			delete classDiagramForm->verticalScrollBar;
		}
		if (classDiagramForm->horizontalScroll != NULL) {
			delete classDiagramForm->horizontalScroll;
		}
		classDiagramForm->diagram = new Diagram();
		classDiagramForm->selection = new Selection;
		classDiagramForm->mouseLButton = new MouseLButton;
		classDiagramForm->historyGraphic = new HistoryGraphic;
		classDiagramForm->verticalScrollBar = new VerticalScrollBar(classDiagramForm);
		classDiagramForm->horizontalScroll = new HorizontalScrollBar(classDiagramForm);
		classDiagramForm->keyBoard = new KeyBoard;
		classDiagramForm->fileName = dlgFile.GetPathName();
		classDiagramForm->Load();
	}
}