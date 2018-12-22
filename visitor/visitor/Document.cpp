#include "Document.h"
#include "DocElement.h"
#include <iostream>
#include "concreteVisitor.h"

Document::Document()
{

}

Document::~Document()
{
	for(std::list<DocElement*>::iterator it=lpElements_.begin();it!=lpElements_.end();++it)
		delete (*it);
	lpElements_.clear();
}

void Document::AddDocument(DocElement* element)
{
	lpElements_.push_back(element);
}

void Document::DisplayStatistics(void)
{
	concreteVisitor statAcyclic;
	for(std::list<DocElement*>::iterator it=lpElements_.begin();it!=lpElements_.end();++it)
		(*it)->Accept(statAcyclic);
	statAcyclic.Display();

}