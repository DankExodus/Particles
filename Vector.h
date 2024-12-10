#pragma once
#include <iostream>
using namespace std;


/// most of vector minus the iterator stuff
namespace Vector
{
	template<typename T>	/// only applies to class declaration
	class vector
	{
	private:
		size_t sz;
		T* elem;	/// pointer to array
		size_t space;		/// how big is the array
	public:
		vector() : sz{ 0 }, elem{ nullptr }, space{ 0 } {}		/// the curly brackets offer more flexibility than just parentheses 
		vector(size_t s) : sz{ s }, elem{ new T[s] }, space{ s }{}		/// constructing with given size s
		
		/// Big Three
		vector(const vector&);
		vector& operator=(const vector&);
		~vector() { delete[] elem; cout << "Destructor called" << endl; }

		/// access operators
		T& at(size_t n);
		const T& at(size_t n) const;
		T& operator[](size_t n);
		const T& operator[](size_t n) const;

		size_t size() const { return sz; }
		void resize(size_t newsize); 
		void push_back(T d);	/// takes on new type T called d

		void reserve(size_t newalloc);
		int capacity() const { return space; }
	};


	template<typename T>		/// need to re-declare template again
	T& vector<T>::operator[](size_t n)
	{
		return elem[n];
	}
	template<typename T>
	const T& vector<T>::operator[](size_t n) const
	{
		return elem[n];
	}

	struct out_of_range {};

	template<typename T>		
	T& vector<T>::at(size_t n)
	{
		if (n < 0 || n >= sz) throw out_of_range();
		return elem[n];
	}
	template<typename T>
	const T& vector<T>::at(size_t n) const
	{
		if (n < 0 || n >= sz) throw out_of_range();
		return elem[n];
	}

	/// copy constructor
	template<typename T>
	vector<T>::vector(const vector<T>& a)
		: sz{ a.sz }, elem{ new T[sz] }, space{ a.sz }
	{
		//sz = a.sz
		//elem = new T[sz]
		cout << "Copy constructor" << endl;
		for (size_t i = 0; i < sz; i++) elem[i] = a.elem[i];
	}

	/// copy assignment
	template<typename T>
	vector<T>& vector<T>::operator=(const vector<T>& a)
	{
		cout << "Copy assignment" << endl;
		
		if (this == &a) return *this;		/// guard against self-assignment

		if (a.sz <= space)		/// enough space to copy a's array into ours
		{
			for (size_t i = 0; i < a.sz; i++) elem[i] = a.elem[i];
			sz = a.sz;
			return *this;
		}

		/// if we get here, we didn't have enough space allocated yet
		T* p = new T[a.sz];
		for (size_t i = 0; i < a.sz; i++) p[i] = a.elem[i];
		delete[] elem;
		sz = a.sz;
		space = a.space;
		elem = p;
		return *this;
	}

	template<typename T>
	void vector<T>::reserve(size_t newalloc)
	{
		if (space >= newalloc) return;
		T* p = new T[newalloc];
		for (size_t i = 0; i < sz; i++) p[i] = elem[i];
		delete[] elem;
		elem = p;
		space = newalloc;		/// size doesn't change but space does
	}

	template<typename T>
	void vector<T>::push_back(T d)
	{
		if (sz == 0)
		{
			reserve(8);
		}
		else if (sz == space)
		{
			reserve(2 * space);
		}

		elem[sz] = d;
		++sz;
	}

	template<typename T>
	void vector<T>::resize(size_t newsize)
	{
		reserve(newsize);
		for (size_t i = sz; i < newsize; i++) elem[i] = T();	/// T() is a cpp trick to set a generalized default value
		sz = newsize;
	}

	template<typename T>
	ostream& operator<<(ostream& os, const vector<T>& v)
	{
		for (size_t i = 0; i < v.size(); i++)
		{
			os << v[i] << " ";
		}

		return os;
	}
}
