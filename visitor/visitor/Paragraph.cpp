#include "Paragraph.h"
#include <iostream>

Paragraph::Paragraph()
{
	NrOfChars_=0;
	NrOfWords_=0;
}

Paragraph::~Paragraph()
{
}

Paragraph::Paragraph(std::string& paragraph)
{
	sParagraph_=paragraph;
	NrOfChars_=paragraph.length();
	NrOfWords_=0;
}

unsigned int Paragraph::NrOfChars(void)
{
	return NrOfChars_;
}

unsigned int Paragraph::NrOfWords(void)
{
	return NrOfWords_;
}
