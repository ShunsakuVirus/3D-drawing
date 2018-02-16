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

	/*Matrix4x4 Matrix4x4::camera(Vector3 cameraPos, Vector3 gazingPoint, Vector3 camUp) {
		Vector3 sight(gazingPoint - cameraPos);
		sight = sight.normalized();

		Vector3 xAxis(Vector3::cross(camUp,sight));
		xAxis = xAxis.normalized();

		Vector3 yAxis(Vector3::cross(sight,xAxis));
		yAxis = yAxis.normalized();

		float dotX = Vector3::dot(xAxis, cameraPos);
		float dotY = Vector3::dot(yAxis, cameraPos);
		float dotZ = Vector3::dot(sight, cameraPos);

		return Matrix4x4(xAxis.x, yAxis.x, sight.x, 0.0F,
						xAxis.y, yAxis.y, sight.y, 0.0F,
						xAxis.z, yAxis.z, sight.z, 0.0F,
						-dotX, -dotY, -dotZ, 1.0F);
	}

	Matrix4x4 Matrix4x4::perspective(float fieldOfView, float width, float height, float clippingNear, float clippingFar) {
		Matrix4x4 work;
		work.identity();
		float h = 1.0F / (float)std::tan(fieldOfView/2.0F);
		float w = h / ((float)width/ (float)height);
		float c = clippingFar - clippingNear;
		work.a = w;
		work.f = h;
		work.k = clippingFar / c;
		work.l = 1.0F;
		work.o = -clippingNear * clippingFar / c;
		work.p = 0.0F;
		return work;
	}*/

	Matrix4x4 Matrix4x4::inverse(Matrix4x4 mat) {
		float detA = mat.a*mat.f*mat.k*mat.p +
					mat.a*mat.g*mat.l*mat.n +
					mat.a*mat.h*mat.j*mat.o +
					mat.b*mat.e*mat.l*mat.o +
					mat.b*mat.g*mat.i*mat.p +
					mat.b*mat.h*mat.k*mat.m +
					mat.c*mat.e*mat.j*mat.p +
					mat.c*mat.f*mat.l*mat.m +
					mat.c*mat.h*mat.i*mat.n +
					mat.d*mat.e*mat.k*mat.n +
					mat.d*mat.f*mat.i*mat.o +
					mat.d*mat.g*mat.j*mat.m -
					mat.a*mat.f*mat.l*mat.o -
					mat.a*mat.g*mat.j*mat.p -
					mat.a*mat.h*mat.k*mat.n -
					mat.b*mat.e*mat.k*mat.p -
					mat.b*mat.g*mat.l*mat.m -
					mat.b*mat.h*mat.i*mat.o -
					mat.c*mat.e*mat.l*mat.n -
					mat.c*mat.f*mat.i*mat.p -
					mat.c*mat.h*mat.j*mat.m -
					mat.d*mat.e*mat.j*mat.o -
					mat.d*mat.f*mat.k*mat.m -
					mat.d*mat.g*mat.i*mat.n;
		Matrix4x4 ret;
		if (detA == 0.0F) return ret;
		ret.a = mat.f*mat.k*mat.p + mat.g*mat.l*mat.n + mat.h*mat.j*mat.o - mat.f*mat.l*mat.o - mat.g*mat.j*mat.p - mat.h*mat.k*mat.n;
		ret.b = mat.b*mat.l*mat.o + mat.c*mat.j*mat.p + mat.d*mat.k*mat.n - mat.b*mat.k*mat.p - mat.c*mat.l*mat.n - mat.d*mat.j*mat.o;
		ret.c = mat.b*mat.g*mat.p + mat.c*mat.h*mat.n + mat.d*mat.f*mat.o - mat.b*mat.h*mat.o - mat.c*mat.f*mat.p - mat.d*mat.g*mat.n;
		ret.d = mat.b*mat.h*mat.k + mat.c*mat.f*mat.l + mat.d*mat.g*mat.j - mat.b*mat.g*mat.l - mat.c*mat.h*mat.j - mat.d*mat.f*mat.k;
		ret.e = mat.e*mat.l*mat.o + mat.g*mat.i*mat.p + mat.h*mat.k*mat.m - mat.e*mat.k*mat.p - mat.g*mat.l*mat.m - mat.h*mat.i*mat.o;
		ret.f = mat.a*mat.k*mat.p + mat.c*mat.l*mat.m + mat.d*mat.i*mat.o - mat.a*mat.l*mat.o - mat.c*mat.i*mat.p - mat.d*mat.k*mat.m;
		ret.g = mat.a*mat.h*mat.o + mat.c*mat.e*mat.p + mat.d*mat.g*mat.m - mat.a*mat.g*mat.p - mat.c*mat.h*mat.m - mat.d*mat.e*mat.o;
		ret.h = mat.a*mat.g*mat.l + mat.c*mat.h*mat.i + mat.d*mat.e*mat.k - mat.a*mat.h*mat.k - mat.c*mat.e*mat.l - mat.d*mat.g*mat.i;
		ret.i = mat.e*mat.j*mat.p + mat.f*mat.l*mat.m + mat.h*mat.i*mat.n - mat.e*mat.l*mat.n - mat.f*mat.i*mat.p - mat.h*mat.j*mat.m;
		ret.j = mat.a*mat.l*mat.n + mat.b*mat.i*mat.p + mat.d*mat.j*mat.m - mat.a*mat.j*mat.p - mat.b*mat.l*mat.m - mat.d*mat.i*mat.n;
		ret.k = mat.a*mat.f*mat.p + mat.b*mat.h*mat.m + mat.d*mat.e*mat.n - mat.a*mat.h*mat.n - mat.b*mat.e*mat.p - mat.d*mat.f*mat.m;
		ret.l = mat.a*mat.h*mat.j + mat.b*mat.e*mat.l + mat.d*mat.f*mat.i - mat.a*mat.f*mat.l - mat.b*mat.h*mat.i - mat.d*mat.e*mat.j;
		ret.m = mat.e*mat.k*mat.n + mat.f*mat.i*mat.o + mat.g*mat.j*mat.m - mat.e*mat.j*mat.o - mat.f*mat.k*mat.m - mat.g*mat.i*mat.n;
		ret.n = mat.a*mat.j*mat.o + mat.b*mat.k*mat.m + mat.c*mat.i*mat.n - mat.a*mat.k*mat.n - mat.b*mat.i*mat.o - mat.c*mat.j*mat.m;
		ret.o = mat.a*mat.g*mat.n + mat.b*mat.e*mat.o + mat.c*mat.f*mat.m - mat.a*mat.f*mat.o - mat.b*mat.g*mat.m - mat.c*mat.e*mat.n;
		ret.p = mat.a*mat.f*mat.k + mat.b*mat.g*mat.i + mat.c*mat.e*mat.j - mat.a*mat.g*mat.j - mat.b*mat.e*mat.k - mat.c*mat.f*mat.i;
		return ret;
	}

	Camera::Camera() {
		this->x = 0.0F;
		this->y = 1.0F;
		this->z = -10.0F;
	}

	void Camera::cameraMatrix(Vector3 cameraPos, Vector3 gazingPoint, Vector3 camUp) {
		this->x = cameraPos.x;
		this->y = cameraPos.y;
		this->z = cameraPos.z;
		Vector3 sight(gazingPoint - cameraPos);
		sight = sight.normalized();
		this->forward = sight;

		Vector3 xAxis(Vector3::cross(camUp, sight));
		xAxis = xAxis.normalized();
		this->right = xAxis;

		Vector3 yAxis(Vector3::cross(sight, xAxis));
		yAxis = yAxis.normalized();
		this->up = yAxis;

		float dotX = Vector3::dot(xAxis, cameraPos);
		float dotY = Vector3::dot(yAxis, cameraPos);
		float dotZ = Vector3::dot(sight, cameraPos);

		this->viewMat = Matrix4x4(xAxis.x, yAxis.x, sight.x, 0.0F,
								xAxis.y, yAxis.y, sight.y, 0.0F,
								xAxis.z, yAxis.z, sight.z, 0.0F,
								-dotX, -dotY, -dotZ, 1.0F);
	}

	void Camera::projection(float fieldOfView, float width, float height, float clippingNear, float clippingFar) {
		Matrix4x4 work;
		work.identity();
		float h = 1.0F / (float)std::tan(fieldOfView / 2.0F);
		float w = h / ((float)width / (float)height);
		float c = clippingFar - clippingNear;
		work.a = w;
		work.f = h;
		work.k = clippingFar / c;
		work.l = 1.0F;
		work.o = -clippingNear * clippingFar / c;
		work.p = 0.0F;
		this->projMat = work;
	}

	void Camera::viewPort() {
		Matrix4x4 work;
		work.identity();
		work.a = 960.0F;
		work.f = -540.0F;
		work.m = 960.0F;
		work.n = 540.0F;
		this->vPortMat = work;
	}

	Vector3 Camera::screenToWorldPoint(Vector3 position) {
		Vector4 v(position.x,position.y,position.z,this->z);
		v = v* Matrix4x4::inverse(this->vPortMat);
		Vector4 work(v.x*this->z, v.y*this->z, v.z*this->z, this->z);
		work = work* Matrix4x4::inverse(this->projMat);
		work = work* Matrix4x4::inverse(this->viewMat);
		return Vector3(work.x,work.y,work.z);
	}

	Vector3 Camera::worldToScreenPoint(Vector3 position) {
		Vector4 v(position.x, position.y, position.z, 1.0F);
		v = v * this->viewMat*this->projMat;
		Vector3 ret;
		ret = Vector4::screenTransformation(v, 960, 540);
		return ret;
	}