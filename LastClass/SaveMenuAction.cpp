#include "SaveMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include <afxdlgs.h>
using namespace std;
SaveMenuAction::SaveMenuAction() {
}
SaveMenuAction::~SaveMenuAction() {
}
void SaveMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->fileName == "") {
		int messageBox = lastClass->MessageBox(_T("���� ������ ���� ������ �����Ͻðڽ��ϱ�?"), "ClassDiagram", MB_YESNOCANCEL);
		if (messageBox == IDYES) {
			CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "�ؽ�Ʈ ����(*.txt)");
			if (dlgFile.DoModal() == IDOK){
				lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
				lastClass->classDiagramForm->Save();
			}
		}
	}
	else {
		lastClass->classDiagramForm->Save();
	}

}