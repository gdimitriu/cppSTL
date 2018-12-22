#pragma once
#include "typelists.h"

template <class TList, template <class> class Unit>
class GenScatterHierarchy;

// GenScatterHierarchy specialization: Typelist to Unit
template <class T1, class T2, template <class> class Unit>
class GenScatterHierarchy<TL::TypeList<T1, T2>, Unit>
	: public GenScatterHierarchy<T1, Unit>
	, public GenScatterHierarchy<T2, Unit>
{
public:
	typedef typename TL::TypeList<T1, T2> TList;
	typedef GenScatterHierarchy<T1, Unit> LeftBase;
	typedef GenScatterHierarchy<T2, Unit> RightBase;
	template <typename T> struct Rebind
    {
       typedef Unit<T> Result;
    };
};

// Pass an atomic type (non-typelist) to Unit
template <class AtomicType, template <class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType>
{
	typedef Unit<AtomicType> LeftBase;
	template <typename T> struct Rebind
    {
        typedef Unit<T> Result;
    };
};

// Do nothing for NullType
template <template <class> class Unit>
class GenScatterHierarchy<TL::NullType, Unit>
{
	template <typename T> struct Rebind
    {
       typedef Unit<T> Result;
    };
};

template <class T, class H>
typename H::template Rebind<T>::Result& Field(H& obj)
{
	return obj;
}

//global definition
template<class TList,template <class AtomicType, class Base> class Unit,class Root = EmptyType>
class GenLinearHierarchy;

//two elements (typelist) definition    
template<class T1,class T2,template <class, class> class Unit,class Root>
class GenLinearHierarchy<TL::TypeList<T1, T2>, Unit, Root> : public Unit< T1, GenLinearHierarchy<T2, Unit, Root> >
{
};

//one element (leaf or atomic) definition
template<class T,template <class, class> class Unit,class Root>
class GenLinearHierarchy<TL::TypeList<T, TL::NullType>, Unit, Root> : public Unit<T, Root>
{
};
