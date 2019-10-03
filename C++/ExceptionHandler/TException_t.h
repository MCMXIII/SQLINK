#include <string>
#ifndef TEXCEPTION_T_H
#define TEXCEPTION_T_H

template <class T> class TException_t
{
	public:
		TException_t(T o, string desc, string f, unsigned int l) { buildingId = id; }
		Building_t(const Building_t& other) { buildingId = other.buildingId; }
		~Building_t() {}
		Building_t<T>& operator=(const Building_t<T>& other);
		T getId();
		void setId(T id);
	private:
		T obj;
		string description;
		string file;
		unsigned int line;
};

#endif