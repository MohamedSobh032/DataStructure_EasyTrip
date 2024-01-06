#ifndef _BUS_H_
#define _BUS_H_
#include "Passenger.h"
#include "PassengerPrioQueue.h"
class Bus
{
private:
	int BusID;
	bool BusType;
	bool BusStatus;
	TimeHM MaintenanceTime;
	int CurrentPassenger;
	PassengerPrioQueue PassengerOnBus;
	int TotalPassengers;
	int CurrentStation;
	/* The journeys taken variable is just a counter for journeys, not the actual journeys taken */
	int JourneysTaken;
	bool Direction;
	int TotalJourneysTaken;
	TimeHM TimeNotInStation;
	TimeHM TotalTimeInStation;
	TimeHM BusyTime;
public:
	/* Default Constructor */
	Bus();
	/* Constructor */
	Bus(int Id, bool T, int MT);

	void setBusID(int ID);
	int getBusID() const;

	void setBusType(bool T);
	bool getBusType() const;

	void setBusStatus(bool S);
	bool getBusStatus() const;
	/* Toggles the Current Status, should be called whenever a bus reaches his maximum journeys */
	void ToggleBusStatus();

	void setMaintenanceTime(int MT);
	TimeHM getMaintenanceTime() const;
	/* Decrement the maintenace time, when MT <= 0, toggles bus status to working */
	bool DecrementMaintenanceTime(int TimeStepInSeconds);

	void setCurrentPassenger(int CP);
	int getCurrentPassenger() const;
	/* Takes the maximum capacity, returns the available passengers */
	int getAvailablePassenger(int C);

	/* Adds passenger to the bus' prio queue passenger, it inserts correctly */
	bool AddPassenger(int C, Passenger*& p);
	/* checks if the current station is the station that the passenger should be dropped at */
	/* returns false if it will not drop the passenger, if will drop, returns true */
	bool DropPassenger(Passenger*& ps);




	void setTotalPassengers(int TP);
	int getTotalPassengers() const;
	/* should be called whenever a new passenger gets on the bus */
	void IncrementTotalPassengers();

	void setCurrentStation(int CS);
	void IncrementCurrentStation();
	/* returns the current station of the bus, if the bus is not in a station, it returns the previous station */
	int getCurrentStation() const;

	void setJourneysTaken(int JT);
	int getJourneysTaken() const;
	/* if the bus reached his max journeys, it checks whether he is at station 0 */
	/* if at station 0, it set the status to maintenance, if not, it is still working */
	bool IncrementJourneysTaken(int MAXJ, int WBMT, int MBMT);

	void setDirection(bool D);
	bool getDirection() const;
	void ToggleDirection();

	void setTotalJourneysTaken(int TJ);
	int getTotalJourneysTaken() const;
	void IncrementTotalJourneysTaken();

	void setTimeNotInStation(TimeHM t);
	TimeHM getTimeNotInStation() const;
	bool IncrementTimeNotInStation(int TimeBetweenStationInMinutes, int StepSizeInSeconds);
	void ResetTimeNotInStation();

	void setTotalTimeInStation(TimeHM t);
	TimeHM getTotalTimeInStation() const;
	bool IncrementTotalTimeInStation(int StepSizeInSeconds, int StationID);

	void setBusyTime(TimeHM t);
	TimeHM getBusyTime() const;
	void IncrementBusyTime(int StepSizeInSeconds);

	float BusUtilization(int BCM, int BCW, TimeHM TS);



	bool getPassenger(int index, int& PID);


	Bus(const Bus& b);
	Bus& operator=(const Bus& b)
	{
		this->BusID = b.BusID;
		this->BusType = b.BusType;
		this->BusStatus = b.BusStatus;
		this->MaintenanceTime = b.MaintenanceTime;
		this->CurrentPassenger = b.CurrentPassenger;
		this->PassengerOnBus = b.PassengerOnBus;
		this->TotalPassengers = b.TotalPassengers;
		this->CurrentStation = b.CurrentStation;
		this->JourneysTaken = b.JourneysTaken;
		this->Direction = b.Direction;
		this->TotalJourneysTaken = b.TotalJourneysTaken;
		this->TimeNotInStation = b.TimeNotInStation;
		this->TotalTimeInStation = b.TotalTimeInStation;
		this->BusyTime = b.BusyTime;
		return *this;
	}

	~Bus();
};
#endif

