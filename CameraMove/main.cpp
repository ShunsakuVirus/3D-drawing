#include "lib/framework.hpp"
#include "GameObject.h"
#include "Matrix4x4.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"

#define PI 3.141592653589793

enum Size {
	WIDTH = 1000,
	HEIGHT = 1000
};

int main() {
	AppEnv env(Size::WIDTH, Size::HEIGHT);

	Matrix4x4 camera;
	Matrix4x4 pers;

	Box box[100];
	Rect rect;
	Triangle t;
	
	float a = 0;

	Vector2 nowMouse;
	Vector2 prevMouse;
	Vector2 mouseAxis;
	Vector2 mouse(1.0F,0.5F);

	Vector3 pos;
	Vector3 cameraForward;
	Vector3 cameraRight;
	Vector3 cameraPos;
	while (env.isOpen()) {
		env.begin();

		a += 0.01F;
		nowMouse = Vector2(env.mousePosition().x(), env.mousePosition().y());

		mouseAxis = nowMouse - prevMouse;
		mouseAxis = mouseAxis / Vector2(1000, 1000);
		prevMouse = nowMouse;
		if (env.isButtonPressing(Mouse::RIGHT)) {
			mouse = mouse + mouseAxis;
			if (mouse.y > 0.9F) mouse.y = 0.9F;
			if (mouse.y < 0.1F) mouse.y = 0.1F;
		}
		pos.x = std::sin(mouse.y * PI)*std::cos(mouse.x*PI);
		pos.y = -std::cos(mouse.y*PI);
		pos.z = -std::sin(mouse.y*PI)*std::sin(mouse.x*PI);

		camera = Matrix4x4::camera(cameraPos, cameraPos + Vector3(pos.x, pos.y, pos.z), Vector3(0, 1, 0));
		//camera = Matrix4x4::camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
		pers = Matrix4x4::perspective(degToRad(60.0F), WIDTH, HEIGHT, 1.0F, 1000.0F);

		cameraForward = Vector3(pos.x, pos.y, pos.z).normalized();
		cameraRight = Vector3::cross(Vector3(0,1,0), cameraForward);

		if (env.isKeyPressing('D')) {
			cameraPos = cameraPos + cameraRight/10;
		}
		if (env.isKeyPressing('A')) {
			cameraPos = cameraPos - cameraRight/10;
		}
		if (env.isKeyPressing('W')) {
			cameraPos = cameraPos + cameraForward/10;
		}
		if (env.isKeyPressing('S')) {
			cameraPos = cameraPos - cameraForward/10;
		}
		if (env.isKeyPressing('E')) {
			cameraPos.y += 0.1F;
		}
		if (env.isKeyPressing('Q')) {
			cameraPos.y -= 0.1F;
		}
		rect.Scaling(50,1,50);
		rect.SetLocalPosition(-0.5F,0.0F,-0.5F);
		rect.Draw(Color::white,WIDTH,HEIGHT,camera,pers);

		t.SetLocalPosition(-0.5F,0,0);
		t.Rotation(a,a,degToRad(90));
		t.Draw(Color::blue,WIDTH,HEIGHT,camera,pers);

		for (int i = 0; i < 10;i++) {
			for (int j = 0; j < 10;j++) {
				int num = i * 10 + j;
				box[num].SetLocalPosition(-0.5F, -0.5F, -0.5F);
				box[num].Rotation(a + num, a + num, a + num);
				box[num].Translate(-100 + num * 2, 0, 0);
				box[num].Draw(colorHSB(10*j/100.0F,10+i*10/100.0F,99/100.0F), WIDTH, HEIGHT, camera, pers);
			}
		}
		
		env.end();
	}
}