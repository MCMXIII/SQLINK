#include <iostream>
#include <string>
#include <vector>
#include "Street_t.h"
#ifndef CITY_T_H
#define CITY_T_H


using namespace std;
template <class cID, class sID, class bID> class City_t
{
	public:
		City_t(cID id) { cityId = id; }
		City_t(const City_t<cID, sID, bID>& other) { cityId = other.cityId; streets.clear(); for(int i = 0; i < other.streets.size(); i++) streets.insert(streets.end(), *(new Street_t<sID, bID>(other.streets[i]))); }
		~City_t() {}
		City_t<cID, sID, bID>& operator=(const City_t<cID, sID, bID>& other);
		cID getId();
		void setId(cID id);
		void addStreet(Street_t<sID, bID> street);
		void addStreet(sID streetID);
		Street_t<sID, bID>& getStreet(sID streetID);
		Street_t<sID, bID>& getStreetByPlace(unsigned int index);
	private:
		cID cityId;
		vector<Street_t<sID, bID> > streets;
};
template <class cID, class sID, class bID> City_t<cID, sID, bID>& City_t<cID, sID, bID>::operator=(const City_t<cID, sID, bID>& other) { cityId = other.cityId; streets.clear(); for(int i = 0; i < other.streets.size(); i++) streets.insert(streets.end(), *(new Street_t<sID, bID>(other.streets[i]))); return *this; }
template <class cID, class sID, class bID> cID City_t<cID, sID, bID>::getId() { return cityId; }
template <class cID, class sID, class bID> void City_t<cID, sID, bID>::setId(cID id) { cityId = id; }
template <class cID, class sID, class bID> void City_t<cID, sID, bID>::addStreet(Street_t<sID, bID> street) { streets.insert(streets.end(), street); }
template <class cID, class sID, class bID> void City_t<cID, sID, bID>::addStreet(sID streetID) { streets.insert(streets.end(), *(new Street_t<sID, bID>(streetID))); }
template <class cID, class sID, class bID> Street_t<sID, bID>& City_t<cID, sID, bID>::getStreet(sID streetID) { for(int i = 0; i < streets.size(); i++) {if (streets[i].getId() == streetID) return streets[i];}}
template <class cID, class sID, class bID> Street_t<sID, bID>& City_t<cID, sID, bID>::getStreetByPlace(unsigned int index) { return streets[index];}
#endif
