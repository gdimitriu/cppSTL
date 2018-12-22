#pragma once
#include"Monster.h"

namespace Game
{
	/*
		this is the monster class which will be instanciated at easy level
	*/
	class EasyMonster : public Monster
	{
	public:
		EasyMonster();
		EasyMonster(EasyMonster& monster);
		EasyMonster(wxPoint& center,wxSize& size);
		~EasyMonster();
		Monster* Clone(void);
	};
}