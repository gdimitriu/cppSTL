#include"Monster.h"

namespace Game
{
	Monster::Monster()
	{
		m_Brush=wxBLACK_BRUSH;
		m_Pen=wxBLACK_PEN;
	}

	Monster::Monster(Monster& monster): Enemy(monster)
	{
	}

	Monster::Monster(wxPoint& center,wxSize& size) : Enemy(center,size)
	{
		m_Brush=wxBLACK_BRUSH;
		m_Pen=wxBLACK_PEN;
	}

	Monster::~Monster()
	{
		
	}

	void Monster::DoDraw(wxClientDC* dc)
	{
		wxBrush brush=dc->GetBrush();
		dc->SetBrush(*m_Brush);
		wxPen pen=dc->GetPen();
		dc->SetPen(*m_Pen);
		dc->DrawCircle(m_CentralPosition,m_Size.GetHeight()/2);
		dc->SetBrush(brush);
		dc->SetPen(pen);
	}

	Monster* Monster::Clone(void)
	{
		return new Monster(*this);
	}
}