#pragma once
#include <list>
class DocElement;

class Document
{
public:
	Document();
	~Document();
	void AddDocument(DocElement* element);
	void DisplayStatistics(void);
private:
	std::list<DocElement*> lpElements_;
};