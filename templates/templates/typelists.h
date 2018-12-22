
template<typename T,typename U>
struct TypeList
{
	typedef T Head;
	typedef U Tail;
};

namespace TL
{
class NullType {};

#define TYPELIST_1(T1) TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TypeList<T1,TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1,TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4) TypeList<T1,TYPELIST_3(T2,T3,T4)>
#define TYPELIST_5(T1,T2,T3,T4,T5) TypeList<T1,TYPELIST_4(T2,T3,T4,T5)>	

	//for computing length
	template <class TList> struct Length;
	template <> struct Length<NullType>
	{
		enum { value = 0 };
	};
	template <class T, class U> struct Length< TypeList<T, U> >
	{
		enum { value = 1 + Length<U>::value };
	};

	template <class TList, unsigned int i> struct TypeAt;
	template <class Head,class Tail>
	struct TypeAt<TypeList<Head,Tail>,0>
	{
		typedef Head Result;
	};
	template <class Head, class Tail, unsigned int i>
	struct TypeAt<TypeList<Head, Tail>, i>
	{
		typedef typename TypeAt<Tail, i - 1>::Result Result;
	};

	template <class TList, class T> struct IndexOf;
	//first value if head is empty
	template <class T>
	struct IndexOf<NullType, T>
	{
		enum { value = -1 };
	};
	//first value if head is not emtpy
	template <class T, class Tail>
	struct IndexOf<TypeList<T, Tail>, T>
	{
		enum { value = 0 };
	};
	//for the rest of the value computed by recursivity
	template <class Head, class Tail, class T>
	struct IndexOf<TypeList<Head, Tail>, T>
	{
	private:
		enum { temp = IndexOf<Tail, T>::value };
	public:
		enum { value = temp == -1 ? -1 : 1 + temp };
	};

	template <class TList, class T> struct Append;
	//append to null the null
	template <> struct Append<NullType,NullType>
	{
		typedef NullType Result;
	};
	//append T to null
	template <class T> struct Append<NullType, T>
	{
		typedef TYPELIST_1(T) Result;
	};
	//append to null a list
	template <class Head, class Tail>
	struct Append<NullType, TypeList<Head, Tail> >
	{
		typedef TypeList<Head, Tail> Result;
	};
	//append to a list T
	template <class Head, class Tail, class T>
	struct Append<TypeList<Head, Tail>, T>
	{
		typedef TypeList<Head,typename Append<Tail, T>::Result> Result;
	};
	
	template <class TList, class T> struct Erase;
	//if is just one element
	template <class T> // Specialization 1
	struct Erase<NullType, T>
	{
		typedef NullType Result;
	};
	//erase the head
	template <class T, class Tail> // Specialization 2
	struct Erase<TypeList<T, Tail>, T>
	{
		typedef Tail Result;
	};
	//erase the first occurence
	template <class Head, class Tail, class T> // Specialization 3
	struct Erase<TypeList<Head, Tail>, T>
	{
		typedef TypeList<Head,typename Erase<Tail, T>::Result> Result;
	};

	template <class TList, class T> struct EraseAll;
	//if it has only one element
	template <class T>
	struct EraseAll<NullType, T>
	{
		typedef NullType Result;
	};
	//erase all occurences of type T if first occurence is head
	template <class T, class Tail>
	struct EraseAll<TypeList<T, Tail>, T>
	{
	// Go all the way down the list removing the type
		typedef typename EraseAll<Tail, T>::Result Result;
	};
	//erase all occurences of type T when is into the middle
	template <class Head, class Tail, class T>
	struct EraseAll<TypeList<Head, Tail>, T>
	{
	// Go all the way down the list removing the type
		typedef TypeList<Head, typename EraseAll<Tail, T>::Result> Result;
	};

	template <class TList> struct NoDuplicates;
	template <> struct NoDuplicates<NullType>
	{
		typedef NullType Result;
	};
	template <class Head, class Tail>
	struct NoDuplicates< TypeList<Head, Tail> >
	{
	private:
		typedef typename NoDuplicates<Tail>::Result L1;
		typedef typename Erase<L1, Head>::Result L2;
	public:
		typedef TypeList<Head, L2> Result;
	};

