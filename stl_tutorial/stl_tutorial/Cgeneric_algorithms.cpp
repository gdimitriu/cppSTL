#include "StdAfx.h"
#include "Cgeneric_algorithms.h"
#include <iostream>
#include <iterator>
#include <cassert>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>

using std::vector;

template <typename container> container Cgeneric_algorithms::make(const char str[])
{
	return container(&str[0],&str[strlen(str)]);
}

Cgeneric_algorithms::Cgeneric_algorithms(void)
{
}


Cgeneric_algorithms::~Cgeneric_algorithms(void)
{
}


void Cgeneric_algorithms::ex02_05(void)
{
	std::cout<<"Demonstrating the ussage of the find with array\n";
	char s[]="C++ is a better C";
	//search for the first occurence of the e
	const char* where=std::find(&s[0],&s[strlen(s)],'e');
	assert('e'==*where && 't'==*(where+1));
	std::cout<<"----- OK.\n";
}



void Cgeneric_algorithms::ex02_06(void)
{
	std::cout<<"Demonstrating the ussage of the find with a vector\n";
	std::vector<char> vector1=make<std::vector<char>>("C++ is a better C");
	//search for the first occurence of the e
	std::vector<char>::iterator where=std::find(vector1.begin(),vector1.end(),'e');
	assert('e'==*where && 't'==*(where+1));
	std::cout<<"------OK.\n";
}


void Cgeneric_algorithms::ex02_07(void)
{
	std::cout<<"Demonstating the ussage of the find with a list\n";
	std::list<char> list1=make<std::list<char>>("C++ is a better C");
	//search for the first occurence of the e
	std::list<char>::iterator where=std::find(list1.begin(),list1.end(),'e');
	//advance to the next one using ++ instead of +
	std::list<char>::iterator next=where;
	++next;
	assert('e'==*where && 't'==*next);
	std::cout<<"------OK.\n";
}


void Cgeneric_algorithms::ex02_08(void)
{
	std::cout<<"Demonstrating the ussage of the find with a deque\n";
	std::deque<char> deque1=make<std::deque<char>>("C++ is a better C");
	//find the first occurence of the e
	std::deque<char>::iterator where=std::find(deque1.begin(),deque1.end(),'e');
	assert('e'==*where && 't'==*(where+1));
	std::cout<<"-----OK.\n";
}


void Cgeneric_algorithms::ex02_09(void)
{
	std::cout<<"Demonstrating the merge algorithm with an array, list and deque"<<std::endl;
	char s[]="aeiou";
	int len=strlen(s);
	std::list<char> list1=make<std::list<char>>("bcdfghjklmn");
	//initialize the deque with 26 copies of the leter x
	std::deque<char> deque1(26,'x');
	//merge array and list and put the result into the deque
	std::merge(&s[0],&s[len],list1.begin(),list1.end(),deque1.begin());
	assert(deque1==make<std::deque<char>>("abcdefghijklmnouxxxxxxxxxx"));
	std::cout<<"------OK.\n";
}


void Cgeneric_algorithms::ex02_10(void)
{
	std::cout<<"Demonstrating the merge algorithm with parts from array and deque and put the result into a list"<<std::endl;
	char s[]="acegikm";
	std::deque<char> deque1=make<std::deque<char>>("bdfhjlnopqrstuvwxyz");
	//initialize the list with 26 copies of letter x
	std::list<char> list1(26,'x');
	//merge the 5 leter from array with 10 leters from deque and put the resul into the list
	std::merge(&s[0],&s[5],deque1.begin(),deque1.begin()+10,list1.begin());
	assert(list1==make<std::list<char>>("abcdefghijlnopqxxxxxxxxxxx"));
	std::cout<<"-------OK,\n";
}


void Cgeneric_algorithms::ex02_11(void)
{
	std::cout<<"Demonstrating the ussage of the accumulate function to compute a sum"<<std::endl;
	int x[5]={2,3,5,7,11};
	//initialize the vector with the elements
	std::vector<int> vector1(&x[0],&x[5]);
	int sum=std::accumulate(vector1.begin(),vector1.end(),0);
	assert(28==sum);
	std::cout<<"-----------OK vector.\n";
	std::list<int> list1(&x[0],&x[5]);
	sum=std::accumulate(list1.begin(),list1.end(),0);
	assert(28==sum);
	std::cout<<"-----------OK list.\n";
	std::deque<int> deque1(&x[0],&x[5]);
	sum=std::accumulate(deque1.begin(),deque1.end(),0);
	assert(28==sum);
	std::cout<<"-----------OK deque.\n";
}

