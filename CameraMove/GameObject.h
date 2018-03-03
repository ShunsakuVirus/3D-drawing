#pragma once
#include"Vector2.h"
#include"Matrix4x4.h"
#include"lib/graph.hpp"
#include"lib\random.hpp"
#include<list>
#include <ctime>

struct Box {
	float x;
	float y;
	float z;
	Vector3 vtx[8];
private:
	Vector4 local_vtx[8];
	Matrix4x4 scale;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;

public:
	Box();

	void SetLocalPosition(float _x, float _y, float _z);

	void Translate(float _x, float _y, float _z);
	void Rotation(float _x, float _y, float _z);

	void Draw(Color c, Camera cam);
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

public:
	Rect();

	void SetLocalPosition(float _x, float _y, float _z);

	void Scaling(float _x, float _y, float _z);

	void Rotation(float _x, float _y, float _z);

	void Translate(float _x, float _y, float _z);

	void Draw(Color c, Camera cam);
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

public:
	Triangle();

	void SetLocalPosition(float _x, float _y, float _z);

	void Scaling(float _x, float _y, float _z);

	void Rotation(float _x, float _y, float _z);

	void Translate(float _x, float _y, float _z);

	void Draw(Color c, Camera cam);
};

struct Point {
	float x;
	float y;
	float z;
	float size;
	float timeScl;
private:
	Vector4 local_vtx;
	Vector3 vtx;
	/*Matrix4x4 scale;*/
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;

public:
	Point();

	void SetLocalPosition(float _x, float _y, float _z);

	/*void Scaling(float _x, float _y, float _z);*/

	void Rotation(float _x, float _y, float _z);

	void Translate(float _x, float _y, float _z);

	void Draw(Color c, Camera cam);
};

struct Line {
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

public:
	Line();

	void SetLocalPosition(float _x, float _y, float _z);

	void Scaling(float _x, float _y, float _z);

	void Rotation(float _x, float _y, float _z);

	void Translate(float _x, float _y, float _z);

	void Draw(Color c, Camera cam);
};

struct Circle {
	float x;
	float y;
	float z;
	float size;
	float timeScl;
private:
	Vector4 local_vtx;
	Vector3 vtx;
	/*Matrix4x4 scale;*/
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 translate;

public:
	Circle();

	void SetLocalPosition(float _x, float _y, float _z);

	/*void Scaling(float _x, float _y, float _z);*/

	void Rotation(float _x, float _y, float _z);

	void Translate(float _x, float _y, float _z);

	void Draw(Color c, Camera cam);
};

struct Particle {
	Point point;
	Vector3 location;
	Vector3 velocity;
	Vector3 acceleration;
	float lifespan;

	bool seed = false;
	bool isnull = false;

	float hu;

	Particle();
	Particle(float x, float y, float z, float h, Random &dice);
	Particle(Vector3 l, float h, Random &dice);

	void applyForce(Vector3 force);

	void run(Camera cam);

	bool explode();

	void update();

	void display(Camera cam);

	bool isDead();
};
struct Firework {
	std::list<Particle> particles;
	Particle firework;
	float hu;
	Firework(Random &dice);
	
	bool done();

	void run(Camera cam, Random &dice);

	bool dead();
};

struct Raycast {
	Vector3 rayCastHit(Vector3 startPos, Vector3 direction, float distance, Vector3 &point);
};