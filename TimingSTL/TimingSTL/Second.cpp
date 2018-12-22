#include "Second.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Timer.h"
using namespace std;


Second::Second(void)
{
}


Second::~Second(void)
{
}


void Second::run(void)
{
	cout<<"Timing sort on random vectors."<<endl;
	srand(time(0));
	vector<double> v,v0;
	unsigned long N,N1,N2;
	unsigned int reps;
	cout<<"Repetitions, initial size, and final size: ";
	cin>>reps>>N1>>N2;
	CTimer tim;

	for (N=N1;N<=N2;N*=2)
	{
		v.clear();
		v.reserve(N);
		for(unsigned int i=0;i<N;++i)
			v.push_back((double)rand());
		v0=v; //save the input vector in v0
		//compute the baseline time for N
		tim.start_baseline(reps);
		do {
			//include the vector assignment in baseline time
			v=v0;
		} while(tim.check());
		tim.report(false);
		tim.start(reps,N);
		do {
			v=v0; //restore the saved vector v0 into v
			sort(v.begin(),v.end());
		}while(tim.check());
		tim.report(false);
	}
	return;
}
