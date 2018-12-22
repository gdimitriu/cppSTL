#include "Enemy.h"

namespace Game
{
	Enemy::Enemy() : m_CentralPosition(0,0)
	{

	}

	Enemy::Enemy(wxPoint& position,wxSize& size) : m_CentralPosition(position),m_Size(size)
	{

	}
	
	Enemy::Enemy(Enemy& enemy)
	{
		this->m_CentralPosition=enemy.m_CentralPosition;
		this->m_Size=enemy.m_Size;
		this->m_Brush=enemy.m_Brush;
		this->m_Pen=enemy.m_Pen;
	}
	
	Enemy::~Enemy()
	{

	}

	void Enemy::SetPosition(wxPoint& point)
	{
		m_CentralPosition=point;
	}

	wxPoint Enemy::GetPosition(void)
	{
		return m_CentralPosition;
	}

	void Enemy::Draw(wxClientDC *dc)
	{
		DoDraw(dc);
	}

	void Enemy::SetSize(wxSize& size)
	{
		m_Size=size;
	}
	
	wxSize Enemy::GetSize(void)
	{
		return m_Size;
	}

	void Enemy::SetBrush(const wxBrush *brush)
	{
		m_Brush=brush;
	}

	void Enemy::SetPen(const wxPen *pen)
	{
		m_Pen=pen;
	}
}