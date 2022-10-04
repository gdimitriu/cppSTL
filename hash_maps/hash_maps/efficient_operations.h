template<typename MapType, typename KeyArgType, typename ValueArgType>
typename MapType::iterator efficientAndOrUpdate(MapType& m, const KeyArgType& k, const ValueArgType& v)
{
	typename MapType::iterator Ib=m.lower_bound(k);
	if(Ib!=m.end() && !(m.key_comp()(k,Ib->first)))
	{
		Ib->second=v;
		return Ib;
	}
	else
	{
		typedef typename MapType::value_type MVT;
		return m.insert(Ib,MVT(k,v));
	}
};
