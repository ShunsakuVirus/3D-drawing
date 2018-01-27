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
	localVertex[0] = Vector4::Vector4(5, 0, 0, 1);
	localVertex[1] = Vector4::Vector4(-5, 0, 0, 1);
	localVertex[2] = Vector4::Vector4(0, 5, 0, 1);

	Vector4 lV2[8];
	lV2[0] = Vector4::Vector4(-1, -1, -1, 1);
	lV2[1] = Vector4::Vector4(-1, 1, -1, 1);
	lV2[2] = Vector4::Vector4(1, 1, -1, 1);
	lV2[3] = Vector4::Vector4(1, -1, -1, 1);
	lV2[4] = Vector4::Vector4(-1, -1, 1, 1);
	lV2[5] = Vector4::Vector4(-1, 1, 1, 1);
	lV2[6] = Vector4::Vector4(1, 1, 1, 1);
	lV2[7] = Vector4::Vector4(1, -1, 1, 1);

	Vector3 vertex[3];
	Vector3 vertex2[8];
	Matrix4x4 v2translate;
	Matrix4x4 v2scal;

	Matrix4x4 translate;
	Matrix4x4 rotX;
	Matrix4x4 rotY;
	Matrix4x4 rotZ;
	Matrix4x4 scal;
	float mx = 0;
	float mz = 0;
	while (env.isOpen()) {
		env.begin();
		Vector2 mouse = Vector2::Vector2(env.mousePosition().x(), env.mousePosition().y());
		camera = Matrix4x4::Camera(Vector3(mx, 0, mz), Vector3(mx+std::sin(mouse.x/200), mouse.y/200, mz + std::cos(mouse.x/200)), Vector3(0, 1, 0));
		pers = Matrix4x4::perspective(degToRad(60), WIDTH, HEIGHT, 1, 1000.0F);

		if (env.isKeyPressing('D')) {
			mx += 0.1F;
		}
		if (env.isKeyPressing('A')) {
			mx -= 0.1F;
		}
		if (env.isKeyPressing('W')) {
			mz += 0.1F;
		}
		if (env.isKeyPressing('S')) {
			mz -= 0.1F;
		}
		translate = Matrix4x4::translate(0, 0, 10);
		v2translate = Matrix4x4::translate(10, -10, 10);
		v2scal = Matrix4x4::scaling(5,5,5);
		//rotX = Matrix4x4::rotateX(a);
		//rotY = Matrix4x4::rotateY(a);
		//rotZ = Matrix4x4::rotateZ(a);
		//scal = Matrix4x4::scaling(10,1,1);
		//a += 0.01F;
		for (int i = 0; i < elemsof(localVertex); i++) {
			Vector4 work = localVertex[i] * scal* rotX*rotY*rotZ* translate* camera *pers;
			vertex[i] = Vector4::ScreenTransformation(work, WIDTH, HEIGHT);
			/*vertex[i] = Vector3::Vector3(work.x / work.w , work.y / work.w, work.z / work.w);
			vertex[i].x *= WIDTH / 2;
			vertex[i].y *= HEIGHT / 2;*/
		}
		for (int i = 0; i < elemsof(lV2); i++) {
			Vector4 work = lV2[i] *v2scal* v2translate*camera*pers;
			vertex2[i] = Vector4::ScreenTransformation(work, WIDTH, HEIGHT);
		}


		for (int i = 0; i < elemsof(vertex2)/2; i++) {
			drawLine(vertex2[i].x, vertex2[i].y, vertex2[(i + 1) % 4].x, vertex2[(i + 1) % 4].y, 3, Color(1, 0, 0));
			if (i+4==7) {
				drawLine(vertex2[i + 4].x, vertex2[i + 4].y, vertex2[4].x, vertex2[4].y, 3, Color(1, 0, 0));
			}
			else {
				drawLine(vertex2[i + 4].x, vertex2[i + 4].y, vertex2[(i + 4 + 1)].x, vertex2[(i + 4 + 1)].y, 3, Color(1, 0, 0));
			}
			drawLine(vertex2[i].x,vertex2[i].y, vertex2[i+4].x, vertex2[i+4].y, 3,Color(1,0,0));
		}
		for (int i = 0; i < elemsof(vertex); i++) {
			drawLine(vertex[i].x, vertex[i].y, vertex[(i + 1) % 3].x, vertex[(i + 1) % 3].y, 3, Color(1, 1, 1));
		}
		env.end();
	}
}