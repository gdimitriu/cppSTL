#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
class CTimer
{
public:
	CTimer(void);
	~CTimer(void);
	//start a series of r trials for problem size N:
	void start(unsigned int r,unsigned long N);
	//start a series of r trials to determine baseline time:
	void start_baseline(unsigned int r);
	//return true if the trials have been completed, else false
	bool check();
	//report the results of teh trials on cout
	//with additional output if verbose is true:
	void report(bool verbose);
	//returns the results for external use
	const map<unsigned int,double>& results() const;
private:
	unsigned int reps; //number of trials
	//for storing loop iterations of a trial
	vector<long> iterations;
	//for saving  initial and final times of a trial
	time_t initial,final;
	//for counting loop iterations of a trial
	unsigned long count;
	//for saving the problem size(N) for current trials
	unsigned int problem_size;
	//for storing (problem size,time) pairs
	map<unsigned int,double> result_map;
	//true if this is a baseline computation, false otherwise
	bool baseline;
	//for recording the baseline time
	double baseline_time;
};

