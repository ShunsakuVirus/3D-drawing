#include "lib/framework.hpp"
#include "Matrix4x4.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"

enum Size {
  WIDTH  = 1000,
  HEIGHT = 1000
};

int main() {
	AppEnv env(Size::WIDTH, Size::HEIGHT);
	Matrix4x4 camera;
	Matrix4x4 pers;

	Vector4 localVertex[3];
	localVertex[0] = Vector4::Vector4(1,0,10,1);
	localVertex[1] = Vector4::Vector4(-1,0,10,1);
	localVertex[2] = Vector4::Vector4(0,1,10,1);

	Vector3 vertex[3];

	Matrix4x4 translate;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 scal;
	float a = 0;
  while (env.isOpen()) {
    env.begin();

	camera = Matrix4x4::Camera(Vector3(0,0,0),Vector3(0,0,1),Vector3(0,1,0));
	pers = Matrix4x4::perspective(degToRad(60),WIDTH, HEIGHT, 1,1000.0F);
	//translate = Matrix4x4::translate(0,0,0);
	//rotX = Matrix4x4::rotateX(a);
	//rotY = Matrix4x4::rotateY(a);
	//rotZ = Matrix4x4::rotateZ(a);
	//scal = Matrix4x4::scaling(10,1,1);
	a += 0.01F;
	for (int i = 0; i < elemsof(localVertex);i++) {
		Vector4 work = localVertex[i] * scal* rotX*rotY*rotZ* translate* camera *pers;
		vertex[i] = Vector4::ScreenTransformation(work,WIDTH,HEIGHT);
		//vertex[i] = Vector3::Vector3(work.x / work.w , work.y / work.w, work.z / work.w);
		//vertex[i].x *= WIDTH / 2;
		//vertex[i].y *= HEIGHT / 2;
	}

	for (int i = 0; i < elemsof(vertex); i++) {
		drawLine(vertex[i].x,vertex[i].y,vertex[(i+1)%3].x,vertex[(i+1)%3].y,3,Color(1,1,1));
	}
    env.end();
  }
}