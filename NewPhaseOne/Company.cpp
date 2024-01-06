#include "DEFS.h"
#include "Arrival.h"
#include "Leave.h"
#include "Company.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


Company::Company()
{
	this->TimeStep = 0;
	this->NumberOfStations = 0;
	this->MinsBetweenStations = 0;
	this->WBUS = 0;
	this->MBUS = 0;
	this->WBUSCapacity = 0;
	this->MBUSCapacity = 0;
	this->MaxJourneys = 0;
	this->WBUSMaintenanceTime = 0;
	this->MBUSMaintenanceTime = 0;
	this->MaxW = 0;
	this->OnOffTime = 0;
	this->MaxLines = 0;
	this->CurrentLine = 0;
	this->CDdropper = 0;
}
bool Company::FileLoader(string filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Error opening file: Filename does not exist" << endl;
		return false;
	}
	file >> NumberOfStations >> MinsBetweenStations;
	file >> WBUS >> MBUS;
	file >> WBUSCapacity >> MBUSCapacity;
	file >> MaxJourneys >> WBUSMaintenanceTime >> MBUSMaintenanceTime;
	file >> MaxW >> OnOffTime;
	file >> MaxLines;
	//CDdropper = OnOffTime;

	int iterator = 0;
	char EventType = 0;

	for (int iterator = 0; iterator < MaxLines; iterator++)
	{
		file >> EventType;
		if (EventType == 'A')
		{
			char PassengerType[2];
			int hours, minutes, ID, SS, ES, ActualPT = 0;
			char semi;
			file >> PassengerType[0] >> PassengerType[1];
			file >> hours >> semi >> minutes;
			TimeHM timeArrived(hours, minutes, 0);
			file >> ID >> SS >> ES;
			if (PassengerType[0] == 'S')
			{
				char Ps;
				file >> Ps;
				if (Ps == 'A' || Ps == 'a')
				{
					ActualPT = SPAged;
					file >> Ps >> Ps >> Ps;
				}
				else
				{
					file >> Ps;
					if (Ps == 'o' || Ps == 'O')
					{
						ActualPT = SPPod;
						file >> Ps;
					}
					else
					{
						ActualPT = SPPW;
						file >> Ps >> Ps >> Ps >> Ps >> Ps >> Ps;
					}
				}
			}
			else if (PassengerType[0] == 'N')
			{
				ActualPT = NP;
			}
			else
			{
				ActualPT = WP;
			}
			Event* E = new Arrival(iterator, ActualPT, timeArrived, ID, SS, ES);
			EV.enqueue(E);
		}
		else
		{
			int hours, minutes, ID, SS;
			char semi;
			file >> hours >> semi >> minutes;
			file >> ID >> SS;
			TimeHM timeArrived(hours, minutes, 0);
			Event* E = new Leave(iterator, timeArrived, ID, SS);
			EV.enqueue(E);
		}
	}
	return true;
}
void Company::IncrementTimeStep()
{
	TimeStep += 60;
	if (TimeStep.getHours() == 24)
		TimeStep.setHours(0);	
	static TimeHM Release(0, 0, 0);
	Station* S0;
	if (TimeStep <= 4 * 3600 || TimeStep >= 22 * 3600)	//NOT WORKING HOURS
	{
		S.peek(S0,0);
		this->DecrementMaintenanceTime(60);
		IncrementWaitingTimeInStation(60);
		IncrementBusTimeNotInStation(60);
	}
	else												//WORKING HOURS
	{
		Release += 60;
		S.peek(S0,0);
		if (Release.getMinutes() >= 15)
		{
			Bus* b = nullptr;
			S0->DequeueBusS0(b);
			if (b != nullptr && (b->getBusStatus() == Working) && (b->getBusType() == MB))
				MixedBussesNotInStation.enqueue(b);
			else if (b != nullptr && (b->getBusStatus() == Working) && (b->getBusType() == WB))
				WheelBussesNotInStation.enqueue(b);
			Release = 0;
		}
		this->DecrementMaintenanceTime(60);
		this->IncrementWaitingTimeInStation(60);
		this->IncrementBusTimeNotInStation(60);
		this->DropPassengersFromAllStations(60);
	}
}
bool Company::CallEvent()
{
	Event* E0 = nullptr;
	Station* dummyStation;
	if (!EV.peek(E0))
		return false;
	TimeHM EventTime = E0->getHM();
	while (EventTime <= TimeStep)
	{
		S.peek(dummyStation, E0->getStartS());
		Passenger* newps = new Passenger(E0->getPassengerID(), E0->getStartS(), E0->getEndS(), E0->getPsType(), EventTime, OnOffTime);
		E0->Execute(newps, dummyStation);
		EV.dequeue(E0);
		CurrentLine++;
		delete E0;
		if (!EV.peek(E0))
			return false;
		EventTime = E0->getHM();
	}
	return true;
}
void Company::InitializeStations()
{
	for (int i = 0; i < NumberOfStations+1; i++)
	{
		Station* newS = new Station(i);
		S.InsertEnd(newS);
	}
}
void Company::InitializeBusses()
{	
	for (int i = 1; i < MBUS+1; i++)
	{
		Bus* m = new Bus(i, MB, MBUSMaintenanceTime);
		MixedBussesNotInStation.enqueue(m);
	}
	for (int i = MBUS+1; i < WBUS + MBUS+1; i++)
	{
		Bus* w = new Bus(i, WB, WBUSMaintenanceTime);
		WheelBussesNotInStation.enqueue(w);
	}
	Bus* m;
	Station* s;
	S.peek(s,0);
	char flag = false;
	for (int i = 0; i < WBUS + MBUS; i++)
	{
		//if false insert Mbus first, if true insert Wbus
		if (flag == false)
		{
			if (MixedBussesNotInStation.dequeue(m))
			{
				s->BusArrived(m);
				m->setCurrentStation(0);
			}
			flag = true;
		}
		else
		{
			if (WheelBussesNotInStation.dequeue(m))
			{
				s->BusArrived(m);
				m->setCurrentStation(0);
			}
			flag = false;
		}
	}
}
void Company::IncrementWaitingTimeInStation(int TimeStepInSeconds)
{
	Station* dummyStation;
	for (int i = 1; i < NumberOfStations + 1; i++)
	{
		S.peek(dummyStation, i);
		dummyStation->IncrementQueuesWaitingTime(TimeStepInSeconds,MaxW,i);
	}
}
void Company::IncrementBusTimeNotInStation(int TimeStepInSeconds)
{
	Bus* b = nullptr;
	Station* s = nullptr;
	int currentStation = 0;
	int PrevStation = 0;
	bool direction = false;

	for (int i = 0; i < MixedBussesNotInStation.getCount(); i++)
	{
		MixedBussesNotInStation.dequeue(b);
		if (b->IncrementTimeNotInStation(MinsBetweenStations, 60))
		{
			PrevStation = b->getCurrentStation();
			direction = b->getDirection();
			if (direction == FWD)
				currentStation = PrevStation + 1;
			else
				currentStation = PrevStation - 1;
			S.peek(s, currentStation);
			if (currentStation == NumberOfStations)
			{
				b->IncrementTotalJourneysTaken();
				b->ToggleDirection();
				s->BusArrived(b);
				b->setCurrentStation(NumberOfStations);
				b->IncrementJourneysTaken(MaxJourneys, WBUSMaintenanceTime, MBUSMaintenanceTime);
			}
			else if (currentStation == 0)
			{
				b->ToggleDirection();
				b->setCurrentStation(0);
				b->IncrementTotalJourneysTaken();
				b->IncrementJourneysTaken(MaxJourneys, WBUSMaintenanceTime, MBUSMaintenanceTime);
				if (b->getBusStatus() == Maintenance)
					CheckUpBusses.enqueue(b);
				else
				{
					s->BusArrived(b);
				}
			}
			else
			{
				b->IncrementCurrentStation();
				s->BusArrived(b);
			}
		}
		else
			MixedBussesNotInStation.enqueue(b);
	}
	for (int i = 0; i < WheelBussesNotInStation.getCount(); i++)
	{
		WheelBussesNotInStation.dequeue(b);
		if (b->IncrementTimeNotInStation(MinsBetweenStations, 60))
		{
			PrevStation = b->getCurrentStation();
			direction = b->getDirection();
			if (direction == FWD)
				currentStation = PrevStation + 1;
			else
				currentStation = PrevStation - 1;
			S.peek(s, currentStation);
			if (currentStation == NumberOfStations)
			{
				b->IncrementTotalJourneysTaken();
				b->IncrementJourneysTaken(MaxJourneys, WBUSMaintenanceTime, MBUSMaintenanceTime);
				b->ToggleDirection();
				s->BusArrived(b);
			}
			else if (currentStation == 0)
			{
				b->IncrementTotalJourneysTaken();
				b->IncrementJourneysTaken(MaxJourneys, WBUSMaintenanceTime, MBUSMaintenanceTime);
				b->ToggleDirection();
				if (b->getBusStatus() == Maintenance)
					CheckUpBusses.enqueue(b);
				else
					s->BusArrived(b);
			}
			else
				s->BusArrived(b);
		}
		else
			WheelBussesNotInStation.enqueue(b);

	}
}
bool Company::DropPassengersFromAllStations(int TimeStepInSeconds)
{
	Station* CS = nullptr;
	Passenger* p = nullptr;
	for (int i = 1; i < NumberOfStations + 1; i++)
	{
		S.peek(CS, i);
		TimeHM t(0, 1, 0);
		TimeHM t2(0, 1, 0);
		while (t != 0 && CS->DropPassengerFromBusFWD(p))
		{
			t -= OnOffTime;
			if (p != nullptr)
			{
				p->setFT(TimeStep);
				FinishedPassenger.InsertBeg(p);
				p = nullptr;
			}
			else if (p == nullptr)
			{
				// add here
				t2 -= t;
				Bus* b = nullptr;
				while (t2 != 0 && CS->AddPassengerToBusFWD(MBUSCapacity, WBUSCapacity, b))
				{
					t2 -= OnOffTime;
				}
				if (b != nullptr)
				{
					if (b->getBusType() == MB)
						MixedBussesNotInStation.enqueue(b);
					else
						WheelBussesNotInStation.enqueue(b);
				}
				t = 0;
				t2 = 0;
			}
		}
		t = 60;
		t2 = 60;
		p = nullptr;
		while (t != 0 && CS->DropPassengerFromBusBWD(p))
		{
			t -= OnOffTime;
			if (p != nullptr)
			{
				p->setFT(TimeStep);
				FinishedPassenger.InsertBeg(p);
				p = nullptr;
			}
			else if (p == nullptr)
			{
				// add here
				t2 -= t;
				Bus* b = nullptr;
				while (t2 != 0 && CS->AddPassengerToBusBWD(MBUSCapacity, WBUSCapacity, b))
				{
					t2 -= OnOffTime;
				}
				if (b != nullptr)
				{
					if (b->getBusType() == MB)
						MixedBussesNotInStation.enqueue(b);
					else
						WheelBussesNotInStation.enqueue(b);
				}
				t = 0;
			}
		}


	}
	return true;
}

