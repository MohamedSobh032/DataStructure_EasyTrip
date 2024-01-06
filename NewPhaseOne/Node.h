#ifndef _NODE_H_
#define _NODE_H_

template <typename T>
class Node
{
private:
	T item;
	Node<T>* next;
public:
	Node();
	Node(const T& r_item);
	Node(const T& r_item, Node<T>* nextNodePtr);

	void setItem(const T& r_item);
	void setNext(Node<T>* nextNodePtr);

	T getItem() const;
	Node<T>* getNext() const;
	//Copy Constructor
	Node(const Node<T>& r_node);
	//Assignment Operator
	Node<T>& operator=(const Node<T>& r_node);
};

template <typename T>
Node<T>::Node()
{
	next = nullptr;
}

template <typename T>
Node<T>::Node(const T& r_item)
{
	next = nullptr;
	item = r_item;
}

template <typename T>
Node<T>::Node(const T& r_item, Node<T>* nextNodePtr)
{
	item = r_item;
	next = nextNodePtr;
}

template <typename T>
void Node<T>::setItem(const T& r_item)
{
	item = r_item;
}

template <typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template <typename T>
T Node<T>::getItem() const
{
	return item;
}

template <typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

template <typename T>
Node<T>::Node(const Node<T>& r_Node)
{
	item = r_Node.item; next = r_Node.next;
}

template <typename T>
Node<T>& Node<T>::operator=(const Node<T>& r_Node)
{
	if (this != &r_Node) {
		item = r_Node.item; next = r_Node.next;
	}
	return *this;
}


#endif
