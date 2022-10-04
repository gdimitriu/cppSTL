#include "stdafx.h"
#include <algorithm>

using std::pair;

typedef pair<int,int> Data;
class DataCompare
{
public:
	bool operator()(const Data& left,const Data& right) const
	{
		return _keyLess(left.first,right.first);
	}
	bool operator()(const Data& left,const Data::first_type& k) const
	{
		return _keyLess(left.first,k);
	}
	bool operator()(const Data::first_type& k,const Data& right) const
	{
		return _keyLess(k,right.first);
	}
private:
	bool _keyLess(const Data::first_type& k1,const Data::first_type& k2) const
	{
		return k1<k2;
	}
};
