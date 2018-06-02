#include "VehicleSystem.h"

VehicleSystem::VehicleSystem() {
	vehicles = new vector<Vehicle*>();
	f.loadFromFile("arial.ttf");
	createText(Vector2f(10, 550), tAlignment);
	createText(Vector2f(210, 550), tSeparation);
	createText(Vector2f(410, 550), tCohesion);
	tAlignment.setString("Alignment OFF");
	tSeparation.setString("Separation OFF");
	tCohesion.setString("Cohesion OFF");
}

VehicleSystem::~VehicleSystem() {
	for (int i = 0; i < vehicles->size(); i++) {
		delete vehicles->at(i);
	}
}

void VehicleSystem::addVehicle(Vector2f position) {
	vehicles->push_back(new Vehicle(position));
	vehicles->at(vehicles->size() - 1)->create();
	if (a)
		vehicles->at(vehicles->size() - 1)->alignmentB = true;
	if (s)
		vehicles->at(vehicles->size() - 1)->separationB = true;
	if (c)
		vehicles->at(vehicles->size() - 1)->cohesionB = true;
}

void VehicleSystem::removeVehicle() {
	vehicles->erase(vehicles->begin() + (vehicles->size() - 1));
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
	window.draw(tAlignment);
	window.draw(tSeparation);
	window.draw(tCohesion);
}

void VehicleSystem::separation() {
	for (int i = 0; i < vehicles->size(); i++) {
		Vehicle* v = vehicles->at(i);
		if (!v->separationB) {
			s = true;
			v->separationB = true;
			tSeparation.setString("Separation ON");
		}
		else {
			s = false;
			v->separationB = false;
			tSeparation.setString("Separation OFF");
		}
	}
}

void VehicleSystem::alignment() {
	for (int i = 0; i < vehicles->size(); i++) {
		Vehicle* v = vehicles->at(i);
		if (!v->alignmentB) {
			a = true;
			v->alignmentB = true;
			tAlignment.setString("Alignment ON");
		}
		else {
			a = false;
			v->alignmentB = false;
			tAlignment.setString("Alignment OFF");
		}
	}
}

void VehicleSystem::cohesion() {
	for (int i = 0; i < vehicles->size(); i++) {
		Vehicle* v = vehicles->at(i);
		if (!v->cohesionB) {
			c = true;
			v->cohesionB = true;
			tCohesion.setString("Cohesion ON");
		}
		else {
			c = false;
			v->cohesionB = false;
			tCohesion.setString("Cohesion OFF");
		}
	}
}

void VehicleSystem::createText(Vector2f position, Text &t) {
	t.setCharacterSize(25);
	t.setFont(f);
	t.setPosition(position);
	t.setFillColor(Color::White);
	t.setString("");
}