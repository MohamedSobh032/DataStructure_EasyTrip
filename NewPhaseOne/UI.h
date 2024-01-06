#ifndef _UI_H_
#define _UI_H_
#include "StationList.h"
#include "PassengerList.h"
class UI
{
public:
	UI();
	void DisplayStation(int SID, Station* DummyStation, const TimeHM& CurrentTime, PassengerList& FP, BusQueue CUB, int MBusCapacity, int WBusCapacity);

	void END();

};
#endif
