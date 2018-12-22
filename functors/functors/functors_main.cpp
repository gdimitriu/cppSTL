// Assume Functor.h includes the Functor implementation
#include "functor.h"
#include <iostream>
// The using directive is acceptable for a small C++ program
using namespace std;
using namespace TL;
// Define a test functor
struct TestFunctor
{
	void operator()(int i, double d)
	{
		cout << "TestFunctor::operator()(" << i<< ", " << d << ") called.\n";
	}
};
int main()
{
	TestFunctor f;
	Functor<void, TYPELIST_2(int, double)> cmd(f);
	cmd(4, 4.5);
}