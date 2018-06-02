#include "Vehicle.h"

Vehicle::Vehicle() {

}

Vehicle::Vehicle(Vector2f position) {
	this->position = position;
	float x = -1 + (rand() / (RAND_MAX / (1 + 1)));
	float y = -1 + (rand() / (RAND_MAX / (1 + 1)));
	direction = Vector2f(x, y);
	speed = 200;
	velocity = speed * direction;
	maxForce = 50;
	steeringForce = Vector2f(0, 0);
	x = (rand() / (RAND_MAX / SCREEN_WIDTH));
	x = (rand() / (RAND_MAX / SCREEN_HEIGHT));
	target = Vector2f(x, y);
}

void Vehicle::create() {
	vehicle.setPointCount(3);
	vehicle.setPoint(0, Vector2f(0, 0));
	vehicle.setPoint(1, Vector2f(-15, 5));
	vehicle.setPoint(2, Vector2f(-15, -5));
	vehicle.setFillColor(Color::Black);
	vehicle.setOutlineColor(Color::White);
	vehicle.setOutlineThickness(2);
	vehicle.setPosition(position);
	vehicle.setOrigin(-7.5, 0);
}

void Vehicle::update(float dt) {
	wrapAround();
	velocity += steeringForce * dt;
	vehicle.setPosition(vehicle.getPosition() + (velocity * dt));
	vehicle.setRotation(convertVector(velocity));
	position = vehicle.getPosition();
	steeringForce *= 0.f;
}

void Vehicle::draw() {
	window.draw(vehicle);
}

void Vehicle::wrapAround() {
	if (vehicle.getPosition().x + 7.5 < 0) {
		vehicle.setPosition(Vector2f(SCREEN_WIDTH + 7.5, vehicle.getPosition().y));
	}

	if (vehicle.getPosition().x - 7.5 > SCREEN_WIDTH) {
		vehicle.setPosition(Vector2f(-7.5, vehicle.getPosition().y));
	}

	if (vehicle.getPosition().y + 5 < 0) {
		vehicle.setPosition(Vector2f(vehicle.getPosition().x, SCREEN_HEIGHT + 5));
	}

	if (vehicle.getPosition().y - 5 > SCREEN_HEIGHT) {
		vehicle.setPosition(Vector2f(vehicle.getPosition().x, -5));
	}
}

void Vehicle::setDirection(Vector2f dir) {
	direction = dir;
}

void Vehicle::seek(Vector2f t) {
	desiredVelocity = t - position;
	desiredVelocity = normalize(desiredVelocity) *  speed;
	steeringForce += (desiredVelocity - velocity) * cohesionMult;
}


void Vehicle::setTarget(Vector2f t) {
	target = t;
}

void Vehicle::Flock(vector<Vehicle*>* vehicles) {
	Vector2f alignmentSum = Vector2f(0,0);
	Vector2f cohesionSum = Vector2f(0, 0);
	Vector2f separationSum = Vector2f(0, 0);
	int count = 0;
	float neighborDistance = 150;
	float desiredSeparation = 75;
	bool separation = false;

	for (int i = 0; i < vehicles->size(); i++) {
		float distance = magnitude(vehicles->at(i)->position - vehicle.getPosition());

		if (distance > 0 && distance < neighborDistance) {
			alignmentSum += vehicles->at(i)->velocity;
			cohesionSum += vehicles->at(i)->position;
			count++;
		}
		if (distance > 0 && distance < desiredSeparation) {
			separation = true;
			separationSum += normalize(vehicle.getPosition() - vehicles->at(i)->position) / distance;
		}
	}

	//Alignment
	if (alignmentB) {
		if (count > 0) {
			alignmentSum = normalize(alignmentSum, magnitude(alignmentSum))*speed;
			Vector2f steer = normalize(alignmentSum - velocity) * maxForce;
			steeringForce += steer*alignmentMult;
		}
	}

	//Cohesion
	if (cohesionB) {
		if (count > 0) {
			cohesionSum /= (float)count;
			setTarget(cohesionSum);
			seek(target);
		}
	}

	//Separation
	if (separationB) {
		if (separation) {
			separationSum = normalize(separationSum, magnitude(separationSum))*speed;
			Vector2f steer = normalize(separationSum - velocity) * maxForce;
			steeringForce += steer*separationMult;
		}
	}

}