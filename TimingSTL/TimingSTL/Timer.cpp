#include "Timer.h"


CTimer::CTimer(void)
{
	baseline=false;
}


CTimer::~CTimer(void)
{
}

void CTimer::start(unsigned int r,unsigned long N)
{
	reps=r;
	problem_size=N;
	count=0;
	iterations.clear();
	iterations.reserve(reps);
	initial=time(0);
}

void CTimer::start_baseline(unsigned int r)
{
	baseline=true;
	start(r,0);
}

bool CTimer::check()
{
	++count;
	final=time(0);
	if(initial<final)
	{
		iterations.push_back(count);
		initial=final;
		count=0;
	}
	return (iterations.size()<reps);
}

const map<unsigned int,double>& CTimer::results() const
{
	return result_map;
}

void CTimer::report(bool verbose)
{
	if(verbose)
	{
		//<print the interation counts,breaking lines every 10 numbers>
		for(unsigned int k=0;k<iterations.size();++k)
		{
			cout<<iterations[k]<<" ";
			if((k+1)%10==0)
				cout<<endl;
		}
		cout<<endl;
	}
	sort(iterations.begin(),iterations.end());
	if(verbose)
	{
		cout<<"Sorted counts:"<<endl;
		//<Print the iteration counts, breaking lines every 10 numbers>
		for(unsigned int k=0;k<iterations.size();++k)
		{
			cout<<iterations[k]<<" ";
			if((k+1)%10==0)
				cout<<endl;
		}
		cout<<endl;
	}
	//<choose the median of the counts a the most accurate>
	int selected_count=iterations[reps/2];
	if(verbose)
		cout<<"Selected count: "<<selected_count<<endl;
	if(baseline)
	{
		baseline_time=1000.0/selected_count;
		cout<<"Baseline time: "<<baseline_time<<endl;
		baseline=false;
	}
	else
	{
		double calculated_time,growth_factor;
		result_map[problem_size]=calculated_time=1000.0/selected_count-baseline_time;
		cout<<setiosflags(ios::fixed)<<setprecision(4)<<setw(35)<<problem_size<<setw(12)<<calculated_time<<" ms ";
		//<compute the growth factor if possible>
		if(result_map.find(problem_size/2)!=result_map.end())
		{
			growth_factor=calculated_time/result_map[problem_size/2];
			cout<<setiosflags(ios::fixed)<<setprecision(4)<<setw(8)<<growth_factor;
		}
		cout<<endl;
	}
}