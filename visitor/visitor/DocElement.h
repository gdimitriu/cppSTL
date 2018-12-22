#pragma once
#include "GenericVisitor.h"

class DocElement : public BaseVisitable<>
{
public:
	DocElement() {}
	virtual ~DocElement(){}
	DEFINE_VISITABLE()
};