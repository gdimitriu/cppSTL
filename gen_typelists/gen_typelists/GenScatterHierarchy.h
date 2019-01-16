#include "typelists.h"
using namespace TL;
template <class TList, template <class> class Unit>
class GenScatterHierarchy;

// GenScatterHierarchy specialization: Typelist to Unit
template <class T1, class T2, template <class> class Unit>
class GenScatterHierarchy<TypeList<T1, T2>, Unit>
	: public GenScatterHierarchy<T1, Unit>
	, public GenScatterHierarchy<T2, Unit>
{
public:
	typedef TypeList<T1, T2> TList;
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
class GenScatterHierarchy<NullType, Unit>
{
	template <typename T> struct Rebind
    {
       typedef Unit<T> Result;
    };
};
/*
template <class T, class H>
typename H::template Rebind<T>::Result& Field(H& obj)
{
	return obj;
}
*/
template <class H, typename R>
inline R& FieldHelper(H& obj, Type2Type<R>, Int2Type<0>)
{
	typename H::LeftBase& subobj = obj;
	return subobj;
}
template <class H, typename R, int i>
inline R& FieldHelper(H& obj, Type2Type<R> tt, Int2Type<i>)
{
	typename H::RightBase& subobj = obj;
	return FieldHelper(subobj, tt, Int2Type<i- 1>());
}
//Refer to HierarchyGenerators.h for FieldTraits' definition
template <int i, class H>
typename TypeAt<H,i>::Result&
Field(H& obj)
{
	typedef typename TypeAt<H,i>::Result Result;
	return FieldHelper(obj, Type2Type<Result>(), Int2type<i>());
}