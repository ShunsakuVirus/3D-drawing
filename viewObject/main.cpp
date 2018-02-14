#include "lib/framework.hpp"
#include "GameObject.h"
#include "UI.h"
#include <ctime>

#define PI 3.141592653589793

enum Size {
	WIDTH = 1920,
	HEIGHT = 1080
};

int main() {
	AppEnv env(Size::WIDTH, Size::HEIGHT, Screen::DEFAULT);
	Vec2i wndPos(env.windowPosition());
	env.windowPosition(Vec2i(wndPos.x(),wndPos.y()+30));

	Random dice;
	dice.setSeed(std::time(nullptr));

	Matrix4x4 camera;
	Matrix4x4 pers;
	pers = Matrix4x4::perspective(degToRad(60.0F), WIDTH, HEIGHT, 1.0F, 1000.0F);

	Rect rect[100];
	Box box[1000];
	Line line[500];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int num = 10 * i + j;
			rect[num].Translate(i - 5, 0, j - 5);
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				int num = k * 100 + i * 10 + j;
				box[num].SetLocalPosition(-0.5F, -0.5F, -0.5F);
				box[num].Translate(-10 + i * 2, -10 + j * 2, -10 + k * 2);
			}
		}
	}

	float rain_speed[500];
	float rain_dy[500];
	float rain_len[500];
	Vector3 rain_sp[500];
	for (int i = 0; i < elemsof(line); i++) {
		rain_speed[i] = dice(0.8F, 1.0F);
		rain_len[i] = dice(0.1F,0.5F);
		rain_sp[i].x = dice(-25.0F,25.0F);
		rain_sp[i].y = dice(50.0F, 100.0F);
		rain_sp[i].z = dice(-25.0F, 25.0F);
		rain_dy[i] = rain_sp[i].y;
		line[i].Scaling(1.0F,rain_len[i],1.0F);
		line[i].Translate(rain_sp[i].x, rain_sp[i].y, rain_sp[i].z);
	}


	Font font("res/Consolas.ttf");
	
	float a = 0;
	Vector2 nowMouse;
	Vector2 prevMouse;
	Vector2 mouseAxis;
	Vector2 mouse(1.0F,0.5F);

	Vector3 pos;
	Vector3 cameraForward;
	Vector3 cameraRight;
	Vector3 cameraUp;
	Vector3 cameraPos;

	bool isRain = false;
	bool isBox1000 = false;


	Button exit(-WIDTH/2, HEIGHT/2-53, 100, 50, env.viewSize());
	Button creativeMode(-WIDTH/2 + 102,HEIGHT/2-53,130,50,env.viewSize());
	Button rain(-WIDTH/2 + 232, HEIGHT/2-53,130,50,env.viewSize());
	Button box1000(-WIDTH/2 + 362,HEIGHT/2-53,130,50,env.viewSize());

	while (env.isOpen()) {
		env.begin();
		a += 0.01F;
		nowMouse = Vector2(env.mousePosition().x(), env.mousePosition().y());

		mouseAxis = nowMouse - prevMouse;
		mouseAxis = mouseAxis / Vector2(1000, 1000);
		prevMouse = nowMouse;
		if (env.isButtonPressing(Mouse::RIGHT)) {
			mouse = mouse + mouseAxis;
			if (mouse.y > 0.999999F) mouse.y = 0.999999F;
			if (mouse.y < 0.000001F) mouse.y = 0.000001F;
		}
		pos.x = std::sin(mouse.y*PI)*std::cos(mouse.x*PI);
		pos.y = -std::cos(mouse.y*PI);
		pos.z = -std::sin(mouse.y*PI)*std::sin(mouse.x*PI);

		camera = Matrix4x4::camera(cameraPos, cameraPos + Vector3(pos.x, pos.y, pos.z), Vector3(0, 1, 0));

		cameraForward = Vector3(pos.x, pos.y, pos.z).normalized();
		cameraRight = Vector3::cross(Vector3(0,1,0), cameraForward).normalized();
		cameraUp = Vector3::cross(cameraForward, cameraRight).normalized();

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
			cameraPos = cameraPos + cameraUp/10;
		}
		if (env.isKeyPressing('Q')) {
			cameraPos = cameraPos - cameraUp/10;
		}
		for (int i = 0; i < 10;i++) {
			for (int j = 0; j < 10;j++) {
				int num = 10 * i + j;
				rect[num].Translate(i-5,0,j-5);
				rect[num].Draw(Color(1,1,1,0.5), camera, pers);
			}
		}
		if (isBox1000) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					for (int k = 0; k < 10; k++) {
						int num = k * 100 + i * 10 + j;
						box[num].Rotation(a + num, a + num, a + num);
						box[num].Draw(color256(i * 25, j * 25, k * 25), camera, pers);
					}
				}
			}
		}
		if (isRain) {
			for (int i = 0; i < elemsof(line);i++) {
				if (line[i].y < -1.0F) {
					rain_speed[i] = dice(0.5F, 1.0F);
					rain_len[i] = dice(0.1F, 0.5F);
					rain_sp[i].x = dice(-25.0F, 25.0F);
					rain_sp[i].y = dice(50.0F, 100.0F);
					rain_sp[i].z = dice(-25.0F, 25.0F);
					rain_dy[i] = rain_sp[i].y;
					line[i].Scaling(1.0F, rain_len[i], 1.0F);
					line[i].Translate(rain_sp[i].x, rain_sp[i].y, rain_sp[i].z);
				}
				rain_dy[i] -= rain_speed[i];
				line[i].Translate(rain_sp[i].x, rain_dy[i],rain_sp[i].z); 
				line[i].Draw(Color::white, camera, pers);
			}
		}

#pragma region UI
		if (exit.onClick(env.mousePosition(), env.isButtonPushed(Mouse::LEFT))) {
			break;
		}
		if (rain.onClick(env.mousePosition(), env.isButtonPushed(Mouse::LEFT))) {
			isRain = !isRain;
		}
		if (box1000.onClick(env.mousePosition(),env.isButtonPushed(Mouse::LEFT))) {
			isBox1000 = !isBox1000;
		}
		exit.Draw(font, "EXIT", 30, Color::white, Color::white, NOT_FILL, CENTER, env.viewSize());
		creativeMode.Draw(font, "CREATE", 30, Color::white, Color::white, NOT_FILL, CENTER, env.viewSize());
		rain.Draw(font, "RAIN", 30, Color::white, Color::white, NOT_FILL, CENTER, env.viewSize());
		box1000.Draw(font, "BOXES", 30, Color::white, Color::white, NOT_FILL, CENTER, env.viewSize());

#pragma endregion
		env.end();
	}
}