#include"Matrix4x4.h"
#include<cmath>
#include"myMath.h"
	Matrix4x4::Matrix4x4() {
		identity();
	}

	Matrix4x4::Matrix4x4(float _a,float _b,float _c,float _d,
						float _e, float _f, float _g, float _h, 
						float _i, float _j, float _k, float _l, 
						float _m, float _n, float _o, float _p) {
		this->a = _a; this->b = _b; this->c = _c; this->d = _d;
		this->e = _e; this->f = _f; this->g = _g; this->h = _h;
		this->i = _i; this->j = _j; this->k = _k; this->l = _l;
		this->m = _m; this->n = _n; this->o = _o; this->p = _p;
	}

	void Matrix4x4::identity() {
		a = 1; b = 0; c = 0; d = 0;
		e = 0; f = 1; g = 0; h = 0;
		i = 0; j = 0; k = 1; l = 0;
		m = 0; n = 0; o = 0; p = 1;
	}

	Matrix4x4 Matrix4x4::scaling(float x, float y, float z) {
		Matrix4x4 work;
		work.identity();
		work.a = x;
		work.f = y;
		work.k = z;
		return work;

	}

	Matrix4x4 Matrix4x4::rotateX(float r) {
		Matrix4x4 work;
		work.identity();
		work.f = std::cos(r);
		work.g = std::sin(r);
		work.j = -std::sin(r);
		work.k = std::cos(r);
		return work;
	}

	Matrix4x4 Matrix4x4::rotateY(float r) {
		Matrix4x4 work;
		work.identity();
		work.a = std::cos(r);
		work.c = -std::sin(r);
		work.i = std::sin(r);
		work.k = std::cos(r);
		return work;
	}

	Matrix4x4 Matrix4x4::rotateZ(float r) {
		Matrix4x4 work;
		work.identity();
		work.a = std::cos(r);
		work.b = std::sin(r);
		work.e = -std::sin(r);
		work.f = std::cos(r);
		return work;
	}

	Matrix4x4 Matrix4x4::rotateDegX(float r) {
		Matrix4x4 work;
		work.identity();
		r = myMath::degToRad(r);
		work.f = std::cos(r);
		work.g = std::sin(r);
		work.j = -std::sin(r);
		work.k = std::cos(r);
		return work;
	}

	Matrix4x4 Matrix4x4::rotateDegY(float r) {
		Matrix4x4 work;
		work.identity();
		r = myMath::degToRad(r);
		work.a = std::cos(r);
		work.c = -std::sin(r);
		work.i = std::sin(r);
		work.k = std::cos(r);
		return work;
	}

	Matrix4x4 Matrix4x4::rotateDegZ(float r) {
		Matrix4x4 work;
		work.identity();
		r = myMath::degToRad(r);
		work.a = std::cos(r);
		work.b = std::sin(r);
		work.e = -std::sin(r);
		work.f = std::cos(r);
		return work;
	}

	Matrix4x4 Matrix4x4::translate(float x, float y, float z) {
		Matrix4x4 work;
		work.identity();
		work.m = x;
		work.n = y;
		work.o = z;
		return work;
	}

	Matrix4x4 Matrix4x4::Camera(Vector3 cameraPos, Vector3 gazingPoint, Vector3 camUp) {
		Vector3 sight(gazingPoint - cameraPos);
		sight = Vector3::normalize(sight);

		Vector3 xAxis(Vector3::Cross(camUp,sight));
		xAxis = Vector3::normalize(xAxis);

		Vector3 yAxis(Vector3::Cross(sight,xAxis));
		yAxis= Vector3::normalize(yAxis);

		float dotX = Vector3::Dot(xAxis,cameraPos);
		float dotY = Vector3::Dot(yAxis, cameraPos);
		float dotZ = Vector3::Dot(sight, cameraPos);

		return Matrix4x4(xAxis.x, yAxis.x, sight.x, 0.0F,
						xAxis.y, yAxis.y, sight.y, 0.0F,
						xAxis.z, yAxis.z, sight.z, 0.0F,
						-dotX, -dotY, -dotZ, 1.0F);
	}

	Matrix4x4 Matrix4x4::perspective(float viewAngle, float width, float height, float clippingNear, float clippingFar) {
		Matrix4x4 work;
		work.identity();
		float h = 1 / std::tan(viewAngle/2);
		float w = h / (width/ height);
		float c = clippingFar - clippingNear;
		work.a = w;
		work.f = h;
		work.k = clippingFar / c;
		work.l = 1;
		work.o = -clippingNear * clippingFar / c;
		work.p = 0;
		return work;
	}