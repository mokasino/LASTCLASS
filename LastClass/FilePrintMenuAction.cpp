#include "FilePrintMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Diagram.h"
#include "WritingVisitor.h"
#include "PrintPreview.h"
#include "Finder.h"
#include "FigureComposite.h"
#include "Relation.h"
FilePrintMenuAction::FilePrintMenuAction() {
}
FilePrintMenuAction::~FilePrintMenuAction() {
}
void FilePrintMenuAction::MenuPress(LastClass* lastClass) {
	//lastClass->classDiagramForm->selection->DeleteAllItems();
	//
	//CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_RETURNDC);

	//INT_PTR int_ptr = AfxGetApp()->DoPrintDialog(&printDialog);

	//if (int_ptr == IDOK) {
	//	Finder finder;
	//	bool ret = false;
	//	CRect rect(2000, 0, 4000, 2000);
	//	Long i = 0;
	//	Long j;
	//	Long k;
	//	Long length = lastClass->classDiagramForm->diagram->GetLength();

	//	while (i < length && ret != true) { // 2�������� Ŭ������ �޸�ڽ��� �ִ��� Ȯ��.
	//		FigureComposite *figureComposite = (FigureComposite*)lastClass->classDiagramForm->diagram->GetAt(i);
	//		CRect comperRect(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
	//		ret = finder.FindRectangleByArea(comperRect, rect);
	//		j = 0;
	//		while (j < figureComposite->GetLength() && ret != true) {
	//			Figure *figure = figureComposite->GetAt(j);
	//			ret = finder.FindRectangleByPoint(rect, figure->GetX(), figure->GetY());
	//			if (dynamic_cast<Relation*>(figure)) {
	//				Relation *relation = static_cast<Relation*>(figure);
	//				k = 0;
	//				while (k < relation->GetLength() && ret != true) {
	//					CPoint point1 = relation->GetAt(k);
	//					ret = finder.FindRectangleByPoint(rect, point1.x, point1.y);
	//					k++;
	//				}
	//			}
	//			j++;
	//		}
	//		i++;
	//	}
	//	int count = printDialog.GetCopies();
	//	CPaintDC dc(lastClass);
	//	CDC cdc;
	//	CDC memDC;
	//	CDC memDCOne;
	//	CBitmap *pOldBitmap = NULL;
	//	CBitmap bitmap;
	//	CBitmap *pOldBitmapOne = NULL;
	//	CBitmap bitmapOne;
	//	CFont cFont;
	//	CFont *oldFont=NULL;
	//	i = 1;
	//	CString strTitle;
	//	DOCINFO di;
	//	CPrintInfo Info;
	//	BOOL bPrintingOK;
	//	if (ret == true) {
	//		Info.SetMaxPage(2);
	//	}
	//	else {
	//		Info.SetMaxPage(1);
	//	}
	//	cdc.Attach(printDialog.GetPrinterDC());
	//	lastClass->printPreview = new PrintPreview(lastClass);
	//	
	//		cdc.m_bPrinting = TRUE;
	//		strTitle.LoadString(AFX_IDS_APP_TITLE);
	//		ZeroMemory(&di, sizeof(DOCINFO));
	//		di.cbSize = sizeof(DOCINFO);
	//		di.lpszDocName = strTitle;

	//		bPrintingOK = cdc.StartDoc(&di);

	//
	//		Info.m_rectDraw.SetRect(0, 0, cdc.GetDeviceCaps(HORZRES), cdc.GetDeviceCaps(VERTRES));
	//		lastClass->printPreview->OnBeginPrinting(&cdc, &Info);
	//		for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {
	//			i = 1;
	//			while (i <= count) {
	//				cdc.StartPage();
	//				Info.m_nCurPage = page;
	//				//lastClass->printPreview->OnPrint(&dc, &Info, page);

	//				Long l[2] = { 0,2000 };
	//				Long k = page - 1;

	//				Long width = Info.m_rectDraw.Width();
	//				Long hegiht = Info.m_rectDraw.Height();

	//				CRect rect;
	//				lastClass->classDiagramForm->GetClientRect(&rect);
	//				//CBitmap *pOldBitmap;
	//				//CBitmap bitmap;

	//				//CPaintDC dc(lastClass);

	//				memDC.CreateCompatibleDC(&dc);
	//				bitmap.CreateCompatibleBitmap(&dc, 4000, 2000);
	//				pOldBitmap = memDC.SelectObject(&bitmap);
	//				memDC.FillSolidRect(CRect(0, 0, 4000, 2000), RGB(255, 255, 255));
	//				cFont;//CreateFont�� ��18�� textEdit�� rowHight�� �ٲ����
	//				cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
	//					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "���� ���");
	//				lastClass->SetFont(&cFont, TRUE);
	//				oldFont = memDC.SelectObject(&cFont);

	//				DrawingVisitor drawingVisitor;
	//				lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
	//				WritingVisitor writingVisitor;
	//				lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);


	//				//CBitmap *pOldBitmapOne;
	//				//CBitmap bitmapOne;

	//				memDCOne.CreateCompatibleDC(&dc);
	//				bitmapOne.CreateCompatibleBitmap(&dc, 2000, 2000);
	//				pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
	//				memDCOne.FillSolidRect(CRect(0, 0, 2000, 2000), RGB(255, 255, 255));
	//				memDCOne.BitBlt(0, 0, 2000, 2000, &memDC, l[k], 0, SRCCOPY);

	//				int mapMode = cdc.GetMapMode();
	//				memDCOne.SetMapMode(mapMode);
	//				cdc.SetStretchBltMode(COLORONCOLOR);

	//				cdc.StretchBlt(100, 100, width - 200, hegiht - 200, &memDCOne, 0, 0, 2000, 2000, SRCCOPY);


	//				bPrintingOK = (cdc.EndPage() > 0);
	//				i++;
	//			}

	//		}
	//	lastClass->printPreview->OnEndPrinting(&cdc, &Info);
	//	if (bPrintingOK) cdc.EndDoc();
	//	else cdc.AbortDoc();
	//	
	//	memDC.SelectObject(pOldBitmap);
	//	memDC.SelectObject(oldFont);
	//	memDCOne.SelectObject(pOldBitmapOne);
	//	bitmap.DeleteObject();
	//	bitmapOne.DeleteObject();
	//	cFont.DeleteObject();
	//	cdc.Detach();
	//	cdc.DeleteDC();
	//	
	//	memDC.Detach();
	//	memDC.DeleteDC();
	//	memDCOne.Detach();
	//	memDCOne.DeleteDC();
	//	//dc.Detach();
	//	//dc.DeleteDC();
	//}
	//
	//delete printDialog;

	//if (lastClass->printPreview != NULL) {
	//	delete lastClass->printPreview;
	//	lastClass->printPreview = NULL;
	//}


CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_RETURNDC, lastClass);

