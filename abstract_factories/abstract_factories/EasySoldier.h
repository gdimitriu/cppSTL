#pragma once
#include"Soldier.h"

namespace Game
{
	/*
		This is the soldier class which will be instanciated at easy level
	*/
	class EasySoldier : public Soldier
	{
	public:
		EasySoldier();
		EasySoldier(wxPoint& center,wxSize& size);
		EasySoldier(EasySoldier& soldier);
		~EasySoldier();
		Soldier* Clone(void);
	};
}