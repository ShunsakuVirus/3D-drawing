#pragma once
#include "Vector3.h"
struct Matrix4x4 {
	float a, b, c, d;
	float e, f, g, h;
	float i, j, k, l;
	float m, n, o, p;

	Matrix4x4();

	Matrix4x4(float _a, float _b, float _c, float _d,
			float _e, float _f, float _g, float _h,
			float _i, float _j, float _k, float _l,
			float _m, float _n, float _o, float _p);

	void identity();

	static Matrix4x4 scaling(float x, float y, float z);
	
	static Matrix4x4 rotateX(float r);
	
	static Matrix4x4 rotateY(float r);
	
	static Matrix4x4 rotateZ(float r);
	
	static Matrix4x4 rotateDegX(float r);
	
	static Matrix4x4 rotateDegY(float r);
	
	static Matrix4x4 rotateDegZ(float r);
	
	static Matrix4x4 translate(float x, float y, float z);

	static Matrix4x4 Camera(Vector3 camera, Vector3 gazingPoint, Vector3 camUp);

};