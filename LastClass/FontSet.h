//FontSet.h

#ifndef _FONTSET_H
#define _FONTSET_H

#include <string>
#include <afxwin.h>

using namespace std;

typedef signed long int Long;

class ClassDiagramForm;
class TextEdit;
class FontSet {
public:
	FontSet();
	FontSet(LOGFONT *lf);
	FontSet(const FontSet& source);
	CFont* SetFont(const LOGFONT& lf, CDC *pDC);
	void ApplyFont(TextEdit *textEdit);
	~FontSet();

	LOGFONT& RelationFontSet();
	CFont cFont;
private:
	LOGFONT lf;
	CFont *p_oldFont;
};

#endif // _FONTSET_H