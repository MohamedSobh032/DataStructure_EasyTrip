#include "StationList.h"
#include <iostream>
void StationList::PrintAllStations() const
{
	cout << "\nprinting list contents:\n\n";
	Node<Station*>* p = Head;

	while (p)
	{
		cout << "[ " << p->getItem()->getStationID() << " ]";
		cout << "--->";
		p = p->getNext();
	}
	cout << "NULL\n";
}