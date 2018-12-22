#pragma once
#include "DocElement.h"
#include "GenericVisitor.h"
#include <string>

class Paragraph : public DocElement
{
public:
	Paragraph();
	~Paragraph();
	Paragraph(std::string& paragraph);
	unsigned int NrOfWords(void);
	unsigned int NrOfChars(void);
	DEFINE_VISITABLE()
protected:
	unsigned int NrOfChars_;
	unsigned int NrOfWords_;
	std::string sParagraph_;
};