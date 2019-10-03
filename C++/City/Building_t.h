#include <iostream>
#include <string>
#ifndef BUILDING_T_H
#define BUILDING_T_H


using namespace std;
template <class T> class Building_t
{
	public:
		Building_t(T id) { buildingId = id; }
		Building_t(const Building_t& other) { buildingId = other.buildingId; }
		~Building_t() {}
		Building_t<T>& operator=(const Building_t<T>& other);
		T getId();
		void setId(T id);
	private:
		T buildingId;
};
template <class T> Building_t<T>& Building_t<T>::operator=(const Building_t<T>& other) { buildingId = other.buildingId; return *this; }
template <class T> T Building_t<T>::getId() { return buildingId; }
template <class T> void Building_t<T>::setId(T id) { buildingId = id; }
#endif
