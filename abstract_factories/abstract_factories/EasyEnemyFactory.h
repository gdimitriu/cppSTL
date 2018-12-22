#pragma once
#include"AbstractEnemyFactory.h"
#include "EasyMonster.h"
#include "EasySoldier.h"

namespace ConcreteEnemyFactory
{
	/*
		This is the factory for the easy level
	*/
	class EasyEnemyFactory: public AbstractEnemyFactory
	{
	public:
		Soldier* MakeSoldier() { return new EasySoldier;}
		Monster* MakeMonster() { return new EasyMonster;}
		Soldier* MakeSoldier(wxPoint& center,wxSize& size){ return new EasySoldier(center,size);}
		Monster* MakeMonster(wxPoint& center,wxSize& size){ return new EasyMonster(center,size);}
	};
}