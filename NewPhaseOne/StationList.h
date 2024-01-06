#ifndef _STATION_LIST_H_
#define _STATION_LIST_H_
#include "LinkedList.h"
#include "Station.h"
class StationList : public LinkedList<Station*>
{
public:
	void PrintAllStations() const;
};
#endif

