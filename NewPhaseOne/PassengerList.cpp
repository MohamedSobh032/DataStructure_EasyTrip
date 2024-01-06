#include "PassengerList.h"


bool PassengerList::PeekID(int& D, int ID)
{
	if (Head == nullptr)
		return false;
	int iterator = 0;
	Node<Passenger*>* P = Head;
	while (P->getNext() != nullptr)
	{
		if (iterator == ID)
			break;
		P = P->getNext();
		iterator++;
	}
	if (iterator != ID)
		return false;
	D = P->getItem()->getPassengerID();
	return true;
}


void PassengerList::GetMinFT(TimeHM& FT, int& ID, TimeHM& AT, TimeHM& WT, int& Ptype)
{
	Node<Passenger*>* Fp = Head;
	Passenger* P = Fp->getItem();
	Node<Passenger*>* Fp1 = Fp->getNext();
	while (Fp1)
	{
		Passenger* P1 = Fp1->getItem();
		if (P1->getFT() > P->getFT())
			Fp = Fp1;
		Fp1 = Fp1->getNext();
	}
	FT = P->getFT();
	ID = P->getPassengerID();
	AT = P->getAT();
	WT = P->getWT();
	Ptype = P->getPassengerType();
	DeleteNode(P);
	return;
}