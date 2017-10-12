#include "FilePrintPreviewMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "PrintPreview.h"
#include <afxwin.h>
#include <afxext.h>
using namespace std;

FilePrintPreviewMenuAction::FilePrintPreviewMenuAction() {
}
FilePrintPreviewMenuAction::~FilePrintPreviewMenuAction() {
}
void FilePrintPreviewMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->selection->DeleteAllItems();
	 
	CRect rect;
	lastClass->GetClientRect(&rect);
	rect.bottom += 300;

	lastClass->printPreview = new PrintPreview(lastClass);
	lastClass->printPreview->Create(NULL, "printPreview", WS_VSCROLL| WS_HSCROLL, rect, NULL, NULL);

	lastClass->printPreview->ShowWindow(SW_MAXIMIZE);

	lastClass->printPreview->UpdateWindow();
}