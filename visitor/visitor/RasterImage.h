#pragma once
#include "DocElement.h"

class RasterImage : public DocElement
{
public:
	RasterImage();
	~RasterImage();
	DEFINE_VISITABLE()
};