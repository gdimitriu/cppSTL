#pragma once
class CArrayClass
{
protected:
	static int m_read_only;
	class CArray_element
	{
	private:
		int m_data;
	public:
		CArray_element(int item)
		{
			m_data=item;
			m_pnext=NULL;
		}
		CArray_element *m_pnext;
		friend class CArrayClass;
	};
	CArray_element *m_first_entry;
	CArray_element *m_last_entry;
	int m_actualsize;
public:
	CArrayClass(void);
	~CArrayClass(void);
	int set(int item, int index);
	int add(int item);
	int set_ro(void);
	int get(int index,int &item);
	void test(void);
	void print(void);
	void set_rw(void);
private:
	int test_readonly(void);
};

