#include "Vehicle.h"

Vehicle::Vehicle() {

}

Vehicle::Vehicle(Vector2f position) {
	this->position = position;
	direction = Vector2f(0, -1);
	speed = 250;
	actualSpeed = speed;
	velocity = speed * direction;
	maxForce = 50;
	steeringForce = Vector2f(0, 0);
	target = Vector2f(0, 0);
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
	float distance = magnitude(vectorSubtract(vehicle.getPosition(), target));
	if ( distance < radius) {
		actualSpeed = distance / radius * speed;
	}
	else {
		actualSpeed = speed;
	}
	computeDesiredVelocity();
	computeSteeringForce();
	velocity += steeringForce * dt;
	vehicle.setPosition(vehicle.getPosition() + (velocity * dt));
	vehicle.setRotation(convertVector(velocity));
}

void Vehicle::draw() {
	window.draw(vehicle);
}

void Vehicle::wrapAround() {
	if (vehicle.getPosition().x + 5 < 0) {
		vehicle.setPosition(Vector2f(SCREEN_WIDTH + 5, vehicle.getPosition().y));
	}

	if (vehicle.getPosition().x - 5 > SCREEN_WIDTH) {
		vehicle.setPosition(Vector2f(-5, vehicle.getPosition().y));
	}

	if (vehicle.getPosition().y + 5 < 0) {
		vehicle.setPosition(Vector2f(vehicle.getPosition().x, SCREEN_HEIGHT + 5));
	}

	if (vehicle.getPosition().y - 5 > SCREEN_HEIGHT) {
		vehicle.setPosition(Vector2f(vehicle.getPosition().x, -5));
	}
}

Vector2f Vehicle::getDirection() {
	float rotation = ((vehicle.getRotation() - 90) * M_PI) / 180;
	return Vector2f(cosf(rotation), sinf(rotation));
}

void Vehicle::setDirection(Vector2f dir) {
	direction = dir;
}

void Vehicle::computeDesiredVelocity() {
	Vector2f dir = vectorSubtract(target, vehicle.getPosition());
	float mag = magnitude(dir);
	Vector2f normalizedDir = normalize(dir, mag);
	desiredVelocity = normalizedDir * actualSpeed;
}

void Vehicle::computeSteeringForce() {
	steeringForce = desiredVelocity - velocity;
}

void Vehicle::setTarget(Vector2f t) {
	target = t;
}