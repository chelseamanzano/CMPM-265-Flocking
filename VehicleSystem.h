#pragma once
#include "Global.h"
#include "Vehicle.h"

class VehicleSystem {
private:
	vector<Vehicle*> vehicles;

public:
	VehicleSystem();
	~VehicleSystem();
	void addVehicle(Vector2f position);
	void update(float dt);
	void draw();
};