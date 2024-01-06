#ifndef _COMPANY_H_
#define _COMPANY_H_
#include "TimeHM.h"
#include "StationList.h"
#include "EventQueue.h"
#include "PassengerList.h"
#include <string>
#include "UI.h"

class Company
{
private:
	TimeHM TimeStep;
	int NumberOfStations;
	int MinsBetweenStations;
	int WBUS;
	int MBUS;
	int WBUSCapacity;
	int MBUSCapacity;
	int MaxJourneys;
	int WBUSMaintenanceTime;
	int MBUSMaintenanceTime;
	int MaxW;
	int OnOffTime;
	int MaxLines;
	int CurrentLine;
	int CDdropper;
	PassengerList FinishedPassenger;
	BusQueue MixedBussesNotInStation;
	BusQueue WheelBussesNotInStation;
	BusQueue CheckUpBusses;
	StationList S;
	EventQueue EV;

	UI Display;
public:
	Company();
	bool FileLoader(string filename);
	void IncrementTimeStep();
	bool CallEvent();


	void InitializeStations();
	void InitializeBusses();

	void IncrementWaitingTimeInStation(int TimeStepInSeconds);
	void IncrementBusTimeNotInStation(int TimeStepInSeconds);

	bool DropPassengersFromAllStations(int TimeStepInSeconds);



	void DecrementMaintenanceTime(int TimeStepInSeconds);

	void GenerateRandStation();
	void CallUI(int& SID);
	bool EndCode();

	bool Output();

	void DisplayEnd();
};

#endif

