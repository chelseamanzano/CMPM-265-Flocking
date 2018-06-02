#include "VehicleSystem.h"

VehicleSystem::VehicleSystem() {
	vehicles = new vector<Vehicle*>();
}

VehicleSystem::~VehicleSystem() {
	for (int i = 0; i < vehicles->size(); i++) {
		delete vehicles->at(i);
	}
}

void VehicleSystem::addVehicle(Vector2f position) {
	vehicles->push_back(new Vehicle(position));
	vehicles->at(vehicles->size() - 1)->create();
}

void VehicleSystem::update(float dt) {
	for (int i = 0; i < vehicles->size(); i++) {
		vehicles->at(i)->Flock(vehicles);
		vehicles->at(i)->update(dt);
	}
}

void VehicleSystem::draw() {
	for (int i = 0; i < vehicles->size(); i++) {
		Vehicle* v = vehicles->at(i);
		v->draw();
	}
}