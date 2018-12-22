#include "avl_orig.h"
#include <iostream>
//#define DEBUG 0
void avl_orig::insert(int x)
{
	bool h;
	_search_avl(x,&h,&_head);
}

void avl_orig::print_all(void)
{
	_print_all(_head);
}

void avl_orig::_print_all(_node *top) //afisare leg arbori
{
	if(top!=NULL)
	{
		_print_all(top->left);
		std::cout<<top->info<<" de "<<top->contor<<" ori si are bal="<<top->bal;
		if(top->left!=NULL)
			std::cout<<" si fiul "<<(top->left)->info;
		if(top->right!=NULL) 
			std::cout<<" si fiul "<<(top->right)->info;
		std::cout<<std::endl;
		std::cout.flush();
		_print_all(top->right);
	}
}

void avl_orig::_search_avl(int x,bool *h,_node **p)
{
	_node *q,*r;
	if (*p==NULL) //inseram primul nod
	{
		*p=new _node;
		(*p)->info=x;
		(*p)->bal=0;
		(*p)->left=NULL;
		(*p)->right=NULL;
		(*p)->contor=1;
		*h=true;
		return;
	}
	if(x<(*p)->info) //insertie si reechilibrare in arborele sting
	{
#ifdef DEBUG
		std::cout<<"insert left "<<x<<" "<<(*p)->info<<std::endl<<std::flush;
#endif
		_search_avl(x,h,&((*p)->left));
		if(*h==true) //adincimea arborelui s-a modificat
		{
			switch((*p)->bal)
			{
			case 0: //inaltimea subarborelui sting a crescut cu o unitate
				{
					(*p)->bal=-1;
					break;
				}
			case 1: //acum cei doi arbori au adincimi egale
				{
					(*p)->bal=0;
					*h=false; //nu exista modificari
					break;
				}
			case -1: //acum incepem reechilibrarea
				{
					q=(*p)->left; //adresa nodului B descendent sting al lui A
					if(q->bal==-1) //trebuie rotatie SS
					{
#ifdef DEBUG
						std::cout<<"begin SS\n"<<std::flush;
#endif
						(*p)->left=q->right;
						q->right=*p;
						(*p)->bal=0;
						q->bal=0;
						if((*p)->right==NULL && (*p)->left==NULL)
							(*p)->bal=0;
						if(q->right==NULL && q->left==NULL)
							q->bal=0;
						*p=q;
#ifdef DEBUG
						std::cout<<"end SS\n"<<std::flush;
#endif
					}
					else //trebuie rotatie SD
					{
						std::cout<<"begin SD\n"<<std::flush;
						r=q->right;
						q->right=r->left;
						r->left=q;
						(*p)->left=r->right;
						r->right=*p;
						if(r->bal==-1) //s-a inserat un x pe r->left
						{
							q->bal=0;
							(*p)->bal=1;
						}
						else //s-a inserat un Y pe r->right
						{
							q->bal=-1;
							(*p)->bal=0;	
						}
						if((*p)->right==NULL && (*p)->left==NULL)
							(*p)->bal=0;
						if(q->right==NULL && q->left==NULL)
							q->bal=0;
						if(r->right==NULL && r->left==NULL)
							r->bal=0;
						*p=r;
						(*p)->bal=0;
						std::cout<<"end SD\n"<<std::flush;
					}
					//ramura stinga nu a crescut deci nu sunt modificari
					*h=false; 
					break;
				}
			}
		}
		return;
	}
	if(x==(*p)->info) //am gasit valoarea deja in arbore
	{
		(*p)->contor++;
		*h=false;
		return;
	}
	if(x>(*p)->info) //insertie si echilibrare in subarborele drept
	{
#ifdef DEBUG
		std::cout<<"insert right "<<x<<" "<<(*p)->info<<std::endl<<std::flush;
#endif
		_search_avl(x,h,&((*p)->right));
		if(*h==true) //a crescut adincimea ramurii drepte
		{
			switch((*p)->bal)
			{
			case 0: //ramura dreapta este mai lunga
				{
					(*p)->bal=1;
					break;
				}
			case -1: //cele doua ramuri sunt egale
				{
					(*p)->bal=0;
					*h=false;
					break;
				}
			case 1: //este necesare reechilibrarea
				{
					q=(*p)->right; //creem adresa catre B descendent drept al nodului A
					if(q->bal==1) //rotatie DD
					{
#ifdef DEBUG
						std::cout<<"begin DD\n"<<std::flush;
#endif
						(*p)->right=q->left;
						q->left=*p;
						(*p)->bal=0;
						q->bal=0;
						if((*p)->right==NULL && (*p)->left==NULL)
							(*p)->bal=0;
						if(q->right==NULL && q->left==NULL)
							q->bal=0;
						*p=q;
#ifdef DEBUG
						std::cout<<"end DD\n"<<std::flush;
#endif
					}
					else //rotatie DS
					{
#ifdef DEBUG
						std::cout<<"begin DS\n"<<std::flush;
#endif
						r=q->left; //pointer catre C descendent sting al lui B
						q->left=r->right;
						r->right=q;
						(*p)->right=r->left;
						r->left=*p;
						if(r->bal==1) //inserare X
						{
							(*p)->bal=-1;
							q->bal=0;
						}
						else //inserare Y
						{
							q->bal=1;
							(*p)->bal=0;
						}
						if((*p)->right==NULL && (*p)->left==NULL)
							(*p)->bal=0;
						if(q->right==NULL && q->left==NULL)
							q->bal=0;
						if(r->right==NULL && r->left==NULL)
							r->bal=0;
						*p=r;
						(*p)->bal=0;
#ifdef DEBUG
						std::cout<<"end DS\n"<<std::flush;
#endif
					}
					//ramura dreapta nu a crescut deci nu sunt modificari
					*h=false;
					break;
				}
			}
		}
	}
}

void avl_orig::run_tests(void)
{
	std::cout<<"start avl_orig tests"<<std::endl;
	/*
	insert(10);
	insert(4);
	insert(5);
	insert(7);
	insert(15);
	insert(2);
*/
	insert(50);
	insert(40);
	insert(30);
	insert(35);
	insert(37);
	insert(39);
	insert(45);
	insert(55);
	insert(42);
/*
	insert(9);
	insert(12);
	insert(14);
	insert(17);
	insert(23);
	insert(19);
	insert(50);
	insert(72);
	insert(54);
	insert(67);
	insert(76);*/
	print_all();
	std::cout<<"end avl_orig tests"<<std::endl;
}