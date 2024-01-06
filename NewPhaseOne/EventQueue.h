#ifndef _EVENT_QUEUE_H_
#define _EVENT_QUEUE_H_
#include "LinkedQueue.h"
#include "Event.h"
class EventQueue : public LinkedQueue<Event*>
{
};
#endif

