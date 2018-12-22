#pragma once
#include <string>
#include <iterator>
using std::string;

template <typename ForwardIterator> class counting_iterator
{
private:
	//<define private data members>
	ForwardIterator current; //state of the iterator
	int plus_count; //number of time ++ has been applied to it
	string name; //name to identify the iterator in the copy constructor and report function
	int version; //version to identify the iterator in the copy constructor and report function
public:
	typedef counting_iterator<ForwardIterator> self;
	//<define types required for adaptation by other iterator adaptors>
	typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
	typedef typename std::iterator_traits<ForwardIterator>::reference reference;
	typedef typename std::iterator_traits<ForwardIterator>::pointer pointer;
	typedef typename std::iterator_traits<ForwardIterator>::difference_type difference_type;
	typedef std::forward_iterator_tag iterator_category;
	//<define main constructor>
	counting_iterator(ForwardIterator first,const string& n): current(first),plus_count(0),name(n),version(1) {}
	~counting_iterator(void) {}
	//<define copy constructor>
	counting_iterator(const self& other);
	//<define *,==,!=, and prefix and posfix ++>
	reference operator*() { return *current;}
	bool operator==(const self& other) const { return current==other.current;}
	bool operator!=(const self& other) const { return current!=other.current;}
	self& operator++()
	{
		++current;
		++plus_count;
		return *this;
	}
	self& operator++(int)
	{
		self tmp=*this;
		++(*this);
		return tmp;
	}
	//<define statistics reporting member function>
	void report(std::ostream& o) const;
};

template <typename ForwardIterator> counting_iterator<ForwardIterator>::counting_iterator(const self& other) : current(other.current),
	plus_count(other.plus_count),name(other.name),
	version(other.version+1)
{
	std::cout<<"copying "<<name<<", new version is "<<version<<std::endl;
}

template <typename ForwardIterator> void counting_iterator<ForwardIterator>::report(std::ostream& o) const
{
	o<<"Iterator "<<name<<", version "<<version<<", reporting "<<plus_count<<" ++ operations "<<std::endl;
}
