#ifndef _PRIO_NODE_H_
#define _PRIO_NODE_H_
template <typename T>
class PrioNode
{
private:
	int P;
	T item;
	PrioNode<T>* next;
public:
	PrioNode();
	PrioNode(const int& r_Prio);
	PrioNode(const int& r_Prio, const T& r_item);
	PrioNode(const int& r_Prio, const T& r_item, PrioNode<T>* nextNodePtr);

	void setPrio(const int& r_Prio);
	void setItem(const T& r_item);
	void setNext(PrioNode<T>* nextNodePtr);

	int getPrio() const;
	T getItem() const;
	PrioNode<T>* getNext() const;
	//Copy Constructor
	PrioNode(const PrioNode<T>& r_node);
	//Assignment Operator
	PrioNode<T>& operator=(const PrioNode<T>& r_node);
};
template <typename T>
PrioNode<T>::PrioNode()
{
	next = nullptr;
}
template <typename T>
PrioNode<T>::PrioNode(const int& r_Prio)
{
	P = r_Prio;
	next = nullptr;
}
template <typename T>
PrioNode<T>::PrioNode(const int& r_Prio, const T& r_item)
{
	P = r_Prio;
	item = r_item;
	next = nullptr;
}
template <typename T>
PrioNode<T>::PrioNode(const int& r_Prio, const T& r_item, PrioNode<T>* nextNodePtr)
{
	P = r_Prio;
	item = r_item;
	next = nextNodePtr;
}



template <typename T>
void PrioNode<T>::setPrio(const int& r_Prio)
{
	P = r_Prio;
}
template <typename T>
void PrioNode<T>::setItem(const T& r_item)
{
	item = r_item;
}
template <typename T>
void PrioNode<T>::setNext(PrioNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template<typename T>
int PrioNode<T>::getPrio() const
{
	return P;
}
template <typename T>
T PrioNode<T>::getItem() const
{
	return item;
}

template <typename T>
PrioNode<T>* PrioNode<T>::getNext() const
{
	return next;
}

template <typename T>
PrioNode<T>::PrioNode(const PrioNode<T>& r_Node)
{
	item = r_Node.item; next = r_Node.next;

}

template <typename T>
PrioNode<T>& PrioNode<T>::operator=(const PrioNode<T>& r_Node)
{
	if (this != &r_Node) {
		item = r_Node.item; next = r_Node.next;
	}
	return *this;
}
#endif