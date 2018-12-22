#include "HardSoldier.h"

namespace Game
{
	HardSoldier::HardSoldier()
	{
		m_Brush=wxRED_BRUSH;
		m_Pen=wxRED_PEN;
	}

	HardSoldier::HardSoldier(wxPoint& center,wxSize& size) : Soldier(center,size)
	{
		m_Brush=wxRED_BRUSH;
		m_Pen=wxRED_PEN;
	}

	HardSoldier::~HardSoldier()
	{
	}

	Soldier* HardSoldier::Clone()
	{
		return new HardSoldier(*this);
	}
}
