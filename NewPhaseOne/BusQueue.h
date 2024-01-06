#ifndef _BUS_QUEUE_H_
#define _BUS_QUEUE_H_
#include "LinkedQueue.h"
#include "Bus.h"
class BusQueue : public LinkedQueue<Bus*>
{
public:
	int IncrementTimeNotInStation(int TimeBetweenStationInMinutes, int StepSizeInSeconds);
	void IncrementTimeInStation(int StepSizeInSeconds, int SID);
	void DecrementMaintenanceTimeQueue(int TimeStepInSeconds);
	int CountMBBus();
	int CountWBBus();

	bool PeekBus(int& ID, bool& Type, int& CurrentCap, int maxc, int index);
	bool PeekPassengerOnBus(int busid, int& PID, int index);

	int CountPassengerOnBus(int busid);

};
#endif