static int mult(int x,int y) {return x*y;}
void Cgeneric_algorithms::ex02_12(void)
{
	std::cout<<"Demonstrating the ussage of the accumulate function to compute a product"<<std::endl;
	int x[5]={2,3,5,7,11};
	//compute the product of a vector
	std::vector<int> vector1(&x[0],&x[5]);
	int product=std::accumulate(vector1.begin(),vector1.end(),1,mult);
	assert(2310==product);
	std::cout<<"-------OK vector.\n";
	//compute the product of a list
	std::list<int> list1(&x[0],&x[5]);
	product=std::accumulate(list1.begin(),list1.end(),1,mult);
	assert(2310==product);
	std::cout<<"-------OK list.\n";
	//compute the product of a deque
	std::deque<int> deque1(&x[0],&x[5]);
	product=std::accumulate(deque1.begin(),deque1.end(),1,mult);
	assert(2310==product);
	std::cout<<"-------OK deque.\n";
}


void Cgeneric_algorithms::ex02_13(void)
{
	std::cout<<"Demonstrating the ussage of the accumulate function to compute a product using function object"<<std::endl;
	int x[5]={2,3,5,7,11};
	//compute the product of a vector
	std::vector<int> vector1(&x[0],&x[5]);
	int product=std::accumulate(vector1.begin(),vector1.end(),1,multiply());
	assert(2310==product);
	std::cout<<"-------OK vector.\n";
	//compute the product of a list
	std::list<int> list1(&x[0],&x[5]);
	product=std::accumulate(list1.begin(),list1.end(),1,multiply());
	assert(2310==product);
	std::cout<<"-------OK list.\n";
	//compute the product of a deque
	std::deque<int> deque1(&x[0],&x[5]);
	product=std::accumulate(deque1.begin(),deque1.end(),1,multiply());
	assert(2310==product);
	std::cout<<"------OK deque.\n";
}


void Cgeneric_algorithms::ex02_14(void)
{
	std::cout<<"Demonstrating the ussage of the accumulate function to compute a product using all STL objects"<<std::endl;
	int x[5]={2,3,5,7,11};
	//compute the product of a vector
	std::vector<int> vector1(&x[0],&x[5]);
	int product=std::accumulate(vector1.begin(),vector1.end(),1,std::multiplies<int>());
	assert(2310==product);
	std::cout<<"------OK vector with STL\n";
}


void Cgeneric_algorithms::ex02_15(void)
{
	std::cout<<"Demonstrating the ussage of the accumulate function with reverse iterator"<<std::endl;
	float small=(float)1.0/(1<<26);
	float x[5]={1.0,3*small,2*small,small,small};
	//using a vector
	std::vector<float> vector1(&x[0],&x[5]);
	std::cout<<"Values to be added: "<<std::endl;
	std::vector<float>::iterator i;
	std::cout.precision(10);
	for(i=vector1.begin();i!=vector1.end();++i)
		std::cout<<*i<<std::endl;
	std::cout<<std::endl;
	float sum=std::accumulate(vector1.begin(),vector1.end(),(float)0.0);
	std::cout<<"Sum accumulated from left = "<<(double)sum<<std::endl;
	float sum1=std::accumulate(vector1.rbegin(),vector1.rend(),(float)0.0);
	std::cout<<"Sum accumulated from right = "<<(double)sum1<<std::endl;
	std::cout<<"New ussage"<<std::endl;
	std::reverse_iterator<std::vector<float>::iterator> start(vector1.end()),finish(vector1.begin());
	float sum2=std::accumulate(start,finish,(float)0.0);
	std::cout<<"Sum accumulated from right = "<<(double)sum2<<std::endl;
}


void Cgeneric_algorithms::runChapter2(void)
{
	ex02_05();
	ex02_06();
	ex02_07();
	ex02_08();
	ex02_09();
	ex02_10();
	ex02_11();
	ex02_12();
	ex02_13();
	ex02_14();
	ex02_15();
}


void Cgeneric_algorithms::runChapter5(void)
{
	if(false)
	{
		ex05_01();
		ex05_02();
		ex05_03();
		nonmutating();
		mutating();
		numeric();
	}
}

