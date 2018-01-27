#include"Vector3.h"
#include"Matrix4x4.h"
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
Vector3 Vector3::operator * (Matrix4x4 m) {
	float _x = this->x*m.a + this->y*m.e + this->z*m.i + m.m;
	float _y = this->x*m.b + this->y*m.f + this->z*m.j + m.n;
	float _z = this->x*m.c + this->y*m.g + this->z*m.k + m.o;
	return Vector3(_x, _y, _z);
}

Vector3 Vector3::Cross(Vector3 v1, Vector3 v2) {
	float _x = v1.y*v2.z - v1.z*v2.y;
	float _y = v1.z*v2.x - v1.x*v2.z;
	float _z = v1.x*v2.y - v1.y*v2.x;
	return Vector3(_x, _y, _z);
}
float Vector3::Dot(Vector3 v1, Vector3 v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector3 Vector3::normalize(Vector3 v) {
	float s = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	v.x = v.x / s;
	v.y = v.y / s;
	v.z = v.z / s;
	return v;
}

