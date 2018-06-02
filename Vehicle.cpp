#include "Vehicle.h"

Vehicle::Vehicle() {

}

Vehicle::Vehicle(Vector2f position) {
	this->position = position;
	direction = Vector2f(0, -1);
	speed = 200;
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
	//computeSteeringForce();
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
	steeringForce += normalizedDir * cohesionMult;
}

void Vehicle::computeSteeringForce() {
	steeringForce = desiredVelocity - velocity;
}

void Vehicle::setTarget(Vector2f t) {
	target = t;
}

void Vehicle::Flock(vector<Vehicle*>* vehicles) {
	Vector2f alignmentSum = Vector2f(0,0);
	Vector2f cohesionSum = Vector2f(0, 0);
	Vector2f separationSum = Vector2f(0, 0);
	int count = 0;
	float neighborDistance = 40;
	float desiredSeparation = 20;
	bool separation = false;

	for (int i = 0; i < vehicles->size(); i++) {
		float distance = magnitude(vehicles->at(i)->position - vehicle.getPosition());

		if (distance > 0 && distance < neighborDistance) {
			alignmentSum += vehicles->at(i)->velocity;
			cohesionSum += vehicles->at(i)->position;
			
			count++;
		}
		if (distance > 0 && distance < desiredSeparation) {
			//separationSum += normalize(vehicles->at(i)->position - vehicle.getPosition(), magnitude(vehicles->at(i)->position - vehicle.getPosition()));
			separation = true;
			separationSum += normalize(vehicle.getPosition() - vehicles->at(i)->position) / distance;
			
		}
		
	}

	//Alignment
	if (count > 0) {
		alignmentSum = normalize(alignmentSum, magnitude(alignmentSum))*speed;
		Vector2f steer = normalize(alignmentSum - velocity) * maxForce;
		steeringForce += steer*alignmentMult;
	}

	//Cohesion
	if (count > 0) {
		cohesionSum /= (float)count;
		setTarget(cohesionSum);
	}

	//Separation
	if (separation) {
		separationSum = normalize(separationSum, magnitude(separationSum))*speed;
		Vector2f steer = normalize(separationSum - velocity) * maxForce;
		steeringForce += steer*separationMult;
	}

}