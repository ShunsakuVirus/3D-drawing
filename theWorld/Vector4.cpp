#include"Matrix4x4.h"
#include<cmath>
Vector4::Vector4() {
	x = 0.0F;
	y = 0.0F;
	z = 0.0F;
	w = 1.0F;
}

Vector4::Vector4(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vector4 Vector4::operator + (Vector4 v) {
	return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}
Vector4 Vector4::operator - (Vector4 v) {
	return Vector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}
Vector4 Vector4::operator * (Matrix4x4 m) {
	float _x = this->x*m.a + this->y*m.e + this->z*m.i + this->w*m.m;
	float _y = this->x*m.b + this->y*m.f + this->z*m.j + this->w*m.n;
	float _z = this->x*m.c + this->y*m.g + this->z*m.k + this->w*m.o;
	float _w = this->x*m.d + this->y*m.h + this->z*m.l + this->w*m.p;
	return Vector4(_x, _y, _z, _w);
}

Vector3 Vector4::screenTransformation(Vector4 v,int width, int height) {
	Vector3 work;
	work = Vector3::Vector3(v.x / v.w, v.y / v.w, v.z / v.w);
	/*work.x = work.x*width / 2;
	work.y = work.y*height / 2;*/
	work.x = work.x*width;
	work.y = work.y*height;
	return work;
}


