#include "VehicleSystem.h"

VehicleSystem::VehicleSystem() {

}

VehicleSystem::~VehicleSystem() {
	for (int i = 0; i < vehicles.size(); i++) {
		delete vehicles[i];
		vehicles[i] = nullptr;
	}
}

void VehicleSystem::addVehicle(Vector2f position) {
	
}

void VehicleSystem::update(float dt) {
	/*for (int i = 0; i < vehicles.size(); i++) {
		V
	}*/
}

void VehicleSystem::draw() {
	for (int i = 0; i < vehicles.size(); i++) {
		Vehicle* v = vehicles[i];
		v->draw();
	}
}