#ifndef _STATION_H_
#define _STATION_H_
#include "Passenger.h"
#include "PassengerQueue.h"
#include "PassengerPrioQueue.h"
#include "BusQueue.h"
class Station
{
	int StationID;

	BusQueue busFWD;
	BusQueue busBWD;

	PassengerQueue WheelPassengerQueueFWD;
	PassengerPrioQueue PassengerPrioQueueFWD;
	PassengerQueue WheelPassengerQueueBWD;
	PassengerPrioQueue PassengerPrioQueueBWD;

public:
	// Constructors
	Station();
	Station(int ID);
	//setters and getters
	void setStationID(int ID);
	int getStationID() const;
	//Printing Function (was made for testing)
	void PrintAllQueues() const;
	/* EVENT FUNCTIONS */
	void AddPassengerToQueue(Passenger* newps);
	bool RemovePassenger(int ID);
	/* REMOVE FIRST PASSNGERTYPE FUNCTION */
	bool RemoveNPSP(bool NormalOrNot, Passenger*& p);
	bool RemoveWP(Passenger*& p);
	/* THIS FUNCTION IS CALLED WHENEVER THE BUS ARRIVES TO A STATION */
	void BusArrived(Bus* bus);
	/* INCREMENT WAITING TIME FUNCTION */
	void IncrementQueuesWaitingTime(int TimeStepInSeconds,int maxWaitingTime, int SID); //max waitign time
	/* STATION #0 FUNCTIONS */
	void DequeueBusS0(Bus*& b);
	/* Get Sizes Functions */
	int CountSizeSP();
	int CountSizeNP();
	int CountSizeWP();
	int CountMBBusFWD();
	int CountWBBusFWD();
	int CountMBBusBWD();
	int CountWBBusBWD();
	int CountPassengerOnBusFWD(int busid);
	int CountPassengerOnBusBWD(int busid);

	/* Peek Elements In Queues */
	bool PeekWheelFWD(int& ID, int index);
	bool PeekWheelBWD(int& ID, int index);
	bool PeekSPNPFWD(int& ID, int& prio, int index);
	bool PeekSPNPBWD(int& ID, int& prio, int index);




	bool PeekFWDBus(int& ID, bool& Type, int& CurrentCapacity, int TotalCapacity, int index);
	bool PeekBWDBus(int& ID, bool& Type, int& CurrentCapacity, int TotalCapacity, int index);
	bool PeekPassengerOnBusFWD(int busid, int& PID, int index);
	bool PeekPassengerOnBusBWD(int busid, int& PID, int index);

	bool isEmptyStation() const;


	/* Firstly, let's Drop the Passengers ONE BY ONE */
	/* This Function will be called untill both Forward Time and Backward Time returns -1 */
	bool DropPassengerFromBusFWD(Passenger*& p);
	bool DropPassengerFromBusBWD(Passenger*& p);
	/* Then, Add Passengers to the Bus ONE BY ONE */
	bool AddPassengerToBusFWD(int CapacityMB, int CapacityWB, Bus*& b);
	bool AddPassengerToBusBWD(int CapacityMB, int CapacityWB, Bus*& b);

	void GetBUBT(float& BU, TimeHM& BT, TimeHM TS, int BCM, int BCW);

	~Station();

};
#endif

