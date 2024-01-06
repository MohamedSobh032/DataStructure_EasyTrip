#ifndef _PASSENGER_H_
#define _PASSENGER_H_

#include "TimeHM.h"

class Passenger
{
private:
	int PassengerID;
	int StartStation;
	int EndStation;
	int PassengerType;

	bool PassengerStatus;

	TimeHM OnOffTime;

	TimeHM AT;
	TimeHM WT;
	TimeHM FT;
public:
	Passenger();
	Passenger(int id, int StartS, int EndS, int PassType, TimeHM ArrivalTime, int OFT);

	void setPassengerID(int id);
	int getPassengerID() const;

	void setStartStation(int SS);
	int getStartStation() const;

	void setEndStation(int ES);
	int getEndStation() const;

	void setPassengerType(int PT);
	int getPassengerType() const;

	void setPassengerStatus(bool Status);
	bool getPassengerStatus() const;

	void setPromoted();
	bool getPromoted() const;

	void setOnOffTime(int OnOffTime);
	TimeHM getOnOffTime() const;
	void DecrementOnOffTime(TimeHM t);

	void setAT(TimeHM At);
	TimeHM getAT() const;

	void setWT(TimeHM Wt);
	TimeHM getWT() const;
	bool IncrementWT(int TimeStepInSeconds, int maxWT);

	void setFT(TimeHM FT);
	TimeHM getFT() const;

	Passenger(const Passenger& P);
	Passenger& operator=(const Passenger& P)
	{
		this->PassengerID = P.PassengerID;
		this->StartStation = P.StartStation;
		this->EndStation = P.EndStation;
		this->PassengerType = P.PassengerType;
		this->PassengerStatus = P.PassengerStatus;
		this->AT = P.AT;
		this->WT = P.WT;
		return *this;
	}

	~Passenger();
};
#endif

