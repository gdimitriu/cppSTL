#pragma once
#include "Soldier.h"

namespace Game
{
	/*
		This class will instanciate a soldier at hard level
	*/
	class HardSoldier : public Soldier
	{
	public:
		HardSoldier();
		HardSoldier(wxPoint& center,wxSize& size);
		~HardSoldier();
		Soldier* Clone(void);
	};
}