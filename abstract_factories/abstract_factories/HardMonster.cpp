#include"HardMonster.h"

namespace Game
{
	HardMonster::HardMonster()
	{
		m_Brush=wxRED_BRUSH;
		m_Pen=wxRED_PEN;
	}

	HardMonster::HardMonster(HardMonster& monster) : Monster(monster)
	{
	}
	HardMonster::HardMonster(wxPoint& point,wxSize& size) : Monster(point,size)
	{
		m_Brush=wxRED_BRUSH;
		m_Pen=wxRED_PEN;
	}

	HardMonster::~HardMonster()
	{
	}

	Monster* HardMonster::Clone(void)
	{
		return new HardMonster(*this);
	}
}