#include "Soldier.h"

namespace Game
{
	Soldier::Soldier()
	{
		m_Brush=wxBLACK_BRUSH;
		m_Pen=wxBLACK_PEN;
	}

	Soldier::Soldier(Soldier& soldier) : Enemy(soldier)
	{

	}
	Soldier::~Soldier()
	{

	}

	Soldier::Soldier(wxPoint& central,wxSize& size) : Enemy(central,size)
	{
		m_Brush=wxBLACK_BRUSH;
		m_Pen=wxBLACK_PEN;
	}

	void Soldier::DoDraw(wxClientDC* dc)
	{
		wxBrush brush=dc->GetBrush();
		dc->SetBrush(*m_Brush);
		wxPen pen=dc->GetPen();
		dc->SetPen(*m_Pen);
		dc->DrawRectangle(m_CentralPosition.x/2,m_CentralPosition.y/2,m_Size.x,m_Size.y);
		dc->SetBrush(brush);
		dc->SetPen(pen);
	}

	Soldier* Soldier::Clone(void)
	{
		return new Soldier(*this);
	}
}