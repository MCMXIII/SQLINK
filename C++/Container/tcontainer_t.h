#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <typeinfo>
#include <algorithm>
#ifndef TCONTAINER_T_H
#define TCONTAINER_T_H

using namespace std;
	template <class T, typename container=allocator<T*> > class TContainer_t
	{
		public:
			TContainer_t() {}
			~TContainer_t() {}
			T& operator[](unsigned int index);
			bool isEmpty() const { return cont.size() == 0; }
			unsigned int numOfElements() const { return cont.size(); }
			void insertToEnd(T& elem) { cont.insert(cont.end(), &elem); }
			T& getFirst() const { return *(*(cont.begin())); }
			T& getLast() const { return *(*(cont.rbegin())); }
			T& findElement(T& elem, bool (*comp)(T*, T*));
			T& removeElement(T& elem, bool (*comp)(T*, T*));
			T** removeAllElements();
			void deleteElement(T& elem, bool (*comp)(T*, T*));
			void deleteAllElements();
		private:
			container cont;
			TContainer_t(const TContainer_t<T, container> & other);
			TContainer_t<T, container>& operator=(const TContainer_t<T, container>& other);
			typename container::iterator findIterator(T& elem, bool (*comp)(T*, T*));
			static T& returnIndex(vector<T*>& contain, unsigned int& index);
			static T& returnIndex(list<T*>& contain, unsigned int& index);
	};
	template <class T, typename container=allocator<T*> > class Find
	{
		public:
			Find(T& obj, bool (*compare)(T*, T*)) {ob = &obj; com = compare; }
			bool operator()(T* other) { return com(ob, other); }
		private:
			T* ob;
			bool (*com)(T*, T*);
	};
	template <class T, typename container> T& TContainer_t<T, container>::returnIndex(vector<T*>& contain, unsigned int& index)
	{
		return *(contain[index]);
	}
	template <class T, typename container> T& TContainer_t<T, container>::returnIndex(list<T*>& contain, unsigned int& index)
	{
		list<T*> l;
		typename list<T*>::iterator it = l.end();
		return *(*(it));
	}
	template <class T, typename container> T& TContainer_t<T, container>::operator[](unsigned int index)
	{
		try
		{
			int ex = 0;
			if(index >= cont.size())
			{
				throw(ex);
			}
			string name =  typeid(cont).name();
			if(name.find("vector", 0) < name.length()) return TContainer_t<T, container>::returnIndex(cont, index);
			unsigned int i = 0;
			for (typename container::iterator it=cont.begin(); it != cont.end(); it++)
			{
				if(i++ == index) return *(*it);
			}
		}
		catch(int ex)
		{
			cout << "Invalid index!\n";
			return *(*(cont.begin()));
		}
	}
	template <class T, typename container> typename container::iterator TContainer_t<T, container>::findIterator(T& elem, bool (*comp)(T*, T*))
	{
		typename container::iterator it = find_if(cont.begin(), cont.end(), typename Find<T, container>::Find(elem, comp));
		return it;
	}
	template <class T, typename container> T& TContainer_t<T, container>::findElement(T& elem, bool (*comp)(T*, T*))
	{
		typename container::iterator it = findIterator(elem, comp);
		if(it == cont.end())
		{
			cout << "Not found, original parameter returned...\n";
			return elem;
		}
		return *(*(it));
	}
	template <class T, typename container> T& TContainer_t<T, container>::removeElement(T& elem, bool (*comp)(T*, T*))
	{
		typename container::iterator it = findIterator(elem, comp);
		if(it == cont.end())
		{
			cout << "Not found, original parameter returned...\n";
			return elem;
		}
		T& tr = *(*(it));
		cont.erase(it);
		return tr;		
	}
	template <class T, typename container> T** TContainer_t<T, container>::removeAllElements()
	{
		T** arr = new T*[cont.size()];
		unsigned int i = 0;
		for (typename container::iterator it=cont.begin(); it != cont.end();)
		{
			arr[i++] = *it;
			cont.erase(it);
		}
		return arr;
	}
	template <class T, typename container> void TContainer_t<T, container>::deleteElement(T& elem, bool (*comp)(T*, T*))
	{
		typename container::iterator it = findIterator(elem, comp);
		if(it == cont.end())
		{
			cout << "Not found...\n";
			return;
		}
		T* tp = *it;
		cont.erase(it);		
	}
	template <class T, typename container> void TContainer_t<T, container>::deleteAllElements()
	{
		T** arr = new T*[cont.size()];
		unsigned int i = 0;
		for (typename container::iterator it=cont.begin(); numOfElements() != 0; it)
		{
			arr[i++] = *it;
			cont.erase(it);
		}
	}
#endif