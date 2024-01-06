#ifndef _DEFS_H_
#define _DEFS_H_
enum PassengerType {
	PNP,				// Promoted Normal Passenger
	SPAged,				// Special Categories Passenger
	SPPod,				// Special Categories POD
	SPPW,				// Special Categories Pregnant Woman
	NP,					// Normal Passenger
	WP					// Passenger with Wheelchair
};



enum BusType {
	MB,					// Mixed Bus
	WB					// Wheelchair Bus
};



enum DirectionType {
	FWD = 0,			// if bus is moving forward from station #0
	BWD = 1				// if bus is moving backwards from station #N
};


enum BusStatus {
	Working = 0,		//If bus is working
	Maintenance = 1,	//If bus is in maintenance mode
};

enum EventsType {
	Arriv = 0,
	Leav = 1
};

enum PassengerStatus {
	waiting = 0,
	Boarded = 1
};

enum Promotion {
	NotPromoted = 0,
	Promoted = 1
};

#endif