#include "lib/framework.hpp"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector2.h"

enum Size {
  WIDTH  = 800,
  HEIGHT = 600
};

int main() {
	AppEnv env(Size::WIDTH, Size::HEIGHT);
	Matrix4x4 camera;

	Vector3 vertex1(50,0,2);
	Vector3 vertex2(-50,0,2);
	Vector3 vertex3(0,50,2);

	Vector3 vertex[3];

	Matrix4x4 translate;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 scal;
	float a = 0;
  while (env.isOpen()) {
    env.begin();
	
	//Vector2 mouse(env.mousePosition().x(), env.mousePosition().y());

	camera = Matrix4x4::Camera(Vector3(0,0,0),Vector3(0,0,1),Vector3(0,1,0));
	translate = Matrix4x4::translate(50,0,0);
	//rotX = Matrix4x4::rotateX(a);
	//rotY = Matrix4x4::rotateY(a);
	//rotZ = Matrix4x4::rotateZ(a);
	//scal = Matrix4x4::scaling(10,1,1);
	a += 0.01F;
	vertex[0] = vertex1* scal* rotX*rotY*rotZ* translate* camera;
	vertex[1] = vertex2* scal* rotX*rotY*rotZ* translate* camera;
	vertex[2] = vertex3* scal* rotX*rotY*rotZ* translate* camera;

	for (int i = 0; i < 3; i++) {
		drawLine(vertex[i].x,vertex[i].y,vertex[(i+1)%3].x,vertex[(i+1)%3].y,3,Color(1,1,1));
	}
    env.end();
  }
}
