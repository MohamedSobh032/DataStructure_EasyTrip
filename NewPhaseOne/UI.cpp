#include "DEFS.h"
#include "Station.h"
#include "UI.h"
#include <iostream>


UI::UI()
{

}
void UI::DisplayStation(int SID, Station* DummyStation, const TimeHM& CurrentTime, PassengerList& FP, BusQueue BUC, int MBusCapacity, int WBusCapacity)
{

	int dummyprio = 0;
	int index = 0;
	int ID = 0;
	int SizeSP = DummyStation->CountSizeSP();
	int SizeWP = DummyStation->CountSizeWP();
	int SizeNP = DummyStation->CountSizeNP();


	std::cout << "\033[2J\033[1;1H";
	std::cout << "Current Time (Hour:Min)==> " << CurrentTime.getHours() << ":" << CurrentTime.getMinutes() << std::endl;
	std::cout << "=============================      Station #" << SID << "      =============================" << std::endl;

	std::cout << SizeSP << " Waiting SP: FWD[";

	while (DummyStation->PeekSPNPFWD(ID, dummyprio, index))
	{
		if (dummyprio != NP && dummyprio != PNP)
		{
			std::cout << ID << "(";
			if (dummyprio == SPAged)
				std::cout << "Ag)";
			else if (dummyprio == SPPod)
				std::cout << "PD)";
			else
				std::cout << "PREG)";
			index++;
			if (dummyprio != NP && dummyprio != PNP && DummyStation->PeekSPNPFWD(ID, dummyprio, index) && dummyprio != NP && dummyprio != PNP)
			{
				std::cout << " ";
			}
		}
		index++;
	}
	index = 0;
	std::cout << "] BCK[";
	while (DummyStation->PeekSPNPBWD(ID, dummyprio, index))
	{
		if (dummyprio != NP && dummyprio != PNP)
		{
			std::cout << ID << "(";
			if (dummyprio == SPAged)
				std::cout << "Ag)";
			else if (dummyprio == SPPod)
				std::cout << "PD)";
			else
				std::cout << "PREG)";
			if (dummyprio != NP && dummyprio != PNP && DummyStation->PeekSPNPBWD(ID, dummyprio, index) && dummyprio != NP && dummyprio != PNP)
			{
				std::cout << " ";
			}
		}
		index++;
	}
	index = 0;
	std::cout << "]" << std::endl << SizeWP << " Waiting WP: FWD[";
	while (DummyStation->PeekWheelFWD(ID, index))
	{
		std::cout << ID;
		index++;
		if (DummyStation->PeekWheelFWD(ID, index))
			std::cout << " ";
	}
	index = 0;
	std::cout << "] BCK[";
	while (DummyStation->PeekWheelBWD(ID, index))
	{
		std::cout << ID;
		index++;
		if (DummyStation->PeekWheelBWD(ID, index))
			std::cout << " ";
	}
	index = 0;
	std::cout << "]" << std::endl << SizeNP << " Waiting NP: FWD[";
	while (DummyStation->PeekSPNPFWD(ID, dummyprio, index))
	{
		if (dummyprio == NP || dummyprio == PNP)
			std::cout << ID;
		index++;
		if ((dummyprio == NP || dummyprio == PNP) && DummyStation->PeekSPNPFWD(ID, dummyprio, index) && (dummyprio == NP || dummyprio == PNP) )
			std::cout << " ";
	}
	index = 0;
	std::cout << "] BCK[";
	while (DummyStation->PeekSPNPBWD(ID, dummyprio, index))
	{
		if (dummyprio == NP || dummyprio == PNP)
			std::cout << ID;
		index++;
		if ((dummyprio == NP || dummyprio == PNP) && DummyStation->PeekSPNPBWD(ID, dummyprio, index) && (dummyprio == NP || dummyprio == PNP))
			std::cout << " ";
	}
	std::cout << "]" << std::endl;


	int FWDMB = DummyStation->CountMBBusFWD();
	int FWDWB = DummyStation->CountWBBusFWD();
	int BWDMB = DummyStation->CountMBBusBWD();
	int BWDWB = DummyStation->CountWBBusBWD();

	int TotalBusses = FWDMB + FWDWB + BWDMB + BWDWB;
	int BusID = 0;
	bool BusType = 0;
	int PassID = 0;
	int CurrentCapacity = 0;
	std::cout << TotalBusses << " Buses at this station:" << std::endl;
	for (int i = 0; i < FWDMB+FWDWB; i++)
	{
		DummyStation->PeekFWDBus(BusID, BusType, CurrentCapacity, MBusCapacity,i);
		if (BusType == MB)
		{
			std::cout << "B" << BusID << "[FWD, MBUS, " << CurrentCapacity << "] {";
			for (int j = 0; j < DummyStation->CountPassengerOnBusFWD(i); j++)
			{
				if (DummyStation->PeekPassengerOnBusFWD(i, PassID, j))
					cout << PassID;
				if (DummyStation->PeekPassengerOnBusFWD(i, BusID, j + 1))
					cout << ", ";
			}
			cout << "}" << endl;
		}
	}

	for (int i = 0; i < FWDWB+FWDMB; i++)
	{
		DummyStation->PeekFWDBus(BusID, BusType, CurrentCapacity, WBusCapacity, i);
		if (BusType == WB)
		{
			std::cout << "B" << BusID << "[FWD, WBUS, " << CurrentCapacity << "] {";
			for (int j = 0; j < DummyStation->CountPassengerOnBusFWD(i); j++)
			{
				if (DummyStation->PeekPassengerOnBusFWD(i, PassID, j))
					cout << PassID;
				if (DummyStation->PeekPassengerOnBusFWD(i, BusID, j + 1))
					cout << ", ";
			}
			cout << "}" << endl;
		}
	}

	for (int i = 0; i < BWDMB+BWDWB; i++)
	{
		DummyStation->PeekBWDBus(BusID, BusType, CurrentCapacity, MBusCapacity, i);
		if (BusType == MB)
		{
			std::cout << "B" << BusID << "[BWD, MBUS, " << CurrentCapacity << "] {";
			for (int j = 0; j < DummyStation->CountPassengerOnBusBWD(i); j++)
			{
				if (DummyStation->PeekPassengerOnBusBWD(i, PassID, j))
					cout << PassID;
				if (DummyStation->PeekPassengerOnBusBWD(i, BusID, j + 1))
					cout << ", ";
			}
			cout << "}" << endl;
		}
	}

	for (int i = 0; i < BWDWB+BWDMB; i++)
	{
		DummyStation->PeekBWDBus(BusID, BusType, CurrentCapacity, WBusCapacity,i);
		if (BusType == WB)
		{
			std::cout << "B" << BusID << "[BWD, WBUS, " << CurrentCapacity << "] {";
			for (int j = 0; j < DummyStation->CountPassengerOnBusBWD(i); j++)
			{
				if (DummyStation->PeekPassengerOnBusBWD(i, PassID, j))
					cout << PassID;
				if (DummyStation->PeekPassengerOnBusBWD(i, BusID, j + 1))
					cout << ", ";
			}
			cout << "}" << endl;
		}
	}	
	std::cout << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << BUC.getCount() << " In-Checkup buses: ";
	Bus* dummybus = nullptr;
	for (int i = 0; i < BUC.getCount(); i++)
	{
		BUC.dequeue(dummybus);
		cout << dummybus->getBusID() << ", ";
		BUC.enqueue(dummybus);
	}
	std::cout << std::endl << "--------------------------------------------------------------------------------" << std::endl;
	std::cout << FP.CountList() << " finished passengers: ";
	index = 0;
	while (FP.PeekID(ID, index)) {
		std::cout << ID;
		index++;
		if (FP.PeekID(ID, index))
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "Press 'A' to display increment the TimeStep | 'S' to display next station | 'S' to display previous station: ";
}


void UI::END()
{
	std::cout << "Silent Mode" << std::endl;
	std::cout << "Simulation Starts..." << std::endl;
	std::cout << "Simulation ends, Output file created" << std::endl;
}
