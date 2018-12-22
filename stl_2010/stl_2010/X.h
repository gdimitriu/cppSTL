//#include <iterator>
#include <iostream>
#include <allocators>
_STD_BEGIN
template <class A, class T = std::allocator<T> >
class X {
public:
    typedef T allocator_type;
    typedef typename A::value_type value_type; 
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    class iterator { 
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
		typedef typename A::size_type size_type;
        typedef bidirectional_iterator_tag iterator_category;

        iterator();
        iterator(const iterator&);
        ~iterator();

        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        bool operator<(const iterator&) const; //optional
        bool operator>(const iterator&) const; //optional
        bool operator<=(const iterator&) const; //optional
        bool operator>=(const iterator&) const; //optional

        iterator& operator++();
        iterator operator++(int); //optional
        iterator& operator--(); //optional
        iterator operator--(int); //optional
/*        iterator& operator+=(size_type); //optional
        iterator operator+(size_type) const; //optional
        friend iterator operator+(size_type, const iterator&) //optional
        iterator& operator-=(size_type); //optional            
        iterator operator-(size_type) const; //optional */
        difference_type operator-(iterator) const; //optional

        reference operator*() const;
        pointer operator->() const;
        reference operator[](size_type) const; //optional
    };
    class const_iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference const_reference;
        typedef typename A::pointer const_pointer;
        typedef bidirectional_iterator_tag iterator_category;

        const_iterator ();
        const_iterator (const const_iterator&);
        const_iterator (const iterator&);
        ~const_iterator();

        const_iterator& operator=(const const_iterator&);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
        bool operator<(const const_iterator&) const; //optional
        bool operator>(const const_iterator&) const; //optional
        bool operator<=(const const_iterator&) const; //optional
        bool operator>=(const const_iterator&) const; //optional

        const_iterator& operator++();
        const_iterator operator++(int); //optional
        const_iterator& operator--(); //optional
        const_iterator operator--(int); //optional
/*        const_iterator& operator+=(size_type); //optional
        const_iterator operator+(size_type) const; //optional
        friend const_iterator operator+(size_type, const const_iterator&) //optional
        const_iterator& operator-=(size_type); //optional            
        const_iterator operator-(size_type) const; //optional */
        difference_type operator-(const_iterator) const; //optional

        const_reference operator*() const;
        const_pointer operator->() const;
        const_reference operator[](size_type) const; //optional
    };

    typedef std::reverse_iterator<iterator> reverse_iterator; //optional
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional

    X();
    X(const X&);
    ~X();

    X& operator=(const X&);
    bool operator==(const X&) const;
    bool operator!=(const X&) const;
    bool operator<(const X&) const; //optional
    bool operator>(const X&) const; //optional
    bool operator<=(const X&) const; //optional
    bool operator>=(const X&) const; //optional

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin(); //optional
    const_reverse_iterator rbegin() const; //optional
    const_reverse_iterator crbegin() const; //optional
    reverse_iterator rend(); //optional
    const_reverse_iterator rend() const; //optional
    const_reverse_iterator crend() const; //optional

    reference front(); //optional
    const_reference front() const; //optional
    reference back(); //optional
    const_reference back() const; //optional
    template<class ...Args>
    void emplace_front(Args...); //optional
    template<class ...Args>
    void emplace_back(Args...); //optional
    void push_front(const T&); //optional
    void push_front(T&&); //optional
    void push_back(const T&); //optional
    void push_back(T&&); //optional
    void pop_front(); //optional
    void pop_back(); //optional
    reference operator[](size_type); //optional
    const_reference operator[](size_type) const; //optional
    reference at(size_type); //optional
    const_reference at(size_type) const; //optional

    template<class ...Args>
    iterator emplace(const_iterator, Args...); //optional
    iterator insert(const_iterator, const T&); //optional
    iterator insert(const_iterator, T&&); //optional
    iterator insert(const_iterator, size_type, T&); //optional
    template<class iter>
    iterator insert(const_iterator, iter, iter); //optional
    iterator insert(const_iterator, std::initializer_list<T>); //optional
    iterator erase(const_iterator); //optional
    iterator erase(const_iterator, const_iterator); //optional
    void clear(); //optional
    template<class iter>
    void assign(iter, iter); //optional
    void assign(std::initializer_list<T>); //optional
    void assign(size_type, const T&); //optional

    void swap(const X&);
    size_type size();
    size_type max_size();
    bool empty();

    A get_allocator(); //optional
};
template <class T, class A = std::allocator<T> >
	std::swap(X<T,A>&, X<T,A>&); //optional
_STD_END