void Company::DecrementMaintenanceTime(int TimeStepInSeconds)
{
	CheckUpBusses.DecrementMaintenanceTimeQueue(TimeStepInSeconds);
	Bus* b = nullptr;
	for (int i = 0; i < CheckUpBusses.getCount(); i++)
	{
		CheckUpBusses.dequeue(b);
		if (b->getBusStatus() == Maintenance)
			CheckUpBusses.enqueue(b);
		else
		{
			if (b->getBusType() == MB)
				MixedBussesNotInStation.enqueue(b);
			else
				WheelBussesNotInStation.enqueue(b);
		}
	}
}

void Company::GenerateRandStation()
{
	int x;
	Station* dummyStation;
	for (int i = 1; i < NumberOfStations + 1; i++)
	{
		S.peek(dummyStation, i);
		Passenger* p = new Passenger();

		x = rand() % 100;
		if (x >= 1 && x <= 25)
		{
			if (dummyStation->RemoveNPSP(false, p))
				FinishedPassenger.InsertBeg(p);
		}
		else if (x >= 35 && x <= 45)
		{
			if (dummyStation->RemoveWP(p))
				FinishedPassenger.InsertBeg(p);
		}
		else if (x >= 50 && x <= 60)
		{
			if (dummyStation->RemoveNPSP(true, p))
				FinishedPassenger.InsertBeg(p);
		}
	}
}
void Company::CallUI(int& SID)
{
	if (SID > NumberOfStations)
		SID = 0;
	else if (SID < 0)
		SID = NumberOfStations;
	Station* stat;
	S.peek(stat, SID);
	Display.DisplayStation(SID, stat, TimeStep, FinishedPassenger, CheckUpBusses, MBUSCapacity, WBUSCapacity);
}
bool Company::EndCode()
{
	Station* dummyStation;
	for (int i = 0; i < NumberOfStations + 1; i++)
	{
		S.peek(dummyStation, i);
		if (!dummyStation->isEmptyStation())
			return false;
	}
	if (!MixedBussesNotInStation.isEmpty())
		return false;
	else if (!WheelBussesNotInStation.isEmpty())
		return false;
	else
		return true;
}
bool Company::Output()
{
	ofstream OutFile;
	OutFile.open("out.txt", ios::out);
	OutFile << "FT		ID		AT		WT		TT" << endl;
	TimeHM FT;
	int ID;
	TimeHM AT;
	TimeHM WT;
	TimeHM TT;

	int Ptype;

	int nNP = 0;
	int nSP = 0;
	int nWP = 0;

	TimeHM sumWT(0, 0, 0);
	TimeHM sumTT(0, 0, 0);
	float prompass = 0;

	int n = FinishedPassenger.CountList();

	for (int i = 0; i < n; i++)
	{
		FinishedPassenger.GetMinFT(FT, ID, AT, WT, Ptype);
		if (Ptype == NP || Ptype == PNP)
			nNP++;
		else if (Ptype == SPAged || Ptype == SPPod || Ptype == SPPW)
			nSP++;
		else if (Ptype == WP)
			nWP++;
		if (Ptype == PNP)
			prompass++;

		int HFT = FT.getHours();
		int MFT = FT.getMinutes();

		int HAT = AT.getHours();
		int MAT = AT.getMinutes();

		int HWT = WT.getHours();
		int MWT = WT.getMinutes();

		TimeHM MT = WT + AT;
		TimeHM TT = FT - MT;
		int HTT = TT.getHours();
		int MTT = TT.getMinutes();
		sumWT = sumWT + WT;
		sumTT = sumTT + TT;

		OutFile << HFT << ":" << MFT << "		" << ID << "		" << HAT << ":" << MAT << "		" << HWT << ":" << MWT;
		OutFile << "		" << HTT << ":" << MTT << endl;
	}
	OutFile << "...................................................." << endl;

	OutFile << "passengers:" << n << "	" << "[NP:" << nNP << ", SP:" << nSP << ", WP:" << nWP << "]" << endl;

	float SWT = sumWT.getHours() * 3600 + sumWT.getMinutes() * 60 + sumWT.getSeconds();
	float AVGWT = SWT / n;
	int HAWT = AVGWT / 3600;
	int MAWT = (AVGWT - HAWT * 3600) / 60;
	OutFile << "passenger Avg Wait Time=" << HAWT << ":" << MAWT << endl;

	float STT = sumTT.getHours() * 3600 + sumTT.getMinutes() * 60 + sumTT.getSeconds();
	float AVGTT = STT / n;
	int HATT = AVGTT / 3600;
	int MATT = (AVGTT - HATT * 3600) / 60;
	OutFile << "passenger Avg Trip Time=" << HATT << ":" << MATT << endl;

	float promper = prompass / n * 100;
	OutFile << "Auto-promoted passengers:" << promper << "%" << endl;
	OutFile << "buses:" << WBUS+MBUS << "	[WBus:" << WBUS << ", MBus:" << MBUS << "]" << endl;


	Station* s = nullptr;
	S.peek(s, 0);

	TimeHM sumBT(0, 0, 0);
	float sumU = 0;
	s->GetBUBT(sumU,sumBT,TimeStep,MBUSCapacity,WBUSCapacity);
	float SBT = sumBT.getHours() * 3600 + sumBT.getMinutes() * 60 + sumBT.getSeconds();
	float AVGBT = SBT / (WBUS + MBUS) * 100;
	OutFile << "Avg Busy time =" << AVGBT << " in seconds" << endl;

	float AVBU = sumU / (WBUS + MBUS) * 100;
	OutFile << "Avg Utilization =" << AVBU << "%" << endl;
	return true;
}

void Company::DisplayEnd()
{
	Display.END();
}