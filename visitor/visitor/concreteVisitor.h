#pragma once
#include "GenericVisitor.h"
#include "Paragraph.h"
#include "RasterImage.h"
#include <iostream>

class concreteVisitor :
	public BaseVisitor, // required
	public Visitor<DocElement>,// visits DocElements
	public Visitor<Paragraph> // visits Paragraphs
{
public:
	concreteVisitor()
	{
		NrOfWords_=0;
		NrOfChars_=0;
		NrOfImages_=0;
	}
	void Visit(DocElement&) { std::cout << "Visit(DocElement&) \n"; }
	void Visit(Paragraph& paragraph)
	{
		NrOfChars_+=paragraph.NrOfChars();
		NrOfWords_+=paragraph.NrOfWords();
	}
	void Visit(RasterImage& image)
	{
		NrOfImages_++;
	}
	void Display(void)
	{
		std::cout<<"Nr of words="<<NrOfWords_<<std::endl;
		std::cout<<"Nr of chars="<<NrOfChars_<<std::endl;
		std::cout<<"Nr of images="<<NrOfImages_<<std::endl;
	} 
protected:
	unsigned int NrOfWords_;
	unsigned int NrOfChars_;
	unsigned int NrOfImages_;
};