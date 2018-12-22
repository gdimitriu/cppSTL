#pragma once
#include "Soldier.h"
#include "Monster.h"
namespace ConcreteEnemyFactory
{
	using namespace Game;
	/*
		This is the begining class of the abstract enemy factory
	*/
	class AbstractEnemyFactory
	{
	public:
		virtual Soldier* MakeSoldier()=0;
		virtual Monster* MakeMonster()=0;
		virtual Soldier* MakeSoldier(wxPoint& center,wxSize& size)=0;
		virtual Monster* MakeMonster(wxPoint& center,wxSize& size)=0;
	};
}	