void Cgeneric_algorithms::ex05_01(void)
{
	std::cout<<"using the inplace sorting algorithm"<<std::endl;
	int a[1000];
	int i;
	//create the input data
	for(i=0;i<1000;++i) {
		a[i]=1000-i-1;
	}
	//sort the data
	std::sort(&a[0],&a[1000]);
	//validate the result
	for(i=0;i<1000;++i) {
		assert(a[i]==i);
	}
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_02(void)
{
	std::cout<<"using the reverse copy algorithm"<<std::endl;
	int a[1000],b[1000];
	int i;
	//create the input data
	for(i=0;i<1000;++i) {
		a[i]=i;
	}
	//reverse copy
	std::reverse_copy(&a[0],&a[1000],&b[0]);
	//validate the result
	for(i=0;i<1000;++i) {
		assert(a[i]==i && b[i]==1000-i-1);
	}
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_03(void)
{
	std::cout<<"using the generic sort algorithm with generic predicate"<<std::endl;
	int a[1000];
	int i;
	//create the input data
	for(i=0;i<1000;++i) {
		a[i]=i;
	}
	//reorder random the data
	std::random_shuffle(&a[0],&a[1000]);
	//sort ascending
	std::sort(&a[0],&a[1000]);
	//validate the result
	for(i=0;i<1000;++i) {
		assert(a[i]==i);
	}
	//reorder random the data
	std::random_shuffle(&a[0],&a[1000]);
	//sort descending using predicate
	std::sort(&a[0],&a[1000],std::greater<int>());
	//validate teh result
	for(i=0;i<1000;++i) {
		assert(a[i]==1000-i-1);
	}
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::nonmutating(void)
{
	ex05_04();
	ex05_05();
	ex05_06();
	ex05_07();
	ex05_08();
	ex05_09();
}


void Cgeneric_algorithms::ex05_04(void)
{
	std::cout<<"Illustrating the generic find_if algorithm"<<std::endl;
	//creating a vector with values 0,1,4,16,...144
	std::vector<int> vector1;
	for(int i=0;i<13;++i)
	{
		vector1.push_back(i*i);
	}
	std::vector<int>::iterator where;
	where=std::find_if(vector1.begin(),vector1.end(),GreatherThan50());
	assert(64==*where);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_05(void)
{
	std::cout<<"Ilustrating the generic adjacent find algorithm"<<std::endl;
	//creating and pupulating the deque
	std::deque<std::string> player(5);
	std::deque<std::string>::iterator iterator;
	player[0]="Pele";
	player[1]="Platini";
	player[2]="Maradona";
	player[3]="Maradona";
	player[4]="Rossi";
	//find the first pair of equal consecutive names
	iterator=std::adjacent_find(player.begin(),player.end());
	assert("Maradona"==*iterator && "Maradona"==*(iterator+1));
	//find the first name which is lexicographically greater then the following name
	iterator=std::adjacent_find(player.begin(),player.end(),std::greater<std::string>());
	assert("Platini"==*iterator && "Maradona"==*(iterator+1));
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_06(void)
{
	std::cout<<"Illustrating the generic count algorithm"<<std::endl;
	int a[]={0,0,0,1,1,1,2,2,2};
	//count the number of elements which are equal to 1
	int final_count=std::count(&a[0],&a[9],1);
	assert(3==final_count);
	//determine the number of the elements from array which are not equal to 1
	final_count=std::count_if(&a[0],&a[9],std::bind2nd(std::not_equal_to<int>(),1));
	assert(6==final_count);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_07(void)
{
	std::cout<<"Illustrating the for each algorithm"<<std::endl;
	//create the list
	std::list<std::string> dlist;
	dlist.insert(dlist.end(),"Clark");
	dlist.insert(dlist.end(),"Prost");
	dlist.insert(dlist.end(),"Senna");
	//print each element of the list
	std::for_each(dlist.begin(),dlist.end(),std::bind1st(std::mem_fun(&Cgeneric_algorithms::print_element),this));
}


void Cgeneric_algorithms::ex05_08(void)
{
	std::cout<<"Illustrating the equal and mismatch algorithms"<<std::endl;
	std::list<std::string> driver_list;
	std::vector<std::string> driver_vector;
	std::deque<std::string> driver_deque;
	//populate the driver list
	driver_list.insert(driver_list.end(),"Clarke");
	driver_list.insert(driver_list.end(),"Rindt");
	driver_list.insert(driver_list.end(),"Senna");
	//populate the vector list
	driver_vector.insert(driver_vector.end(),"Clarke");
	driver_vector.insert(driver_vector.end(),"Rindt");
	driver_vector.insert(driver_vector.end(),"Senna");
	driver_vector.insert(driver_vector.end(),"Berger");
	//populate the deque list
	driver_deque.insert(driver_deque.end(),"Clarke");
	driver_deque.insert(driver_deque.end(),"Berger");
	//show that the driver_list and the first 3 elements of driver_vector are the same
	assert(std::equal(driver_list.begin(),driver_list.end(),driver_vector.begin()));
	//show that the driver_deque are not equal with the two elements of the driver_list
	assert(!std::equal(driver_deque.begin(),driver_deque.end(),driver_list.begin()));
	//find the first coressponding position in driver_list and driver_dequeu where the elements are not equal
	std::pair<std::deque<std::string>::iterator,std::list<std::string>::iterator> pair_result;
	pair_result=std::mismatch(driver_deque.begin(),driver_deque.end(),driver_list.begin());
	if(pair_result.first!=driver_deque.end()) {
		std::cout<<"First disagreement betwen deque and list is at :"<<*(pair_result.first)<<" and "<<*(pair_result.second)<<std::endl;
	}
}


void Cgeneric_algorithms::ex05_09(void)
{
	std::cout<<"Illustrating the generic search algorithm"<<std::endl;
	//initialize the vector structure with 20 consecutive elements
	std::vector<int> vector(20);
	for(int i=0;i<20;++i)
	{
		vector[i]=i;
	}
	//initialize the deque structure with 5,6,7,8,9
	std::deque<int> deque(5);
	for(int i=0;i<5;++i)
	{
		deque[i]=i+5;
	}
	//search in vector the first occurence of the subsequence compoze by the elements of deque
	std::vector<int>::iterator position;
	position=std::search(vector.begin(),vector.end(),deque.begin(),deque.end());
	//validate if the elements 5,6,7,8,9 are into the vector at the result position
	for(int i=0;i<5;++i)
	{
		assert(*(position+i)==i+5);
	}
	std::cout<<"------OK."<<std::endl;
}

void Cgeneric_algorithms::mutating(void)
{
	ex05_10();
	ex05_11();
	ex05_12();
	ex05_13();
	ex05_14();
	ex05_15();
	ex05_16();
	ex05_17();
	ex05_18();
	ex05_19();
	ex05_20();
	ex05_21();
	ex05_22();
	ex05_23();
	ex05_24();
	ex05_25();
	ex05_26();
	ex05_27();
	ex05_28();
	ex05_29();
	ex05_30();
}

void Cgeneric_algorithms::ex05_10(void)
{
	std::cout<<"Illustrating the generic copy and copy_backwards algorithms"<<std::endl;
	std::string str("abcdefghijklmnopqrstuvwxyz");
	std::vector<char> vector1(str.begin(),str.end());
	std::vector<char> vector2(vector1.size());
	//copy vector1 to vector2
	std::copy(vector1.begin(),vector1.end(),vector2.begin());
	assert(vector1==vector2);
	//left shift the contents of the vector1 by 4 positions
	std::copy(vector1.begin()+4,vector1.end(),vector1.begin());
	assert(std::string(vector1.begin(),vector1.end())==std::string("efghijklmnopqrstuvwxyzwxyz"));
	//right shift the contents of the vector1 by 2 positions
	std::copy_backward(vector1.begin(),vector1.end()-2,vector1.end());
	assert(std::string(vector1.begin(),vector1.end())==std::string("efefghijklmnopqrstuvwxyzwx"));
	std::cout<<"-------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_11(void)
{
	std::cout<<"Illustrating the generic fill and fill_n algorithms"<<std::endl;
	//initialize the vector
	std::string s("Hello there");
	std::vector<char> vector(s.begin(),s.end());
	//fill with X the first 4 positions
	std::fill(vector.begin(),vector.begin()+4,'X');
	assert(std::string(vector.begin(),vector.end())==std::string("XXXXo there"));
	//fill with Y the next 3 positions
	std::fill_n(vector.begin()+4,3,'Y');
	assert(std::string(vector.begin(),vector.end())==std::string("XXXXYYYhere"));
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_12(void)
{
	std::cout<<"Illustrating the generic generate algorithm"<<std::endl;
	std::vector<int> powers(10);
	//fill the vector with the values 1,2,4,...,100
	std::generate(powers.begin(),powers.end(),compute_square<int>());
	//validate the values
	for(int i=0;i<10;++i)
	{
		assert(powers[i]==(i+1)*(i+1));
	}
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_13(void)
{
	std::cout<<"Illustrating the generic partition and stable partition algorithm with array"<<std::endl;
	const int N=7;
	int array0[N]={50,30,10,70,60,40,20};
	int array1[N];
	std::copy(&array0[0],&array0[N],&array1[0]);
	std::ostream_iterator<int> out(std::cout," ");
	std::cout<<"Original sequence         :";
	std::copy(&array1[0],&array1[N],out); std::cout<<std::endl;
	//partition1 putting the member that are greater than 40 first
	int *split1=std::partition(&array1[0],&array1[N],std::bind1st(std::mem_fun(&Cgeneric_algorithms::above40),this));
	std::cout<<"Result of the unstable partition :";
	std::copy(&array1[0],split1,out);std::cout<<" | ";
	std::copy(split1,&array1[N],out);std::cout<<std::endl;
	//restore the contents of the array1
	std::copy(&array0[0],&array0[N],&array1[0]);
	//creating the second partition with stable algorithm
	split1=std::stable_partition(&array1[0],&array1[N],std::bind1st(std::mem_fun(&Cgeneric_algorithms::above40),this));
	std::cout<<"Result of the stable partition :";
	std::copy(&array1[0],split1,out);std::cout<<" | ";
	std::copy(split1,&array1[N],out);std::cout<<std::endl;
	std::cout<<"Illustrating the generic stable partition algorithm with list"<<std::endl;
	std::list<int> list1(&array0[0],&array0[N]);
	std::list<int>::iterator split2=std::stable_partition(list1.begin(),list1.end(),std::bind1st(std::mem_fun(&Cgeneric_algorithms::above40),this));
	std::cout<<"Result of the stable partition :";
	std::copy(list1.begin(),split2,out);std::cout<<" | ";
	std::copy(split2,list1.end(),out);std::cout<<std::endl;
}


void Cgeneric_algorithms::ex05_14(void)
{
	std::cout<<"Illustrating the generic random_shuffle algorithm"<<std::endl;
	const int N=20;
	std::vector<int> vect(N);
	for(int i=0;i<N;++i)
	{
		vect[i]=i;
	}
	//now shuffle the data three times
	for(int j=0;j<3;++j)
	{
		std::random_shuffle(vect.begin(),vect.end());
		std::copy(vect.begin(),vect.end(),std::ostream_iterator<int> (std::cout," "));
		std::cout<<std::endl;
	}
}


void Cgeneric_algorithms::ex05_15(void)
{
	std::cout<<"Illustrating the generic remove algorithm"<<std::endl;
	const int N=11;
	int array0[N]={1,2,0,3,4,0,5,6,7,0,8};
	std::vector<int> vect;
	for(int i=0;i<N;++i)
		vect.push_back(array0[i]);
	//remove the elements which are equal to zero
	std::vector<int>::iterator new_end=std::remove(vect.begin(),vect.end(),0);
	//see if the size of the vector remains the same
	assert(N==vect.size());
	//now remove the elements from the vector
	vect.erase(new_end,vect.end());
	//validate that the 3 zero elements were removed
	assert(N-3==vect.size());
	//validate the rest of the elements
	for(int i=0;i<(int)vect.size();++i)
	{
		assert(vect[i]==i+1);
	}
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_16(void)
{
	std::cout<<"Illustrating generic replace algorithm"<<std::endl;
	std::string str("FERRARI");
	std::list<char> list1(str.begin(),str.end());
	//replace all R with S
	std::replace(list1.begin(),list1.end(),'R','S');
	assert(std::string(list1.begin(),list1.end())==std::string("FESSASI"));
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_17(void)
{
	std::cout<<"Illustrating the generic rotate algorithm"<<std::endl;
	std::string s("Software Engineering ");
	std::vector<char> data(s.begin(),s.end());
	//rotate the vector so Engineering comes first
	std::rotate(data.begin(),data.begin()+9,data.end());
	assert(std::string(data.begin(),data.end())==std::string("Engineering Software "));
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_18(void)
{
	std::cout<<"Illustrating the generic swap algorithm"<<std::endl;
	int high=200,low=0;
	std::swap(high,low);
	assert(0==high && 200==low);
	std::vector<int> vect1(200,1);
	std::vector<int> vect2(100,2);
	std::swap(vect1,vect2);
	assert(vect1==std::vector<int>(100,2) && vect2==std::vector<int>(200,1));
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_19(void)
{
	std::cout<<"Illustrating the generic swap ranges algorithm"<<std::endl;
	std::vector<char> vector1=make<std::vector<char>>("HELLO");
	std::vector<char> vector2=make<std::vector<char>>("THERE");
	//save the vector for late checking
	std::vector<char> orig1=vector1;
	std::vector<char> orig2=vector2;
	std::swap_ranges(vector1.begin(),vector1.end(),vector2.begin());
	assert(vector1==orig2 && vector2==orig1);
	std::cout<<"------OK."<<std::endl;
}

int sum(int val1,int val2)
{
		return val1+val2;
}

void Cgeneric_algorithms::ex05_20(void)
{
	std::cout<<"Illustrating the generic transform algorithms"<<std::endl;
	int array1[5]={0,1,2,3,4};
	int array2[5]={6,7,8,9,10};
	std::ostream_iterator<int> out(std::cout," ");
	//create the sum of the elements and put them into the output stream
	std::transform(&array1[0],&array1[5],&array2[0],out,sum);
	std::cout<<std::endl;
}


void Cgeneric_algorithms::ex05_21(void)
{
	std::cout<<"Illustrating the generic unique algorithm"<<std::endl;
	const int N=11;
	int array1[N]={1,2,0,3,3,0,7,7,7,0,8};
	//put the array inside a vector
	std::vector<int> vector1;
	for(int i=0;i<N;++i)
		vector1.push_back(array1[i]);
	//eliminate consecutive duplicate from vector1
	std::vector<int>::iterator new_end;
	new_end=std::unique(vector1.begin(),vector1.end());
	//the size of the vector should remains the same
	assert(N==vector1.size());
	//remove the elements
	vector1.erase(new_end,vector1.end());
	//put the result of the new vector to stdout
	copy(vector1.begin(),vector1.end(),std::ostream_iterator<int>(std::cout," "));
	std::cout<<std::endl;
}


void Cgeneric_algorithms::ex05_22(void)
{
	std::cout<<"Illustrating the generic algorithms sort, stable_sort and partial_sort"<<std::endl;
	const int N=20;
	std::vector<int> vector0;
	//put the element in vector0
	for(int i=0;i<N;++i)
		vector0.push_back(i);
	std::vector<int> vector1=vector0;
	std::ostream_iterator<int> out(std::cout," ");
	//print the vector before sorting
	std::cout<<"Vector before sorting"<<std::endl;
	std::copy(vector0.begin(),vector0.end(),out);
	std::cout<<std::endl;
	std::sort(vector1.begin(),vector1.end(),Comp_Last());
	//print the sorted vector with last digits
	std::cout<<"Sorting with last digits sort algorithm"<<std::endl;
	std::copy(vector1.begin(),vector1.end(),out);
	std::cout<<std::endl;
	//restore the vector
	vector1=vector0;
	std::cout<<"Vector before sorting"<<std::endl;
	std::copy(vector1.begin(),vector1.end(),out);
	std::cout<<std::endl;
	std::stable_sort(vector1.begin(),vector1.end(),Comp_Last());
	//print the sorted vector
	std::cout<<"Vector sorted with stable sort and last digits"<<std::endl;
	std::copy(vector1.begin(),vector1.end(),out);
	std::cout<<std::endl;
	//restor the vector
	vector1=vector0;
	std::cout<<"Vector before sorting"<<std::endl;
	std::copy(vector1.begin(),vector1.end(),out);
	std::cout<<std::endl;
	std::partial_sort(vector1.begin(),vector1.begin()+5,vector1.end(),Comp_Last());
	//print the sorted with lst digits vector it shoudl have at the first 5 position the smallest values for last digits
	std::cout<<"Sorted 5 elements of the vector with smallest last digits"<<std::endl;
	std::copy(vector1.begin(),vector1.end(),out);
	std::cout<<std::endl;
}


void Cgeneric_algorithms::ex05_23(void)
{
	std::cout<<"Illustrating the generic nth algorithm"<<std::endl;
	std::vector<int> v(7);
	v[0]=25; v[1]=7; v[2]=9;
	v[3]=2; v[4]=0; v[5]=5; v[6]=21;
	const int N=4;
	//Use Nth element to replace the Nth smallest element in V
	//in the Nth position, v.begin()+N
	std::nth_element(v.begin(),v.begin()+N,v.end());
	//check that the element at v.begin()+N, v[N] is
	//greater than or equal to each of the preceding elements
	int i;
	for(i=0;i<N;++i)
		assert(v[N]>=v[i]);
	//check that v[N] is less than or equal to each of the folllowing elements
	for(i=N+1;i<7;++i)
		assert(v[N]<=v[i]);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_24(void)
{
	std::cout<<"Illustrating all binary search generic algorithms"<<std::endl;
	std::vector<int> vect(5);
	bool found;
	//initialize the vector
	for(int i=0;i<5;++i)
		vect[i]=i;
	//find the values inside the vector
	for(int i=0;i<5;++i)
	{
		found=std::binary_search(vect.begin(),vect.end(),i);
		assert(true==found);
	}
	//search for an element which does not exist
	found=std::binary_search(vect.begin(),vect.end(),10);
	assert(false==found);
	//initialize the vector with 07778
	vect[0]=0; vect[1]=7; vect[2]=7; vect[3]=7; vect[4]=8;
	//position for lower and upper bound
	std::vector<int>::iterator position;
	position=std::lower_bound(vect.begin(),vect.end(),7);
	assert(position==vect.begin()+1 && 7==*position);
	position=std::upper_bound(vect.begin(),vect.end(),7);
	assert(position==vect.end()-1 && 8==*position);
	std::pair<std::vector<int>::iterator,std::vector<int>::iterator> pi=std::equal_range(vect.begin(),vect.end(),7);
	assert(pi.first==vect.begin()+1 && pi.second==vect.end()-1);
    std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_25(void)
{
	std::cout<<"Illustrating the merge and inplace_merge algorithms"<<std::endl;
	std::vector<int> vect1(5);
	std::vector<int> vect2(5);
	std::vector<int> vect3(10);
	//initialize the vectors
	for(int i=0;i<5;++i)
		vect1[i]=2*i;
	for(int i=0;i<5;++i)
		vect2[i]=1+2*i;
	//merge the vect1 and vect2 into the vect3
	std::merge(vect1.begin(),vect1.end(),vect2.begin(),vect2.end(),vect3.begin());
	//validate the result
	for(int i=0;i<10;++i)
		assert(i==vect3[i]);
	//create two halves into the vector3
	std::copy(vect1.begin(),vect1.end(),vect3.begin());
	std::copy(vect2.begin(),vect2.end(),vect3.begin()+5);
	std::inplace_merge(vect3.begin(),vect3.begin()+5,vect3.end());
	//validate the result
	for(int i=0;i<10;++i)
		assert(i==vect3[i]);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_26(void)
{
	std::cout<<"Illustrating the generic set operations"<<std::endl;
	std::vector<char> vect1=make<std::vector<char>>("abcde");
	std::vector<char> vect2=make<std::vector<char>>("aeiou");
	bool result;
	result=std::includes(vect1.begin(),vect1.end(),vect2.begin(),vect2.end());
	//the result is false because vect2 is not contains into the vect1
	assert(false==result);
	result=std::includes(vect1.begin(),vect1.end(),vect2.begin(),vect2.begin()+2);
	//the result si true because vect2 (ae) is contained into the vect1
	assert(true==result);
	//set_union
	std::vector<char> setUnion;
	std::set_union(vect1.begin(),vect1.end(),vect2.begin(),vect2.end(),std::back_inserter(setUnion));
	assert(setUnion==make<std::vector<char>>("abcdeiou"));
	//set_intersection
	std::vector<char> setIntersection;
	std::set_intersection(vect1.begin(),vect1.end(),vect2.begin(),vect2.end(),std::back_inserter(setIntersection));
	assert(setIntersection==make<std::vector<char>>("ae"));
	//set_symmetric_difference
	std::vector<char> setSymmetricDifference;
	std::set_symmetric_difference(vect1.begin(),vect1.end(),vect2.begin(),vect2.end(),std::back_inserter(setSymmetricDifference));
	assert(setSymmetricDifference==make<std::vector<char>>("bcdiou"));
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_27(void)
{
	std::cout<<"Illustrating the heap generic algorithms"<<std::endl;
	std::vector<int> vector1(5);
	for(int i=0;i<5;++i)
		vector1[i]=i;
	std::random_shuffle(vector1.begin(),vector1.end());
	//sort the vector1 using the push_heap and pop_heap
	for(int i=2;i<=5;++i)
		std::push_heap(vector1.begin(),vector1.begin()+i);
	for(int i=5;i>=2;--i)
		std::pop_heap(vector1.begin(),vector1.begin()+i);
	//validate if the array is sorted
	for(int i=0;i<5;++i)
		assert(vector1[i]==i);
	//shuffle the elements again
	std::random_shuffle(vector1.begin(),vector1.end());
	//sort using the heap
	std::make_heap(vector1.begin(),vector1.end());
	std::sort_heap(vector1.begin(),vector1.end());
	//validate the result
	for(int i=0;i<5;++i)
		assert(vector1[i]==i);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_28(void)
{
	std::cout<<"Illustrating the min and max element"<<std::endl;
	vector<int> vect1(5);
	for(int i=0;i<5;++i)
		vect1[i]=i;
	//shuffle the data
	std::random_shuffle(vect1.begin(),vect1.end());
	//find the min
	vector<int>::iterator pos=std::min_element(vect1.begin(),vect1.end());
	assert(0==*pos);
	//find the max
	pos=std::max_element(vect1.begin(),vect1.end());
	assert(4==*pos);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_29(void)
{
	std::cout<<"Illustrating the lexicographical compare"<<std::endl;
	//vector initialization
	vector<char> vector1=make<vector<char>>("Helio");
	vector<char> vector2=make<vector<char>>("Hello");
	//lexicographical compare
	bool result=std::lexicographical_compare(vector1.begin(),vector1.end(),vector2.begin(),vector2.end());
	assert(true==result);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_30(void)
{
	std::cout<<"Illustrating the permutation generic algorithm"<<std::endl;
	vector<int> vector1(3);
	for(int i=0;i<3;++i)
		vector1[i]=i;
	//the lexicographical permutation for (0,1,2) are
	//(0,1,2),(0,2,1),(1,0,2),(1,2,0),(2,0,1),(2,1,0)
	//starting from (0,1,2) the next permuation is
	std::next_permutation(vector1.begin(),vector1.end());
	assert(0==vector1[0]);
	assert(2==vector1[1]);
	assert(1==vector1[2]);
	//the prev permuation should now produce the original vector
	std::prev_permutation(vector1.begin(),vector1.end());
	assert(0==vector1[0]);
	assert(1==vector1[1]);
	assert(2==vector1[2]);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::numeric(void)
{
	ex05_31();
	ex05_32();
	ex05_33();
	ex05_34();
}


void Cgeneric_algorithms::ex05_31(void)
{
	std::cout<<"Illustrating the accumutate generic function"<<std::endl;
	vector<int> vector1(20);
	for(int i=0;i<20;++i)
		vector1[i]=i;
	//compute the sum: 5+0+1+2+3+...+19=195
	int result=std::accumulate(vector1.begin(),vector1.end(),5);
	assert(195==result);
	//compute the prod 10*1*2*3*4=240
	result=std::accumulate(vector1.begin()+1,vector1.begin()+5,10,std::multiplies<int>());
	assert(240==result);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_32(void)
{
	std::cout<<"Illustrating the generic partial sum algorithm"<<std::endl;
	const int N=20;
	int x1[N],x2[N];
	//initialize the vector
	for(int i=0;i<N;++i)
		x1[i]=i;
	std::partial_sum(&x1[0],&x1[N],&x2[0]);
	//print the partial sum
	for(int i=0;i<N;++i)
		std::cout<<x2[i]<<" ";
	std::cout<<std::endl;
}


void Cgeneric_algorithms::ex05_33(void)
{
	std::cout<<"Illustrating the adjacent_difference"<<std::endl;
	const int N=20;
	int x1[N],x2[N];
	//initialize the data
	for(int i=0;i<N;++i)
		x1[i]=i;
	//compute the partial sum
	std::partial_sum(&x1[0],&x1[N],&x2[0]);
	//compute the adjacent_difference
	std::adjacent_difference(&x2[0],&x2[N],&x2[0]);
	//see if the result is the correct one, the original vector
	for(int i=0;i<N;++i)
		assert(i==x2[i]);
	std::cout<<"------OK."<<std::endl;
}


void Cgeneric_algorithms::ex05_34(void)
{
	std::cout<<"Illustrating the generic inner product"<<std::endl;
	const int N=5;
	int x1[5],x2[5];
	//initialize the two vector
	for(int i=0;i<N;++i)
	{
		x1[i]=i+1;
		x2[i]=i+2;
	}
	//compute the inner product
	int result=std::inner_product(&x1[0],&x1[N],&x2[0],0);
	std::cout<<"This was the normally innerproduct = "<<result<<std::endl;
	//now compute the inner producty with the + and * reversed
	result=std::inner_product(&x1[0],&x1[N],&x2[0],1,std::multiplies<int>(),std::plus<int>());
	std::cout<<"This was the reversed operations inner product "<<result<<std::endl;
}
