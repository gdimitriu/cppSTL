#pragma once
#include"Enemy.h"

namespace Game
{
	/*
		Monster class is the monster enemy from the game
	*/
	class Monster : public Enemy
	{
	public:
		Monster();
		Monster(Monster& monster);
		Monster(wxPoint& center,wxSize& size);
		~Monster();
		Monster* Clone(void);
	protected:
		void DoDraw(wxClientDC* dc);
	};
}