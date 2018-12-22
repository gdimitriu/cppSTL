#pragma once
#include "AbstractEnemyFactory.h"
#include "HardMonster.h"
#include "HardSoldier.h"

namespace ConcreteEnemyFactory
{
	/*
		This is the factory for the hard level
	*/
	class HardEnemyFactory : public AbstractEnemyFactory
	{
	public:
		Soldier* MakeSoldier() { return new HardSoldier;}
		Monster* MakeMonster() { return new HardMonster;}
		Soldier* MakeSoldier(wxPoint& center,wxSize& size) { return new HardSoldier(center,size);}
		Monster* MakeMonster(wxPoint& center,wxSize& size) { return new HardMonster(center,size);}
	};
}