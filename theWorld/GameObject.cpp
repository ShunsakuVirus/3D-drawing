#pragma once
#include "GameObject.h"
const float dt = 1.0F / 60.0F;
Vector3 gravity(0.0F,-9.8F,0.0F);

void line(int x1, int y1, int x2, int y2, Color c) {
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

	Box::Box() {
		this->local_vtx[0] = Vector4::Vector4(0, 0, 0, 1);
		this->local_vtx[1] = Vector4::Vector4(0, 1, 0, 1);
		this->local_vtx[2] = Vector4::Vector4(1, 1, 0, 1);
		this->local_vtx[3] = Vector4::Vector4(1, 0, 0, 1);
		this->local_vtx[4] = Vector4::Vector4(0, 0, 1, 1);
		this->local_vtx[5] = Vector4::Vector4(0, 1, 1, 1);
		this->local_vtx[6] = Vector4::Vector4(1, 1, 1, 1);
		this->local_vtx[7] = Vector4::Vector4(1, 0, 1, 1);
	}

	void Box::SetLocalPosition(float _x, float _y, float _z) {
		this->local_vtx[0] = Vector4::Vector4(0 + _x, 0 + _y, 0 + _z, 1);
		this->local_vtx[1] = Vector4::Vector4(0 + _x, 1 + _y, 0 + _z, 1);
		this->local_vtx[2] = Vector4::Vector4(1 + _x, 1 + _y, 0 + _z, 1);
		this->local_vtx[3] = Vector4::Vector4(1 + _x, 0 + _y, 0 + _z, 1);
		this->local_vtx[4] = Vector4::Vector4(0 + _x, 0 + _y, 1 + _z, 1);
		this->local_vtx[5] = Vector4::Vector4(0 + _x, 1 + _y, 1 + _z, 1);
		this->local_vtx[6] = Vector4::Vector4(1 + _x, 1 + _y, 1 + _z, 1);
		this->local_vtx[7] = Vector4::Vector4(1 + _x, 0 + _y, 1 + _z, 1);
	}

	void Box::Translate(float _x, float _y, float _z) {
		this->translate = Matrix4x4::translate(_x, _y, _z);
	}
	void Box::Rotation(float _x, float _y, float _z) {
		this->rotX = Matrix4x4::rotateX(_x);
		this->rotY = Matrix4x4::rotateY(_y);
		this->rotZ = Matrix4x4::rotateZ(_z);
	}

	void Box::Draw(Color c, Camera cam) {
		Vector4 work;
		work = work * this->scale* this->rotX*this->rotY*this->rotZ* this->translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		for (int i = 0; i < 8; i++) {
			work = this->local_vtx[i] * this->scale* this->rotX*this->rotY*this->rotZ* this->translate* cam.viewMat* cam.projMat;
			this->vtx[i] = Vector4::screenTransformation(work, 960, 540);
		}
		for (int i = 0; i < 4; i++) {
			if (this->vtx[i].z < 1.0F && this->vtx[i].z != 0.0F &&
				this->vtx[(i + 1) % 4].z < 1.0F && this->vtx[(i + 1) % 4].z != 0.0F) {
				drawLine(this->vtx[i].x, this->vtx[i].y, this->vtx[(i + 1) % 4].x, this->vtx[(i + 1) % 4].y, 1, c);
			}
			if (i + 4 == 7) {
				if (this->vtx[i + 4].z < 1.0F && this->vtx[i + 4].z != 0.0F &&
					this->vtx[4].z < 1.0F && this->vtx[4].z != 0.0F) {
					drawLine(this->vtx[i + 4].x, this->vtx[i + 4].y, this->vtx[4].x, this->vtx[4].y, 1, c);
				}
			}
			else {
				if (this->vtx[i + 4].z < 1.0F && this->vtx[i + 4].z != 0.0F &&
					this->vtx[i + 5].z < 1.0F && this->vtx[i + 5].z != 0.0F) {
					drawLine(this->vtx[i + 4].x, this->vtx[i + 4].y, this->vtx[(i + 5)].x, this->vtx[(i + 5)].y, 1, c);
				}
			}
			if (this->vtx[i].z < 1.0F && this->vtx[i].z != 0.0F &&
				this->vtx[i + 4].z < 1.0F && this->vtx[i + 4].z != 0.0F) {
				drawLine(this->vtx[i].x, this->vtx[i].y, this->vtx[i + 4].x, this->vtx[i + 4].y, 1, c);
			}
		}
	}

	Rect::Rect() {
		this->local_vtx[0] = Vector4::Vector4(0, 0, 0, 1);
		this->local_vtx[1] = Vector4::Vector4(0, 0, 1, 1);
		this->local_vtx[2] = Vector4::Vector4(1, 0, 1, 1);
		this->local_vtx[3] = Vector4::Vector4(1, 0, 0, 1);
	}

	void Rect::SetLocalPosition(float _x, float _y, float _z) {
		this->local_vtx[0] = Vector4::Vector4(0 + _x, 0 + _y, 0 + _z, 1);
		this->local_vtx[1] = Vector4::Vector4(0 + _x, 0 + _y, 1 + _z, 1);
		this->local_vtx[2] = Vector4::Vector4(1 + _x, 0 + _y, 1 + _z, 1);
		this->local_vtx[3] = Vector4::Vector4(1 + _x, 0 + _y, 0 + _z, 1);
	}

	void Rect::Scaling(float _x, float _y, float _z) {
		this->scale = Matrix4x4::scaling(_x, _y, _z);
	}

	void Rect::Rotation(float _x, float _y, float _z) {
		this->rotX = Matrix4x4::rotateX(_x);
		this->rotY = Matrix4x4::rotateY(_y);
		this->rotZ = Matrix4x4::rotateZ(_z);
	}

	void Rect::Translate(float _x, float _y, float _z) {
		this->translate = Matrix4x4::translate(_x, _y, _z);
	}

	void Rect::Draw(Color c, Camera cam) {
		Vector4 work;
		work = work * this->scale* this->rotX*this->rotY*this->rotZ* this->translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		for (int i = 0; i < 4; i++) {
			work = this->local_vtx[i] * this->scale* this->rotX*this->rotY*this->rotZ* this->translate* cam.viewMat* cam.projMat;
			this->vtx[i] = Vector4::screenTransformation(work, 960, 540);
		}
		for (int i = 0; i < 4; i++) {
			if (this->vtx[i].z < 1.0F && this->vtx[i].z != 0.0F &&
				this->vtx[(i + 1) % 4].z < 1.0F && this->vtx[(i + 1) % 4].z != 0.0F) {
				drawLine(this->vtx[i].x, this->vtx[i].y, this->vtx[(i + 1) % 4].x, this->vtx[(i + 1) % 4].y, 1, c);
			}
		}
	}

	Triangle::Triangle() {
		this->local_vtx[0] = Vector4::Vector4(0, 0, 0, 1);
		this->local_vtx[1] = Vector4::Vector4(0.5F, 0, 1, 1);
		this->local_vtx[2] = Vector4::Vector4(1, 0, 0, 1);
	}

	void Triangle::SetLocalPosition(float _x, float _y, float _z) {
		this->local_vtx[0] = Vector4::Vector4(0 + _x, 0 + _y, 0 + _z, 1);
		this->local_vtx[1] = Vector4::Vector4(0.5F + _x, 0 + _y, 1 + _z, 1);
		this->local_vtx[2] = Vector4::Vector4(1 + _x, 0 + _y, 0 + _z, 1);
	}

	void Triangle::Scaling(float _x, float _y, float _z) {
		this->scale = Matrix4x4::scaling(_x, _y, _z);
	}

	void Triangle::Rotation(float _x, float _y, float _z) {
		this->rotX = Matrix4x4::rotateX(_x);
		this->rotY = Matrix4x4::rotateY(_y);
		this->rotZ = Matrix4x4::rotateZ(_z);
	}

	void Triangle::Translate(float _x, float _y, float _z) {
		this->translate = Matrix4x4::translate(_x, _y, _z);
	}

	void Triangle::Draw(Color c, Camera cam) {
		Vector4 work;
		work = work * this->scale* this->rotX*this->rotY*this->rotZ* this->translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		for (int i = 0; i < 3; i++) {
			work = this->local_vtx[i] * this->scale* this->rotX*this->rotY*this->rotZ* this->translate* cam.viewMat* cam.projMat;
			this->vtx[i] = Vector4::screenTransformation(work, 960, 540);
		}
		for (int i = 0; i < 3; i++) {
			if (this->vtx[i].z < 1.0F && this->vtx[i].z != 0.0F &&
				this->vtx[(i + 1) % 3].z < 1.0F && this->vtx[(i + 1) % 3].z != 0.0F) {
				drawLine(this->vtx[i].x, this->vtx[i].y, this->vtx[(i + 1) % 3].x, this->vtx[(i + 1) % 3].y, 1, c);
			}
		}
	}

	Point::Point() {
		this->local_vtx = Vector4::Vector4(0, 0, 0, 1);
		this->size = 1;
	}

	void Point::SetLocalPosition(float _x, float _y, float _z) {
		this->local_vtx = Vector4::Vector4(_x, _y, _z, 1);
	}

	/*void Point::Scaling(float _x, float _y, float _z) {
	scale = Matrix4x4::scaling(_x, _y, _z);
	}*/

	void Point::Rotation(float _x, float _y, float _z) {
		this->rotX = Matrix4x4::rotateX(_x);
		this->rotY = Matrix4x4::rotateY(_y);
		this->rotZ = Matrix4x4::rotateZ(_z);
	}

	void Point::Translate(float _x, float _y, float _z) {
		this->translate = Matrix4x4::translate(_x, _y, _z);
	}

	void Point::Draw(Color c, Camera cam) {
		Vector4 work;
		work = work * this->rotX*this->rotY*this->rotZ* this->translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		work = this->local_vtx * this->rotX*this->rotY*this->rotZ* this->translate* cam.viewMat* cam.projMat;
		this->vtx = Vector4::screenTransformation(work, 960, 540);
		if (this->vtx.z < 1.0F && this->vtx.z != 0.0F) {
			drawPoint(this->vtx.x, this->vtx.y, this->size, c);
		}
	}

	Line::Line() {
		this->local_vtx[0] = Vector4::Vector4(0, 0, 0, 1);
		this->local_vtx[1] = Vector4::Vector4(0, 1, 0, 1);
	}

	void Line::SetLocalPosition(float _x, float _y, float _z) {
		this->local_vtx[0] = Vector4::Vector4(0 + _x, 0 + _y, 0 + _z, 1);
		this->local_vtx[1] = Vector4::Vector4(0 + _x, 1 + _y, 0 + _z, 1);
	}

	void Line::Scaling(float _x, float _y, float _z) {
		this->scale = Matrix4x4::scaling(_x, _y, _z);
	}

	void Line::Rotation(float _x, float _y, float _z) {
		this->rotX = Matrix4x4::rotateX(_x);
		this->rotY = Matrix4x4::rotateY(_y);
		this->rotZ = Matrix4x4::rotateZ(_z);
	}

	void Line::Translate(float _x, float _y, float _z) {
		this->translate = Matrix4x4::translate(_x, _y, _z);
	}

	void Line::Draw(Color c, Camera cam) {
		Vector4 work;
		work = work * this->scale* this->rotX*this->rotY*this->rotZ* this->translate;
		this->x = work.x;
		this->y = work.y;
		this->z = work.z;
		work = this->local_vtx[0] * this->scale* this->rotX*this->rotY*this->rotZ* this->translate* cam.viewMat* cam.projMat;
		this->vtx[0] = Vector4::screenTransformation(work, 960, 540);
		work = this->local_vtx[1] * this->scale* this->rotX*this->rotY*this->rotZ* this->translate* cam.viewMat* cam.projMat;
		this->vtx[1] = Vector4::screenTransformation(work, 960, 540);
		if (this->vtx[0].z < 1.0F && this->vtx[0].z != 0.0F &&
			this->vtx[1].z < 1.0F && this->vtx[1].z != 0.0F) {
			drawLine(this->vtx[0].x, this->vtx[0].y, this->vtx[1].x, this->vtx[1].y, 2, c);
		}
	}

	Particle::Particle() {

	}
	Particle::Particle(float x, float y, float z, float h, Random &dice) {
		this->hu = h;

		this->acceleration = Vector3(0,0,0);
		this->velocity = Vector3(0,dice(-25.0F, -10.0F),0);
		this->location = Vector3(x,y,z);
		this->seed = true;
		this->lifespan = 255.0F;
	}

	Particle::Particle(Vector3 l, float h, Random &dice) {
		this->hu = h;
		this->acceleration = Vector3(0,0,0);
		this->velocity = Vector3(dice(),dice(),dice()).normalized();
		this->velocity = this->velocity * dice(8.0F,16.0F);
		this->location = l;
		this->lifespan = 255.0F;
	}
	
	void Particle::applyForce(Vector3 force) {
		this->acceleration = this->acceleration + force;
	}

	void Particle::run(Camera cam) {
		this->update();
		this->display(cam);
	}

	bool Particle::explode() {
		if (this->seed && this->velocity.y > 0.0F) {
			this->lifespan = 0.0F;
			return true;
		}
		return false;
	}

	void Particle::update() {
		this->velocity = this->velocity + this->acceleration;
		this->location = this->location + this->velocity;
		if (!this->seed) {
			this->lifespan -= 5;
			this->velocity = this->velocity * 0.9F;
		}
		this->acceleration = this->acceleration * 0;
	}

	void Particle::display(Camera cam) {
		float size = 0;
		if (this->seed) {
			size = 8;
		}
		else {
			size = 4;
		}
		Vector4 work;
		Vector3 vtx;
		Matrix4x4 translate = Matrix4x4::translate(this->location.x, this->location.y, this->location.z);
		work = work* translate* cam.viewMat* cam.projMat;
		vtx = Vector4::screenTransformation(work, 960, 540);
		if (vtx.z < 1.0F && vtx.z != 0.0F) {
			drawPoint(vtx.x, vtx.y, size, Color(this->hu, 255,255,this->lifespan));
		}
	}

	bool Particle::isDead() {
		if (this->lifespan < 0.0F) {
			return true;
		}
		else {
			return false;
		}
	}

	Firework::Firework(Random &dice) {
		this->hu = dice(255);
		this->firework = Particle(dice(-10.0F,10.0F),10.0F,dice(-10.0F,10.0F), this->hu, dice);
		this->particles = std::list<Particle>();
	}
	bool Firework::done(){
		if (this->firework.isnull && this->particles.empty()) {
			return true;
		}
		else {
			return false;
		}
	}
	void Firework::run(Camera cam, Random &dice) {
		if (!this->firework.isnull) {
			this->firework.applyForce(gravity);
			this->firework.update();
			this->firework.display(cam);

			if (firework.explode()) {
				for (int i = 0; i < 750; i++) {
					particles.push_back(Particle(firework.location, hu, dice));
				}
				firework.isnull = true;
			}
		}

		for (int i = particles.size() - 1; i >= 0; i--) {
			auto ite = particles.begin();
			for (int j = 0; j < i; j++) {
				++ite;
			}
			Particle p = *ite;
			p.applyForce(gravity);
			p.run(cam);
			if (p.isDead()) {
				particles.erase(ite);
			}
		}
	}
	bool Firework::dead() {
		if (particles.empty()) {
			return true;
		}
		else {
			return false;
		}
	}

	Vector3 Raycast::rayCastHit(Vector3 startPos, Vector3 direction, float distance, Vector3 &point) {
		Vector3 diff = (direction - startPos).normalized();
		/*for (float f = 0; f < distance;f+=1.0F) {
			
		}*/
		return Vector3();
	}