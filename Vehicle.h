#pragma once
#include "Global.h"
#include "VectorMath.h"

class Vehicle {
private:
	ConvexShape vehicle;
	Vector2f position;
	Vector2f direction;
	float speed;
	float maxForce;
	float radius = 20;
	Vector2f velocity;
	Vector2f desiredVelocity;
	Vector2f steeringForce;
	Vector2f target;
	float alignmentMult = 1, separationMult = 1.5, cohesionMult = .2;
	
public:
	Vehicle();
	Vehicle(Vector2f position);
	void setTarget(Vector2f t);
	void setDirection(Vector2f dir);
	void seek(Vector2f t);
	void create();
	void draw();
	void update(float dt);
	void wrapAround();
	void Flock(vector<Vehicle*>* vehicles);
	bool alignmentB = false, separationB = false, cohesionB = false;
};