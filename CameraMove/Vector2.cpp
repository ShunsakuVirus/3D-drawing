#include "Vector2.h"
#include <cmath>

Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float _x, float _y) {
	this->x = _x;
	this->y = _y;
}

Vector2 Vector2::operator + (Vector2 v) {
	return Vector2(this->x + v.x, this->y + v.y);
}
Vector2 Vector2::operator - (Vector2 v) {
	return Vector2(this->x - v.x, this->y - v.y);
}
Vector2 Vector2::operator * (Vector2 v) {
	return Vector2(this->x*v.x, this->y*v.y);
}
Vector2 Vector2::operator / (Vector2 v) {
	return Vector2(this->x/v.x, this->y/v.y);
}

Vector2 Vector2::operator* (float f) {
	return Vector2(this->x*f, this->y*f);
}

float Vector2::cross(Vector2 v1, Vector2 v2) {
	return v1.x*v2.y - v1.y*v2.x;
}

float Vector2::dot(Vector2 v1, Vector2 v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

Vector2 Vector2::nornalized() {
	float s = (float)sqrt(this->x*this->x+this->y*this->y);
	return Vector2(this->x / s, this->y / s);
}