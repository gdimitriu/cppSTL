#include"EasyMonster.h"

namespace Game
{
	EasyMonster::EasyMonster()
	{
		m_Brush=wxGREEN_BRUSH;
		m_Pen=wxGREEN_PEN;
	}

	EasyMonster::EasyMonster(EasyMonster& monster) : Monster(monster)
	{

	}

	EasyMonster::EasyMonster(wxPoint& center,wxSize& size): Monster(center,size)
	{
		m_Brush=wxGREEN_BRUSH;
		m_Pen=wxGREEN_PEN;
	}
	
	EasyMonster::~EasyMonster()
	{

	}

	Monster* EasyMonster::Clone(void)
	{
		return new EasyMonster(*this);
	}
}