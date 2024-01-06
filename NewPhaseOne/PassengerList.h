#ifndef _PASSENGER_LIST_H_
#define _PASSENGER_LIST_H_
#include "LinkedList.h"
#include "Passenger.h"
class PassengerList : public LinkedList<Passenger*>
{
public:
	bool PeekID(int& D, int ID);
	void GetMinFT(TimeHM& FT, int& ID, TimeHM& AT, TimeHM& WT, int& Ptype);
};
#endif // _PASSENGER_LIST_H_

