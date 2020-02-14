#include "lab2_drones_manager.hpp"
#include <iostream>

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() : first(NULL), last(NULL), size(0) {
}

DronesManager::~DronesManager() {
    DroneRecord* temp = first;
    while (temp!= NULL)
    {
        temp = temp->next;
        delete first;
        first = temp;
    }
    first = last = NULL;
    size = 0;
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    if (lhs.droneID == rhs.droneID && lhs.batteryType == rhs.batteryType && lhs.droneType == rhs.droneType
        && lhs.manufacturer == rhs.manufacturer && lhs.description == rhs.description && lhs.yearBought == rhs.yearBought
        && lhs.range == rhs.range)
            return true;
	return false;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	if (first != NULL)
        return false;
     else
        return true;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (empty())
        return DroneRecord();
    DroneRecord* cur = first;
    for (int i = 0; i < index; i++){
        if (!cur->next)
            return *cur;
        cur = cur->next;
    }
    return *cur;
}

unsigned int DronesManager::search(DroneRecord value) const {
	if (empty())
        return 0;
    DroneRecord* cur = first;
    for (int i = 0; cur; i++){
        if (*cur == value)
            return i;
        cur = cur->next;
    }
    return get_size();
}

void DronesManager::print() const {

    DroneRecord* cur = first;
    DroneRecord* next;
    while (cur != NULL)
    {
        //next = cur->next;
        cout << "droneID: " << cur->droneID
            << ", range: " << cur->range
            << ", yearBought: " << cur->yearBought
            << ", droneType: " << cur->droneType
            << ", manufacturer: " << cur->manufacturer
            << ", description: " << cur->description
            << ", batteryType: " << cur->batteryType
            << endl;
        cur = cur->next;
    }
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {

    if (index > size)
        return false;
    else if (size == 0)
    {
        first = &value;
        last = &value;
    }
    else if (index == 0)
    {
        DroneRecord* temp = first;
        first = &value;
        first->next = temp;
        temp->prev = first;
    }
    else if (index == size)
    {
        DroneRecord* temp = last;
        last = &value;
        last->prev = temp;
        temp->next = last;
    }
    else
    {
        DroneRecord* curr = first;
        DroneRecord* temp;
        for (int i = 0; i < index - 1; i++)
        {
            curr = curr->next;
        }
        temp = curr->next;
        curr->next = &value;
        temp->prev = &value;
        value.prev = curr;
        value.next = temp;
    }
    size++;
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    if (size == 0)
    {
        first = &value;
        last = &value;
    }
    else
    {
        DroneRecord* temp = first;
        first = &value;
        first->next = temp;
        temp->prev = first;
    }
    size++;
    return true;

}

bool DronesManager::insert_back(DroneRecord value) {
    if (size == 0)
    {
        first = &value;
        last = &value;
    }
    else
    {
        DroneRecord* temp = last;
        last = &value;
        last->prev = temp;
        temp->next = last;
    }
    size++;
	return true;
}

bool DronesManager::remove(unsigned int index) {
    if (size == 0 || index > size - 1)
        return false;
    else if (size == 1)
    {
        delete first;
        first = NULL;
        last = NULL;
    }
    else if (index == 0)
    {
        DroneRecord* temp = first->next;
        delete first;
        first = temp;
        temp->prev = NULL;
    }
    else if (index == size-1)
    {
        DroneRecord* temp = last->prev;
        delete last;
        last = temp;
        last->next = NULL;
    }
    else
    {
        DroneRecord* curr = first;
        DroneRecord* next;
        DroneRecord* prev;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        next = curr->next;
        prev = curr->prev;

        prev->next = next;
        next->prev = prev;

        delete curr;
    }
    size--;
    return true;

}

bool DronesManager::remove_front() {
    bool done = remove(0);
	return done;
}

bool DronesManager::remove_back() {
    bool done = remove(size-1);
	return done;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {

    DroneRecord* curr = first;
    DroneRecord* next;
    DroneRecord* prev;
    if (index > size - 1)
        return false;
    else if (size == 1)
    {
        first = &value;
        last = &value;
    }
    else if (index == 0)
    {
        next = first->next;
        first = &value;
        first->next = next;
        next->prev = first;
    }
    else if (index == size - 1)
    {
        prev = last->prev;
        last = &value;
        last->prev = prev;
        prev->next = last;
    }
    else
    {
        for (int i = 0; i < index; i++)
            curr = curr->next;
        next = curr->next;
        prev = curr->prev;

        curr = &value;

        curr->next = next;
        curr->prev = prev;

        next->prev = curr;
        prev->next = curr;

    }
	return false;
}

bool DronesManager::reverse_list() {
    DroneRecord* curr = first;
    DroneRecord* temp;
    if (size == 0)
    	return false;
    while (curr != NULL)
    {
    	temp = curr->prev;
    	curr->prev = curr->next;
    	curr->next = temp;
    	curr = curr->prev;
    }
    if (size > 1) // if list size is greater than one, swap first and last
    {
    	temp = first;
    	first = last;
    	last = temp;
    }
	return true;
}

