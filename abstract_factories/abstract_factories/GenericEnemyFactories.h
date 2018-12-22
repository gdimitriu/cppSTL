#pragma once
#include"AbstractFactories.h"
#include "EasyMonster.h"
#include "EasySoldier.h"
#include "HardMonster.h"
#include "HardSoldier.h"

namespace GenericEnemyFactory
{
	using namespace Game;
	using namespace TL;

	typedef AbstractFactory<TYPELIST_2(Soldier,Monster)> AbstractEnemyFactory;

	typedef ConcreteFactory<
		// The abstract factory to implement
		AbstractEnemyFactory,
		// The policy for creating objects
		// (for instance, use the new operator)
		OpNewFactoryUnit,
		// The concrete classes that this factory creates
		TL::TYPELIST_2(EasySoldier, EasyMonster)
	> EasyLevelEnemyFactory;

	typedef ConcreteFactory<
		// The abstract factory to implement
		AbstractEnemyFactory,
		// The policy for creating objects
		// (for instance, use the new operator)
		OpNewFactoryUnit,
		// The concrete classes that this factory creates
		TL::TYPELIST_2(HardSoldier, HardMonster)
	> HardLevelEnemyFactory;

	//Enemy factory using prototype
	typedef ConcreteFactory<
		AbstractEnemyFactory,
		MyFactoryUnit//PrototypeFactoryUnit
	> EnemyFactory;
}