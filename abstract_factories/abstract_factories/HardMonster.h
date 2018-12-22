#pragma once
#include"Monster.h"

namespace Game
{
	/*
		This Monster class will be instanciated at hard level
	*/
	class HardMonster : public Monster
	{
	public:
		HardMonster();
		HardMonster(HardMonster& monster);
		HardMonster(wxPoint& point,wxSize& size);
		~HardMonster();
		Monster* Clone(void);
	};
}