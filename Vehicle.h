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
	float actualSpeed;
	float radius = 20;
	Vector2f velocity;
	Vector2f desiredVelocity;
	Vector2f steeringForce;
	Vector2f target;
	float alignmentMult = 1, separationMult = 3, cohesionMult = .2;
	
public:
	Vehicle();
	Vehicle(Vector2f position);
	Vector2f getDirection();
	void setTarget(Vector2f t);
	void setDirection(Vector2f dir);
	void computeDesiredVelocity();
	void computeSteeringForce();
	void create();
	void draw();
	void update(float dt);
	void wrapAround();
	void Flock(vector<Vehicle*>* vehicles);
};