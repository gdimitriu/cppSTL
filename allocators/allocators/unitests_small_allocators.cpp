#include "unitests_small_allocators.h"
#include <iostream>

void TestFixedAllocatorSameChunk(void)
{
	std::cout<<"start test same chunk"<<std::endl;
	std::cout<<"Create the allocator"<<std::endl;
	FixedAllocator Alloca(sizeof(int));
	//alocate one element
	std::cout<<"Starting to allocate"<<std::endl;
	void *elem=Alloca.Allocate();
	int *pInt1=new(elem) int;
	elem=Alloca.Allocate();
	int *pInt2=new(elem) int;
	*pInt1=10;
	*pInt2=20;
	assert(*pInt1==10);
	assert(*pInt2==20);
	std::cout<<"Starting to deallocate"<<std::endl;
	Alloca.DeAllocate(pInt1);
	Alloca.DeAllocate(pInt2);
	std::cout<<"end test same chunk"<<std::endl;
}

void TestFixedAllocatorTwoChunks(void)
{
	std::cout<<"start test two chunks"<<std::endl;
	std::cout<<"Create the allocator"<<std::endl;
	FixedAllocator Alloca(sizeof(int));
	//allocate 496 elements
	int* _elements[496];
	void *elem;
	for(int i=0;i<496;++i)
	{
		elem=Alloca.Allocate();
		_elements[i]=new(elem) int;
	}
	for(int i=0;i<496;++i)
	{
		*_elements[i]=i;
	}
	for(int i=0;i<496;++i)
		assert(*_elements[i]==i);
	std::cout<<"Starting to deallocate one part"<<std::endl;
	for(int i=148;i<300;++i)
	{
		Alloca.DeAllocate(_elements[i]);
	}
	std::cout<<"reallocate objects"<<std::endl;
	for(int i=148;i<300;++i)
	{
		elem=Alloca.Allocate();
		_elements[i]=new(elem) int;
		*_elements[i]=i;
	}
	for(int i=0;i<496;++i)
	{
		Alloca.DeAllocate(_elements[i]);
	}
	std::cout<<"end test two chunks"<<std::endl;
}

void TestSmallAllocatorIntDouble()
{
	std::cout<<"Start test small obj allocator int double"<<std::endl;
	std::cout<<"Create the allocator"<<std::endl;
	SmallObjAllocator Alloca(128,64);
	//allocate 100 elements: 50 ints and 50 doubles
	int *_iElements[50];
	double *_dElements[50];
	void *elem;
	std::cout<<"begin allocation"<<std::endl;
	for(int i=0;i<50;++i)
	{
		elem=Alloca.Allocate(sizeof(int));
		_iElements[i]=new(elem) int(i);
		elem=Alloca.Allocate(sizeof(double));
		_dElements[i]=new(elem) double(double(i));
	}
	std::cout<<"finished allocation and assign"<<std::endl;
	for(int i=0;i<50;++i)
	{
		assert(*_iElements[i]==i);
		assert(*_dElements[i]==double(i));
	}
	std::cout<<"begin deallocating the ints"<<std::endl;
	for(int i=0;i<50;++i)
	{
		Alloca.DeAllocate(_iElements[i],sizeof(int));
	}
	std::cout<<"reallocate 50 ints"<<std::endl;
	for(int i=0;i<50;++i)
	{
		elem=Alloca.Allocate(sizeof(int));
		_iElements[i]=new(elem) int(i*10);
	}
	for(int i=0;i<50;++i)
	{
		assert(*_iElements[i]==i*10);
	}
	std::cout<<"begin deallocating all"<<std::endl;
	for(int i=0;i<50;++i)
	{
		Alloca.DeAllocate(_iElements[i],sizeof(int));
		Alloca.DeAllocate(_dElements[i],sizeof(double));
	}
	std::cout<<"end test small obj allocator int double"<<std::endl;
}

void unitestsSmallAllocators(void)
{
	TestFixedAllocatorSameChunk();
	TestFixedAllocatorTwoChunks();
	TestSmallAllocatorIntDouble();
}