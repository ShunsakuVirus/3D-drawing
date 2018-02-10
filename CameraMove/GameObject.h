#pragma once
#include "lib/framework.hpp"
#include"Vector4.h"
#include"Vector3.h"
#include"Matrix4x4.h"

struct Box {
	Vector4 local_vtx[8];
	Vector3 vtx[8];
	Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;
	Vector3 changeLocalVtx;

	Box() {
		identity();
	}

	void identity() {
		local_vtx[0] = Vector4::Vector4(1 + changeLocalVtx.x, 1 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[1] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[2] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[3] = Vector4::Vector4(0 + changeLocalVtx.x, 1 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[4] = Vector4::Vector4(1 + changeLocalVtx.x, 1 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[5] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[6] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[7] = Vector4::Vector4(0 + changeLocalVtx.x, 1 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
	}
	void SetLocalPosition(float _x, float _y, float _z) {
		for (int i = 0; i < 8;i++) {
			changeLocalVtx.x = _x;
			changeLocalVtx.y = _y;
			changeLocalVtx.z = _z;
		}
	}

	void Translate(float _x, float _y, float _z) {
		translate = Matrix4x4::translate(_x,_y,_z);
	}
	void Rotation(float _x, float _y, float _z) {
		rotX = Matrix4x4::rotateX(_x);
		rotY = Matrix4x4::rotateY(_y);
		rotZ = Matrix4x4::rotateZ(_z);
	}

	void Draw(Color c, float width, float height, Matrix4x4 camera, Matrix4x4 pers) {
		identity();
		for (int i = 0; i < 8; i++) {
			Vector4 work = local_vtx[i]* scale* rotX*rotY*rotZ* translate* camera* pers;
			vtx[i] = Vector4::screenTransformation(work, width, height);
		}
		for (int i = 0; i < 4; i++) {
			if (vtx[i].z < 1.0F && vtx[i].z != 0.0F &&
				vtx[(i+1)%4].z < 1.0F && vtx[(i+1)%4].z != 0.0F) {
				drawLine(vtx[i].x, vtx[i].y, vtx[(i + 1) % 4].x, vtx[(i + 1) % 4].y, 3, c);
			}
			if (i + 4 == 7) {
				if (vtx[i+4].z < 1.0F && vtx[i+4].z != 0.0F &&
					vtx[4].z < 1.0F && vtx[4].z != 0.0F) {
					drawLine(vtx[i + 4].x, vtx[i + 4].y, vtx[4].x, vtx[4].y, 3, c);
				}
			}
			else {
				if (vtx[i + 4].z < 1.0F && vtx[i + 4].z != 0.0F &&
					vtx[i + 5].z < 1.0F && vtx[i + 5].z != 0.0F) {
					drawLine(vtx[i + 4].x, vtx[i + 4].y, vtx[(i + 5)].x, vtx[(i + 5)].y, 3, c);
				}
			}
			if (vtx[i].z < 1.0F && vtx[i].z != 0.0F &&
				vtx[i + 4].z < 1.0F && vtx[i + 4].z != 0.0F) {
				drawLine(vtx[i].x, vtx[i].y, vtx[i + 4].x, vtx[i + 4].y, 3, c);
			}
		}
	}
};

struct Rect {
	Vector4 local_vtx[4];
	Vector3 vtx[4];
	Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;
	Vector3 changeLocalVtx;

	Rect() {
		identity();
	}

	void identity() {
		local_vtx[0] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[1] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[2] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[3] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
	}
	void SetLocalPosition(float _x, float _y, float _z) {
		for (int i = 0; i < 8; i++) {
			changeLocalVtx.x = _x;
			changeLocalVtx.y = _y;
			changeLocalVtx.z = _z;
		}
	}

	void Scaling(float _x, float _y, float _z) {
		scale = Matrix4x4::scaling(_x,_y,_z);
	}

	void Rotation(float _x, float _y, float _z) {
		rotX = Matrix4x4::rotateX(_x);
		rotY = Matrix4x4::rotateY(_y);
		rotZ = Matrix4x4::rotateZ(_z);
	}

	void Translate(float _x, float _y, float _z) {
		translate = Matrix4x4::translate(_x, _y, _z);
	}

	void Draw(Color c, float width, float height, Matrix4x4 camera, Matrix4x4 pers) {
		identity();
		for (int i = 0; i < 4; i++) {
			Vector4 work = local_vtx[i] * scale* rotX*rotY*rotZ* translate* camera* pers;
			vtx[i] = Vector4::screenTransformation(work, width, height);
		}
		for (int i = 0; i < 4; i++) {
			if (vtx[i].z < 1.0F && vtx[i].z != 0.0F &&
				vtx[(i + 1) % 4].z < 1.0F && vtx[(i + 1) % 4].z != 0.0F) {
				drawLine(vtx[i].x, vtx[i].y, vtx[(i + 1) % 4].x, vtx[(i + 1) % 4].y, 3, c);
			}
		}
	}
};

struct Triangle {
	Vector4 local_vtx[3];
	Vector3 vtx[3];
	Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;
	Vector3 changeLocalVtx;

	Triangle() {
		identity();
	}

	void identity() {
		local_vtx[0] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[1] = Vector4::Vector4(0.5F + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[2] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
	}
	void SetLocalPosition(float _x, float _y, float _z) {
		for (int i = 0; i < 8; i++) {
			changeLocalVtx.x = _x;
			changeLocalVtx.y = _y;
			changeLocalVtx.z = _z;
		}
	}

	void Scaling(float _x, float _y, float _z) {
		scale = Matrix4x4::scaling(_x, _y, _z);
	}

	void Rotation(float _x, float _y, float _z) {
		rotX = Matrix4x4::rotateX(_x);
		rotY = Matrix4x4::rotateY(_y);
		rotZ = Matrix4x4::rotateZ(_z);
	}

	void Translate(float _x, float _y, float _z) {
		translate = Matrix4x4::translate(_x, _y, _z);
	}

	void Draw(Color c, float width, float height, Matrix4x4 camera, Matrix4x4 pers) {
		identity();
		for (int i = 0; i < 3; i++) {
			Vector4 work = local_vtx[i] * scale* rotX*rotY*rotZ* translate* camera* pers;
			vtx[i] = Vector4::screenTransformation(work, width, height);
		}
		for (int i = 0; i < 3; i++) {
			if (vtx[i].z < 1.0F && vtx[i].z != 0.0F &&
				vtx[(i + 1) % 3].z < 1.0F && vtx[(i + 1) % 3].z != 0.0F) {
				drawLine(vtx[i].x, vtx[i].y, vtx[(i + 1) % 3].x, vtx[(i + 1) % 3].y, 3, c);
			}
		}
	}
};