//PrintPreview printPreview(lastClass);
INT_PTR int_ptr = AfxGetApp()->DoPrintDialog(&printDialog);


if (int_ptr == IDOK) {
	Finder finder;
	bool ret = false;
	CRect rect(2000, 0, 4000, 2000);
	Long i = 0;
	Long j;
	Long k;
	Long length = lastClass->classDiagramForm->diagram->GetLength();

	while (i < length && ret != true) { // 2�������� Ŭ������ �޸�ڽ��� �ִ��� Ȯ��.
		FigureComposite *figureComposite = (FigureComposite*)lastClass->classDiagramForm->diagram->GetAt(i);
		CRect comperRect(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
		ret = finder.FindRectangleByArea(comperRect, rect);
		j = 0;
		while (j < figureComposite->GetLength() && ret != true) {
			Figure *figure = figureComposite->GetAt(j);
			ret = finder.FindRectangleByPoint(rect, figure->GetX(), figure->GetY());
			if (dynamic_cast<Relation*>(figure)) {
				Relation *relation = static_cast<Relation*>(figure);
				k = 0;
				while (k < relation->GetLength() && ret != true) {
					CPoint point1 = relation->GetAt(k);
					ret = finder.FindRectangleByPoint(rect, point1.x, point1.y);
					k++;
				}
			}
			j++;
		}
		i++;
	}

	CDC dc;
	int count = printDialog.GetCopies();
	i = 1;
	dc.Attach(printDialog.GetPrinterDC());

	dc.m_bPrinting = TRUE;

	CString strTitle;
	strTitle.LoadString(AFX_IDS_APP_TITLE);
	DOCINFO di;
	ZeroMemory(&di, sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = strTitle;

	BOOL bPrintingOK = dc.StartDoc(&di);

	CPrintInfo Info;

	Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
	if (ret == true) {
		Info.SetMaxPage(2);
	}
	else {
		Info.SetMaxPage(1);
	}
	//printPreview.OnBeginPrinting(&dc, &Info);
	i = 1;
	while (i <= count) {

	for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {
	
	

			dc.StartPage();
			Info.m_nCurPage = page;
			//printPreview.OnPrint(&dc, &Info, page);

			Long p[10] = { 0,2000,800,800,1600,1600,2400,2400,3200,3200 };
			Long q[10] = { 0,0,0,1000,0,1000,0,1000,0,1000 };
			//Long k = page - 1;

			Long width = Info.m_rectDraw.Width();
			Long hegiht = Info.m_rectDraw.Height();
			CDC memDC;
			CRect rect;
			lastClass->classDiagramForm->GetClientRect(&rect);
			CBitmap *pOldBitmap;
			CBitmap bitmap;

			CPaintDC pdc(lastClass);

			memDC.CreateCompatibleDC(&pdc);
			bitmap.CreateCompatibleBitmap(&pdc, 4000, 2000);
			pOldBitmap = memDC.SelectObject(&bitmap);
			memDC.FillSolidRect(CRect(0, 0, 4000, 2000), RGB(255, 255, 255));
			CFont cFont;//CreateFont�� ��18�� textEdit�� rowHight�� �ٲ����
			cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "���� ���");
			lastClass->SetFont(&cFont, TRUE);
			CFont *oldFont = memDC.SelectObject(&cFont);

			DrawingVisitor drawingVisitor;
			lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
			WritingVisitor writingVisitor;
			lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);


			CBitmap *pOldBitmapOne;
			CBitmap bitmapOne;
			CDC memDCOne;
			memDCOne.CreateCompatibleDC(&pdc);
			bitmapOne.CreateCompatibleBitmap(&pdc, 2000, 2000);
			pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
			memDCOne.FillSolidRect(CRect(0, 0, 2000, 2000), RGB(255, 255, 255));
			memDCOne.BitBlt(0, 0, 2000, 2000, &memDC, p[page-1], q[page-1], SRCCOPY);

			int mapMode = dc.GetMapMode();
			memDCOne.SetMapMode(mapMode);
			dc.SetStretchBltMode(COLORONCOLOR);

			//cdc->SetMapMode(MM_ISOTROPIC);
			//cdc->SetWindowExt(100, 100);
			//cdc->SetViewportExt(this->zoomRate, this->zoomRate);

			dc.StretchBlt(100, 100, width - 200, hegiht - 200, &memDCOne, 0, 0, 2000, 2000, SRCCOPY);


			bPrintingOK = (dc.EndPage() > 0);
		
		}
	i++;

	}
	//printPreview.OnEndPrinting(&dc, &Info);
	if (bPrintingOK) dc.EndDoc();
	else dc.AbortDoc();

	dc.Detach();
}

}