	template <class TList, class T, class U> struct Replace;
	template <class T, class U>
	struct Replace<NullType, T, U>
	{
		typedef NullType Result;
	};
	template <class T, class Tail, class U>
	struct Replace<TypeList<T, Tail>, T, U>
	{
		typedef TypeList<U, Tail> Result;
	};
	template <class Head, class Tail, class T, class U>
	struct Replace<TypeList<Head, Tail>, T, U>
	{
		typedef TypeList<Head,typename Replace<Tail, T, U>::Result> Result;
	};

	template <class TList,class T, class U> struct ReplaceAll;
	template <class T,class U>
	struct ReplaceAll<NullType,T,U>
	{
		typedef NullType Result;
	};
	//recursive on tail
	template <class T,class Tail,class U>
	struct ReplaceAll<TypeList<T,Tail>,T,U>
	{
		typedef typename ReplaceAll<Tail,T,U>::Result Result;
	};
	template <class Head,class Tail,class T,class U>
	struct ReplaceAll<TypeList<Head,Tail>,T,U>
	{
		typedef TypeList<Head,typename ReplaceAll<Tail,T,U>::Result> Result;
	};
//typedefs
	//	typedef TypeList<int,NullType> OneTypeOnly;
	typedef TYPELIST_1(int) OneTypeOnly;
//	typedef TypeList<char,TypeList<signed char,TypeList<unsigned char,NullType> > > AllCharTypes;
	typedef TYPELIST_3(char,signed char,unsigned char) AllCharTypes;
//	typedef TypeList<signed char, TypeList<short int,TypeList<int,TypeList<long int,NullType> > > > SingnedIntegrals;
	typedef TYPELIST_4(signed char,short int,int,long int) SignedIntegrals;
	typedef Append<NullType,char>::Result bla0;
	typedef Append<bla0,double>::Result bla1;
	typedef Append<SignedIntegrals, TYPELIST_3(float, double, long double) >::Result SignedTypes;
	typedef Erase<SignedTypes,double>::Result bla2;

	template <class T, class U>
    struct ConversionHelper
    {
		typedef char Small;
        struct Big { char dummy[2]; };
        static Big   Test(...);
        static Small Test(U);
        static T MakeT();
    };

	template <class T,class U>
	class Conversion
	{
		 typedef ConversionHelper<T, U> H;
	public:
		enum { exists = sizeof(typename H::Small) == sizeof((H::Test(H::MakeT()))) };
	};

	template <class T>
	class Conversion<T, T>
	{
	public:
		enum { exists = 1, sameType = 1 };
	};
	#define SUPERSUBCLASS(T, U) (Conversion<const U*, const T*>::exists && !Conversion<const T*, const void*>::sameType)
	template <bool flag, typename T, typename U>
	struct Select
	{
		typedef T Result;
	};
	template <typename T, typename U>
	struct Select<false, T, U>
	{
		typedef U Result;
	};

	template <class TList, class T> struct MostDerived;
	template <class T>
	struct MostDerived<NullType, T>
	{
		typedef T Result;
	};
	template <class Head, class Tail, class T>
	struct MostDerived<TypeList<Head, Tail>, T>
	{
	private:
		typedef typename MostDerived<Tail, T>::Result Candidate;
	public:
		typedef typename Select<SUPERSUBCLASS(Candidate, Head),Head, Candidate>::Result Result;
	};
	template <class T> struct DerivedToFront;
	template <>
	struct DerivedToFront<NullType>
	{
		typedef NullType Result;
	};
	template <class Head, class Tail>
	struct DerivedToFront< TypeList<Head, Tail> >
	{
	private:
		typedef typename MostDerived<Tail, Head>::Result TheMostDerived;
		typedef typename Replace<Tail,TheMostDerived, Head>::Result L;
	public:
		typedef TypeList<TheMostDerived, L> Result;
	};

	template <typename T>
    struct Type2Type
    {
        typedef T OriginalType;
    };
	
	template <int v>
    struct Int2Type
    {
        enum { value = v };
    };

};