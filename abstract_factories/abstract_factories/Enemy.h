#pragma once
#include"wx/wx.h"

namespace Game
{
	/*
		This class is the base class for the enemy from the game
	*/
	class Enemy
	{
	public:
		//constructors and destructors
		Enemy();
		Enemy(wxPoint& position,wxSize& size);
		Enemy(Enemy& enemy);
		~Enemy();
		//this draw function will be called from external app
		void Draw(wxClientDC *dc);
		//set the central position of the enemy
		void SetPosition(wxPoint& point);
		//get the central position of the enemy
		wxPoint GetPosition(void);
		//set the size of the enemy
		void SetSize(wxSize& size);
		//get the size of the enemy
		wxSize GetSize(void);
		//set the brush and pen ussually for erase reason
		void SetBrush(const wxBrush *brush);
		void SetPen(const wxPen *pen);
		virtual Enemy* Clone(void)=0;
	protected:
		//this is a pure virtual function to be derived by the other enemies
		//this will do the actual drawing
		virtual void DoDraw(wxClientDC *dc)=0;
		//location of the central position of the enemy
		wxPoint m_CentralPosition;
		//this is the size of the enemy
		wxSize m_Size;
		//brush for painting
		const wxBrush *m_Brush;
		//pen for painting
		const wxPen *m_Pen;
	};
}