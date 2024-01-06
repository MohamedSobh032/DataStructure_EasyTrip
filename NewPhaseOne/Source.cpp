#include <iostream>
using namespace std;
#include "Company.h"
#include "DEFS.h"
#include "Passenger.h"
#include "TimeHM.h"
#include "LinkedQueue.h"
#include "LinkedList.h"
#include "LinkedPrioQueue.h"
#include "PassengerQueue.h"
#include "PassengerPrioQueue.h"
#include "Bus.h"
#include "Station.h"
#include "Event.h"
#include "Arrival.h"
#include "Leave.h"

int main()
{

	char readed;
	Company C;
	C.FileLoader("random_file1.txt");
	C.InitializeStations();
	C.InitializeBusses();
	int StationID = 0;

	C.CallUI(StationID);

	while (1)
	{
		if (!C.CallEvent())
			break;
		cin >> readed;
		if (readed == 'a' || readed == 'A')
			C.IncrementTimeStep();
		else if (readed == 's' || readed == 'S')
		{
			StationID++;
			//Change UI to another Station
		}
		else if (readed == 'd' || readed == 'D')
		{
			StationID--;
			//Change UI to another Station
		}
		C.CallUI(StationID);
	}


	while (1)
	{
		if (C.EndCode())
			break;
		C.CallUI(StationID);
		cin >> readed;
		if (readed == 'a' || readed == 'A')
			C.IncrementTimeStep();
		else if (readed == 's' || readed == 'S')
		{
			StationID++;
			//Change UI to another Station
		}
		else if (readed == 'd' || readed == 'D')
		{
			StationID--;
			//Change UI to another Station
		}
		C.CallUI(StationID);
	}

	C.Output();
	
	
	cout << endl << "Hello World!" << endl;
	return 0;
}