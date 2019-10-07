#ifndef TCONTAINER_T_H
#define TCONTAINER_T_H

	template <class T, class container<T*>> class TContainer_t
	{
		public:
			TContainer_t();
			~TContainer_t() {}
			T& operator[](unsigned int index);
			bool isEmpty() const;
			unsigned int numOfElements() const;
			void insertToEnd(T elem);
			T getFirst() const;
			T getLast() const;
			T* findElement(T elem) const;
			T* removeElement(T elem);
			T** removeAllElements();
			void deleteElement(T elem);
			void deleteAllElements();
		private:
			container<T*> cont;
			TContainer_t(const TContainer_t<T, container<T*>>& other);
			TContainer_t<T, container<T>>& operator=(const TContainer_t<T, container<T*>>& other);
	}

#endif
