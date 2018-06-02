#include "VectorMath.h"

float magnitude(Vector2f v) {
	float m = sqrtf(pow(v.x, 2) + pow(v.y, 2));
	return m;
}

Vector2f normalize(Vector2f v, float magnitude) {
	return v/magnitude;
}

Vector2f normalize(Vector2f v) {
	return v / magnitude(v);
}

Vector2f vectorSubtract(Vector2f a, Vector2f b) {
	return a - b;
}

float convertVector(Vector2f v) {
	Vector2f normalizedDir = normalize(v, magnitude(v));
	return atan2(normalizedDir.y, normalizedDir.x) * 180 / M_PI;
}