#include "Document.h"
#include "Paragraph.h"
#include "RasterImage.h"
#include <stdio.h>
#include <tchar.h>     

int _tmain(int argc, _TCHAR* argv[])
{
	Document doc;
	doc.AddDocument(new Paragraph(std::string("bla bla")));
	doc.AddDocument(new Paragraph(std::string("bla")));
	doc.AddDocument(new RasterImage);
	doc.DisplayStatistics();
	return 0;
} 