#pragma once
#include <iostream>
#include <string>
class Cgeneric_algorithms
{
private:
	template <typename container> container make(const char str[]);
	class multiply{
	public:
		int operator()(int x,int y) const { return x*y;}
	};
	class GreatherThan50{
	public:
		bool operator()(int x) const { return x> 50;}
	};
	template <typename T> class compute_square {
	private:
		T i;
	public:
		compute_square() : i(0) {}
		T operator()() {++i;return i*i;}
	};
	class Comp_Last{
	public:
		bool operator()(int x, int y)
		{
			return x%10 < y%10;
		}
	};
	void ex02_05(void);
	void ex02_06(void);
	void ex02_07(void);
	void ex02_08(void);
	void ex02_09(void);
	void ex02_10(void);
	void ex02_11(void);
	void ex02_12(void);
	void ex02_13(void);
	void ex02_14(void);
	void ex02_15(void);
public:
	Cgeneric_algorithms(void);
	~Cgeneric_algorithms(void);
	void runChapter2(void);
	void runChapter5(void);
	void print_element(std::string s)
	{
		std::cout<<s<<std::endl;
	}
	bool above40(int n)
	{
		return (n>40);
	}
private:
	void ex05_01(void);
	void ex05_02(void);
	void ex05_03(void);
public:
	void nonmutating(void);
private:
	void ex05_04(void);
	void ex05_05(void);
	void ex05_06(void);
	void ex05_07(void);
	void ex05_08(void);
	void ex05_09(void);
public:
	void mutating(void);
private:
	void ex05_10(void);
	void ex05_11(void);
	void ex05_12(void);
	void ex05_13(void);
	void ex05_14(void);
	void ex05_15(void);
	void ex05_16(void);
	void ex05_17(void);
	void ex05_18(void);
	void ex05_19(void);
	void ex05_20(void);
	void ex05_21(void);
	void ex05_22(void);
	void ex05_23(void);
	void ex05_24(void);
	void ex05_25(void);
	void ex05_26(void);
	void ex05_27(void);
	void ex05_28(void);
	void ex05_29(void);
	void ex05_30(void);
public:
	void numeric(void);
private:
	void ex05_31(void);
	void ex05_32(void);
	void ex05_33(void);
	void ex05_34(void);
};

