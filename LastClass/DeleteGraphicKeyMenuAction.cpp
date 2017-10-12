//DeleteGraphicKeyMenuAction.cpp

#include "DeleteGraphicKeyMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "DeleteGraphicKey.h"

DeleteGraphicKeyMenuAction::DeleteGraphicKeyMenuAction() {
}
DeleteGraphicKeyMenuAction::DeleteGraphicKeyMenuAction(const DeleteGraphicKeyMenuAction& source) {
}
DeleteGraphicKeyMenuAction::~DeleteGraphicKeyMenuAction() {
}

void DeleteGraphicKeyMenuAction::MenuPress(LastClass *lastClass) {
	DeleteGraphicKey *ctrlUndo = new DeleteGraphicKey;
	CClientDC dc(lastClass->classDiagramForm);
	ctrlUndo->KeyPress(lastClass->classDiagramForm, &dc);
	lastClass->classDiagramForm->Invalidate(false);
	if (ctrlUndo != 0) {
		delete ctrlUndo;
	}
}