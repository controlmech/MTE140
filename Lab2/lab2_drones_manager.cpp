#include <iostream>
#include "lab2_drones_manager.hpp"
// Comment
// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
}

DronesManager::~DronesManager() {
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	return false;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	 if (first != nullptr)
        return true;
     else return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if (empty())
        return DroneRecord();
    DroneRecord* cur = first;
    for (int i = 0; i < index; i++){
        if (!cur->next)
            return cur;
        cur = cur->next;
    }
    return *cur;
}

unsigned int DronesManager::search(DroneRecord value) const {
    if (empty())
        return 0;
    DroneRecord* cur = first;
    for (int i = 0; cur; i++){
        if (*cur == this)
            return i;
        cur = cur->next;
    }
    return get_size();
}

void DronesManager::print() const {
    cout << "droneID: " << DroneRecord.droneID
        << ", range: " << DroneRecord.range
        << ", yearBought" << DroneRecord.yearBought
        << ", droneType: " << DroneRecord.droneType
        << ", manufacturer: " << DroneRecord.manufacturer
        << ", description: " << DroneRecord.description
        << ", batteryType: " << DroneRecord.batteryType
        << endl;
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	return false;
}

bool DronesManager::insert_front(DroneRecord value) {
	return false;
}

bool DronesManager::insert_back(DroneRecord value) {
	return false;
}

bool DronesManager::remove(unsigned int index) {
	return false;
}

bool DronesManager::remove_front() {
	return false;
}

bool DronesManager::remove_back() {
	return false;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	return false;
}

bool DronesManager::reverse_list() {
	return false;
}

