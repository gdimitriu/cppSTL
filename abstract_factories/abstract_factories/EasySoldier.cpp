#include"EasySoldier.h"

namespace Game
{
	EasySoldier::EasySoldier()
	{
		m_Brush=wxGREEN_BRUSH;
		m_Pen=wxGREEN_PEN;
	}

	EasySoldier::EasySoldier(wxPoint& center,wxSize& size): Soldier(center,size)
	{
		m_Brush=wxGREEN_BRUSH;
		m_Pen=wxGREEN_PEN;
	}
	
	EasySoldier::EasySoldier(EasySoldier& soldier):Soldier(soldier)
	{
	}

	EasySoldier::~EasySoldier()
	{

	}

	Soldier* EasySoldier::Clone(void)
	{
		return new EasySoldier(*this);
	}
}