#include"Vector3.h"
#include"Matrix4x4.h"
#include"Vector4.h"
#include<cmath>
Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vector3 Vector3::operator + (Vector3 v) {
	return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}
Vector3 Vector3::operator - (Vector3 v) {
	return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}
Vector3 Vector3::operator * (Vector3 v) {
	return Vector3(this->x*v.x, this->y*v.y, this->z*v.z);
}
Vector3 Vector3::operator/ (Vector3 v) {
	return Vector3(this->x/v.x, this->y/v.y, this->z/v.z);
}

Vector3 Vector3::operator* (float f) {
	return Vector3(this->x*f, this->y*f, this->z*f);
}
Vector3 Vector3::operator/(float f) {
	return Vector3(this->x/f, this->y/f, this->z/f);
}

Vector3 Vector3::cross(Vector3 v1, Vector3 v2) {
	float _x = v1.y*v2.z - v1.z*v2.y;
	float _y = v1.z*v2.x - v1.x*v2.z;
	float _z = v1.x*v2.y - v1.y*v2.x;
	return Vector3(_x, _y, _z);
}
float Vector3::dot(Vector3 v1, Vector3 v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector3 Vector3::normalized() {
	float s = (float)sqrt(this->x*this->x+this->y*this->y+this->z*this->z);
	this->x = this->x / s;
	this->y = this->y / s;
	this->z = this->z / s;
	return Vector3(this->x, this->y, this->z);
}

