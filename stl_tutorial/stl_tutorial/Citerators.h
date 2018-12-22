#pragma once
class Citerators
{
private:
	template <typename container,typename T> container make(const T str[]);
	void ex04_01(void);
	void iterators_wo_examples(void);
public:
	Citerators(void);
	~Citerators(void);
	void run(void);
private:
	void istream_ex(void);
	void ostream_ex(void);
	void iostream_ex(void);
	void setmap_ex(void);
};

