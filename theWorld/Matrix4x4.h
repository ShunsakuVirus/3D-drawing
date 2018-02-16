#pragma once
#include "Vector3.h"
#include "Vector4.h"
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

	/*static Matrix4x4 camera(Vector3 cameraPos, Vector3 gazingPoint, Vector3 camUp);

	static Matrix4x4 perspective(float fieldOfView, float width, float height, float clippingNear, float clippingFar);*/

	static Matrix4x4 inverse(Matrix4x4 mat);
};

struct Camera {
	float x;
	float y;
	float z;
	Vector3 forward;
	Vector3 right;
	Vector3 up;
	Matrix4x4 viewMat;
	Matrix4x4 projMat;
	Matrix4x4 vPortMat;

	Camera();

	void cameraMatrix(Vector3 cameraPos, Vector3 gazingPoint, Vector3 camUp);

	void projection(float fieldOfView, float width, float height, float clippingNear, float clippingFar);

	void viewPort();

	Vector3 screenToWorldPoint(Vector3 position);

	Vector3 worldToScreenPoint(Vector3 position);
};