#pragma once
#include"Enemy.h"

namespace Game
{
	/*
	   This class is the actual implementation of enemy soldier
	*/
	class Soldier : public Enemy
	{
	public:
		//constructors and destructor
		Soldier();
		Soldier(Soldier& soldier);
		Soldier(wxPoint& central,wxSize& size);
		~Soldier();
		Soldier* Clone();
	protected:
		void DoDraw(wxClientDC* dc);
	};
}