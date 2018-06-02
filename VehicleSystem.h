#pragma once
#include "Vehicle.h"

class VehicleSystem {
private:
	vector<Vehicle*> *vehicles;
	bool s, a, c;
	Text tSeparation, tAlignment, tCohesion;
	Font f;

public:
	VehicleSystem();
	~VehicleSystem();
	void addVehicle(Vector2f position);
	void removeVehicle();
	void createText(Vector2f position, Text &t);
	void update(float dt);
	void draw();
	void separation();
	void alignment();
	void cohesion();
};