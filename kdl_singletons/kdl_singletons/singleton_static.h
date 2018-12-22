
template<class T>
class singleton_static
{
public:
	static T& Instance()
	{
		static T obj;
		return obj;
	}
private:
	singleton_static(){};
	singleton_static(const singleton_static& singleton){};
	~singleton_static(){};

//	static T* pInternal_;
};