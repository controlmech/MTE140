#include "lab3_priority_queue.hpp"
#include <iostream>

using namespace std;

// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    heap = new TaskItem*[n_capacity+1];
    capacity = n_capacity;
    size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
    for (int i = 0; i < size; i++)
    {
        delete heap[i];
        heap[i] = NULL;
    }
    delete [] heap;
    heap = NULL;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	return (size == 0);
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	return (size == capacity);
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    for (int i = 1; i <= size; i++)
    {
        cout << heap[i]->priority << " ";
    }
    cout << endl;
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if (heap[1] == NULL)
        return TaskItem(-1, "N/A");
    else
        return *(heap[1]);
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
    if (size == 0)
        heap[1] = new TaskItem(val);
    else if (size == capacity)
        return false;
	else
	{
	    int i = size + 1;
	    heap[i] = new TaskItem(val);
	    while (i > 1 && heap[i/2]->priority < heap[i]->priority)
        {
            TaskItem* temp = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = temp;
            i /= 2;
        }
	}
	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if (size == 0)
        return false;
    else if (size == 1)
    {
        heap[1] = NULL;
    }
    else
    {
        heap[1] = heap[size];
        heap[size] = NULL;
        int i = 1;
        int newSize = size-1;
        while (i*2 <= newSize)
        {
            TaskItem* temp;
            int newI;
            if (heap[i*2+1] == NULL && heap[i*2]->priority > heap[i]->priority)
            {
                temp = heap[i*2];
                heap[i*2] = heap[i];
                heap[i] = temp;
                newI = i*2;
            }
            else if (heap[i*2+1] == NULL)
            {
                // makes sure that if heap[i*2+1] is NULL, heap[i*2+1] isn't checked in the other if statements
                newI = newSize;
            }
            else if ((heap[i*2]->priority > heap[i]->priority && heap[i*2]->priority > heap[i*2+1]->priority))
            {
                temp = heap[i*2];
                heap[i*2] = heap[i];
                heap[i] = temp;
                newI = i*2;
            }
            else if (heap[i*2+1]->priority > heap[i]->priority && heap[i*2+1]->priority > heap[i*2]->priority)
            {
                temp = heap[i*2+1];
                heap[i*2+1] = heap[i];
                heap[i] = temp;
                newI = i*2+1;
            }
            else
            {
                // if none of the above cases, set newI to be newSize so it exits loop
                newI = newSize;
            }
            i = newI;
        }
    }
    size--;
	return true;
}



