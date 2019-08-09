#include <cstring>
#include <iostream>
#include "CircularQueue.hpp"
using namespace std;


typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = nullptr;

CircularQueue::CircularQueue()
{
	head_ = 0;
	tail_ = 1;
	capacity_= 32;
	size_= 0;
	items_ = new QueueItem[capacity_];
}

CircularQueue::CircularQueue(unsigned int capacity)
{
	if(capacity==0)
	{
		head_ = 0;
		tail_ = 1;
		capacity_= 16;
		size_= 0;
		items_ = new QueueItem[capacity_];
	}
	else
	{
		head_ = 0;
		tail_ = 1;
		capacity_= capacity;
		size_= 0;
		items_ = new QueueItem[capacity_];
	}
}

CircularQueue::~CircularQueue()
{
	delete [] items_;
}

bool CircularQueue::empty() const
{
	if(size_ == 0)
		return true;
	return false;
}

bool CircularQueue::full() const
{
	if(size_==capacity_)
		return true;
	return false;
}

int CircularQueue::size() const
{
	return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
	if(empty()){
		items_[0] = value;
		size_ ++;
		return true;
	}
	else if(!full()){
		items_[tail_] = value;
		tail_ = (tail_+1)%capacity_;
		size_ ++;
		return true;
	}
	else
		return false;
}

QueueItem CircularQueue::dequeue()
{
	if(!empty()){
		QueueItem temp = items_[head_];
		head_ = (head_+1)%capacity_;
		size_--;
		return temp;
	}
	else{
		return EMPTY_QUEUE;
	}
}

QueueItem CircularQueue::peek() const
{
	if(!empty())
		return items_[head_];
	else
		return EMPTY_QUEUE;
}

void CircularQueue::print() const
{
	for(int i=0; i>capacity_; i++)
		cout<< items_[i]<<endl;
}
