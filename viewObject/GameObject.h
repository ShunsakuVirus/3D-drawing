#pragma once
#include"Vector4.h"
#include"Vector2.h"
#include"Matrix4x4.h"
#include"lib/graph.hpp"

void line(int x1, int y1, int x2, int y2,Color c) {
	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	int dirx = 0;
	int diry = 0;
	int e = 0;
	int x = x1;
	int y = y1;
	if (x1 < x2) {
		dirx = 1;
	}
	else {
		dirx = -1;
	}
	if (y1 < y2) {
		diry = 1;
	}
	else {
		diry = -1;
	}
	while (x != x2 || y != y2) {
		drawPoint(x, y, 2, c);
		if (dy <= dx) {
			x += dirx;
			e += dy;
			if (e >= dx) {
				y += diry;
				e -= dx;
			}
		}
		else {
			y += diry;
			e += dx;
			if (e >= dy) {
				x += dirx;
				e -= dy;
			}
		}
	}
}

struct Box {
	float x;
	float y;
	float z;
private:
	Vector4 local_vtx[8];
	Vector3 vtx[8];
	Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;
	Vector3 changeLocalVtx;

public:
	Box() {
		identity();
	}

	void identity() {
		local_vtx[0] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[1] = Vector4::Vector4(0 + changeLocalVtx.x, 1 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[2] = Vector4::Vector4(1 + changeLocalVtx.x, 1 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[3] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[4] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[5] = Vector4::Vector4(0 + changeLocalVtx.x, 1 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[6] = Vector4::Vector4(1 + changeLocalVtx.x, 1 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[7] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
	}
	void SetLocalPosition(float _x, float _y, float _z) {
		changeLocalVtx.x = _x;
		changeLocalVtx.y = _y;
		changeLocalVtx.z = _z;
	}

	void Translate(float _x, float _y, float _z) {
		translate = Matrix4x4::translate(_x,_y,_z);
	}
	void Rotation(float _x, float _y, float _z) {
		rotX = Matrix4x4::rotateX(_x);
		rotY = Matrix4x4::rotateY(_y);
		rotZ = Matrix4x4::rotateZ(_z);
	}

	void Draw(Color c, Matrix4x4 camera, Matrix4x4 pers) {
		identity();
		Vector4 work = local_vtx[0] * scale* rotX*rotY*rotZ* translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		work = work * camera* pers;
		vtx[0] = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		for (int i = 1; i < 8; i++) {
			Vector4 work = local_vtx[i]* scale* rotX*rotY*rotZ* translate* camera* pers;
			vtx[i] = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		}
		for (int i = 0; i < 4; i++) {
			if (vtx[i].z < 1.0F && vtx[i].z != 0.0F &&
				vtx[(i+1)%4].z < 1.0F && vtx[(i+1)%4].z != 0.0F) {
				drawLine(vtx[i].x, vtx[i].y, vtx[(i + 1) % 4].x, vtx[(i + 1) % 4].y,1, c);
			}
			if (i + 4 == 7) {
				if (vtx[i+4].z < 1.0F && vtx[i+4].z != 0.0F &&
					vtx[4].z < 1.0F && vtx[4].z != 0.0F) {
					drawLine(vtx[i + 4].x, vtx[i + 4].y, vtx[4].x, vtx[4].y,1, c);
				}
			}
			else {
				if (vtx[i + 4].z < 1.0F && vtx[i + 4].z != 0.0F &&
					vtx[i + 5].z < 1.0F && vtx[i + 5].z != 0.0F) {
					drawLine(vtx[i + 4].x, vtx[i + 4].y, vtx[(i + 5)].x, vtx[(i + 5)].y,1, c);
				}
			}
			if (vtx[i].z < 1.0F && vtx[i].z != 0.0F &&
				vtx[i + 4].z < 1.0F && vtx[i + 4].z != 0.0F) {
				drawLine(vtx[i].x, vtx[i].y, vtx[i + 4].x, vtx[i + 4].y,1, c);
			}
		}
	}
};

struct Rect {
	float x;
	float y;
	float z;
private:
	Vector4 local_vtx[4];
	Vector3 vtx[4];
	Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;
	Vector3 changeLocalVtx;

public:
	Rect() {
		identity();
	}

	void identity() {
		local_vtx[0] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[1] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[2] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[3] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
	}
	void SetLocalPosition(float _x, float _y, float _z) {
		changeLocalVtx.x = _x;
		changeLocalVtx.y = _y;
		changeLocalVtx.z = _z;
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

	void Draw(Color c, Matrix4x4 camera, Matrix4x4 pers) {
		identity();
		Vector4 work = local_vtx[0] * scale* rotX*rotY*rotZ* translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		work = work * camera* pers;
		vtx[0] = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		for (int i = 1; i < 4; i++) {
			Vector4 work = local_vtx[i] * scale* rotX*rotY*rotZ* translate* camera* pers;
			vtx[i] = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		}
		for (int i = 0; i < 4; i++) {
			if (vtx[i].z < 1.0F && vtx[i].z != 0.0F &&
				vtx[(i + 1) % 4].z < 1.0F && vtx[(i + 1) % 4].z != 0.0F) {
				drawLine(vtx[i].x, vtx[i].y, vtx[(i + 1) % 4].x, vtx[(i + 1) % 4].y,1, c);
			}
		}
	}
};

struct Triangle {
	float x;
	float y;
	float z;
private:
	Vector4 local_vtx[3];
	Vector3 vtx[3];
	Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;
	Vector3 changeLocalVtx;

public:
	Triangle() {
		identity();
	}

	void identity() {
		local_vtx[0] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[1] = Vector4::Vector4(0.5F + changeLocalVtx.x, 0 + changeLocalVtx.y, 1 + changeLocalVtx.z, 1);
		local_vtx[2] = Vector4::Vector4(1 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
	}
	void SetLocalPosition(float _x, float _y, float _z) {
		changeLocalVtx.x = _x;
		changeLocalVtx.y = _y;
		changeLocalVtx.z = _z;
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

	void Draw(Color c, Matrix4x4 camera, Matrix4x4 pers) {
		identity();
		Vector4 work = local_vtx[0] * scale* rotX*rotY*rotZ* translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		work = work * camera* pers;
		vtx[0] = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		for (int i = 1; i < 3; i++) {
			Vector4 work = local_vtx[i] * scale* rotX*rotY*rotZ* translate* camera* pers;
			vtx[i] = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		}
		for (int i = 0; i < 3; i++) {
			if (vtx[i].z < 1.0F && vtx[i].z != 0.0F &&
				vtx[(i + 1) % 3].z < 1.0F && vtx[(i + 1) % 3].z != 0.0F) {
				drawLine(vtx[i].x, vtx[i].y, vtx[(i + 1) % 3].x, vtx[(i + 1) % 3].y,1, c);
			}
		}
	}
};

struct Point {
	float x;
	float y;
	float z;
private:
	Vector4 local_vtx;
	Vector3 vtx;
	/*Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;*/
	Matrix4x4 translate;
	Vector3 changeLocalVtx;

public:
	Point() {
		identity();
	}

	void identity() {
		local_vtx = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
	}
	void SetLocalPosition(float _x, float _y, float _z) {
		changeLocalVtx.x = _x;
		changeLocalVtx.y = _y;
		changeLocalVtx.z = _z;
	}

	/*void Scaling(float _x, float _y, float _z) {
		scale = Matrix4x4::scaling(_x, _y, _z);
	}

	void Rotation(float _x, float _y, float _z) {
		rotX = Matrix4x4::rotateX(_x);
		rotY = Matrix4x4::rotateY(_y);
		rotZ = Matrix4x4::rotateZ(_z);
	}*/

	void Translate(float _x, float _y, float _z) {
		translate = Matrix4x4::translate(_x, _y, _z);
	}

	void Draw(Color c, Matrix4x4 camera, Matrix4x4 pers) {
		identity();
		Vector4 work = local_vtx * translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		work = work*camera* pers;
		vtx = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		if (vtx.z < 1.0F && vtx.z != 0.0F) {
			drawPoint(vtx.x, vtx.y, 16, c);
		}
	}
};

struct Line {
public:
	float x;
	float y;
	float z;
private:
	Vector4 local_vtx[2];
	Vector3 vtx[2];
	Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;
	Vector3 changeLocalVtx;

public:
	Line() {
		identity();
	}

	void identity() {
		local_vtx[0] = Vector4::Vector4(0 + changeLocalVtx.x, 0 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
		local_vtx[1] = Vector4::Vector4(0 + changeLocalVtx.x, 1 + changeLocalVtx.y, 0 + changeLocalVtx.z, 1);
	}
	void SetLocalPosition(float _x, float _y, float _z) {
		changeLocalVtx.x = _x;
		changeLocalVtx.y = _y;
		changeLocalVtx.z = _z;
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

	void Draw(Color c, Matrix4x4 camera, Matrix4x4 pers) {
		identity();
		Vector4 work = local_vtx[0] * scale* rotX*rotY*rotZ* translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		work = work * camera* pers;
		vtx[0] = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		work = local_vtx[1]* scale* rotX*rotY*rotZ* translate* camera* pers;
		vtx[1] = Vector4::screenTransformation(work, 1920.0F, 1080.0F);
		if (vtx[0].z < 1.0F && vtx[0].z != 0.0F &&
			vtx[1].z < 1.0F && vtx[1].z != 0.0F) {
			drawLine(vtx[0].x, vtx[0].y, vtx[1].x, vtx[1].y, 1, c);
		}
	}
};