#include <iostream>

class avl_orig
{
private:
	class _node
	{
	public:
		int info;
		int bal;
		int contor;
		_node *left;
		_node *right;
	};
public:
	avl_orig(){_head=NULL;};
	~avl_orig()
	{
		//toDo
	}
	void insert(int _x);
	void print_all(void);
	void run_tests(void);
private:
	_node *_head;
	void _search_avl(int x,bool *h,_node **p);
	void _print_all(_node *top);
};