#include <iostream>
#include <string>
#include <vector>
#include "Building_t.h"
#ifndef STREET_T_H
#define STREET_T_H


using namespace std;
template <class sID, class bID> class Street_t
{
	public:
		Street_t(sID id) { streetId = id; }
		Street_t(const Street_t<sID, bID>& other) { streetId = other.streetId; buildings.clear(); for(int i = 0; i < other.buildings.size(); i++) buildings.insert(buildings.end(), *(new Building_t<bID>(other.buildings[i]))); }
		~Street_t() {}
		Street_t<sID, bID>& operator=(const Street_t<sID, bID>& other);
		sID getId();
		void setId(sID id);
		void addBuilding(Building_t<bID> building);
		void addBuilding(bID buildingID);
		Building_t<bID>& getBuilding(bID buildingID);
		Building_t<bID>& getBuildingByPlace(unsigned int index);
	private:
		sID streetId;
		vector<Building_t<bID> > buildings;
};
template <class sID, class bID> Street_t<sID, bID>& Street_t<sID, bID>::operator=(const Street_t<sID, bID>& other) { streetId = other.streetId; buildings.clear(); for(int i = 0; i < other.buildings.size(); i++) buildings.insert(buildings.end(), *(new Building_t<bID>(other.buildings[i]))); return *this; }
template <class sID, class bID> sID Street_t<sID, bID>::getId() { return streetId; }
template <class sID, class bID> void Street_t<sID, bID>::setId(sID id) { streetId = id; }
template <class sID, class bID> void Street_t<sID, bID>::addBuilding(Building_t<bID> building) { buildings.insert(buildings.end(), building); }
template <class sID, class bID> void Street_t<sID, bID>::addBuilding(bID buildingID) { buildings.insert(buildings.end(), *(new Building_t<bID>(buildingID))); }
template <class sID, class bID> Building_t<bID>& Street_t<sID, bID>::getBuilding(bID buildingID) { for(int i = 0; i < buildings.size(); i++) {if (buildings[i].getId() == buildingID) return buildings[i];}}
template <class sID, class bID> Building_t<bID>& Street_t<sID, bID>::getBuildingByPlace(unsigned int index) { return buildings[index];}
#endif
