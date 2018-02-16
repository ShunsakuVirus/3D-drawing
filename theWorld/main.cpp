#include "lib/framework.hpp"
#include "GameObject.h"
#include "UI.h"
#include <vector>
#include "easing.h"

#define PI 3.141592653589793

enum Size {
	WIDTH = 960,
	HEIGHT = 540
};

int main() {
	AppEnv env(Size::WIDTH, Size::HEIGHT, Screen::DEFAULT);
	Vec2i wndPos(env.windowPosition());
	env.windowPosition(Vec2i(wndPos.x(),wndPos.y()+30));

	Random dice;
	dice.setSeed(std::time(nullptr));

	float _time = 0.0F;

	Camera camera;
	camera.projection(degToRad(60.0F), WIDTH*2, HEIGHT*2, 1.0F, 1000.0F);

	Rect ground[100];
	Box boxes[1000];
	Line rain[500];


	std::vector<Box> player_box;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int num = 10 * i + j;
			ground[num].Translate(i - 5, 0, j - 5);
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				int num = k * 100 + i * 10 + j;
				boxes[num].SetLocalPosition(-0.5F, -0.5F, -0.5F);
				boxes[num].Translate(-10 + i * 2, -10 + j * 2, -10 + k * 2);
			}
		}
	}

	float rain_speed[500];
	float rain_dy[500];
	float rain_len[500];
	Vector3 rain_sp[500];
	for (int i = 0; i < elemsof(rain); i++) {
		rain_speed[i] = dice(0.8F, 3.0F);
		rain_len[i] = dice(0.1F,0.5F);
		rain_sp[i].x = dice(-25.0F,25.0F);
		rain_sp[i].y = dice(50.0F, 100.0F);
		rain_sp[i].z = dice(-25.0F, 25.0F);
		rain_dy[i] = rain_sp[i].y;
		rain[i].Scaling(1.0F,rain_len[i],1.0F);
		rain[i].Translate(rain_sp[i].x, rain_sp[i].y, rain_sp[i].z);
	}

	Font font("res/Consolas.ttf");
	
	float _theta = 0;
	Vector2 nowMouse;
	Vector2 prevMouse;
	Vector2 mouseAxis;
	Vector2 mouse(1.0F,0.5F);

	Vector3 pos(0.0F,0.0F,1.0F);
	Vector3 cameraPos;

	bool isRain = false;
	bool isBox1000 = false;
	bool isCreative = false;

	float timeScale = 1.0F;
	int say_theWorldTime = 100;
	bool isSlowdown = false;

	bool isFirework = false;


	Button ui_exit			(-WIDTH/2,		HEIGHT/2-53,50,50,env.viewSize());
	Button ui_creative		(-WIDTH/2 + 52, HEIGHT/2-53,65,50,env.viewSize());
	Button ui_rain			(-WIDTH/2 + 119,HEIGHT/2-53,65,50,env.viewSize());
	Button ui_boxes			(-WIDTH/2 + 186,HEIGHT/2-53,65,50,env.viewSize());
	Button ui_clock			(-WIDTH/2 + 253,HEIGHT/2-53,65,50,env.viewSize());
	Button ui_firework		(-WIDTH/2 + 320,HEIGHT/2-53,75,50,env.viewSize());

	Color ui_color[6];
	for (int i = 0; i < elemsof(ui_color);i++) {
		ui_color[i] = Color::white;
	}

	Media se_clockS("res/clockS.wav"); se_clockS.looping(false);
	Media se_clockE("res/clockE.wav"); se_clockE.looping(false);
	Media se_rain("res/rain.wav"); se_rain.looping(true);




	std::list<Firework> fireworks;


	while (env.isOpen()) {
		env.begin();
		_theta += 0.01F;

#pragma region camera processing

		nowMouse = Vector2(env.mousePosition().x(), env.mousePosition().y());

		mouseAxis = nowMouse - prevMouse;
		mouseAxis = mouseAxis / Vector2(1000, 1000);
		prevMouse = nowMouse;
		if (env.isButtonPressing(Mouse::RIGHT)) {
			mouse = mouse + mouseAxis;
			if (mouse.y > 0.999999F) mouse.y = 0.999999F;
			if (mouse.y < 0.000001F) mouse.y = 0.000001F;
			pos.x = std::sin(mouse.y*PI)*std::cos(mouse.x*PI);
			pos.y = -std::cos(mouse.y*PI);
			pos.z = -std::sin(mouse.y*PI)*std::sin(mouse.x*PI);
		}

		camera.cameraMatrix(cameraPos, cameraPos + Vector3(pos.x, pos.y, pos.z), Vector3(0, 1, 0));

		if (env.isKeyPressing(KEY_LEFT_SHIFT)) {
			if (env.isKeyPressing('D')) {
				cameraPos = cameraPos + camera.right;
			}
			if (env.isKeyPressing('A')) {
				cameraPos = cameraPos - camera.right;
			}
			if (env.isKeyPressing('W')) {
				cameraPos = cameraPos + camera.forward;
			}
			if (env.isKeyPressing('S')) {
				cameraPos = cameraPos - camera.forward;
			}
			if (env.isKeyPressing('E')) {
				cameraPos = cameraPos + camera.up;
			}
			if (env.isKeyPressing('Q')) {
				cameraPos = cameraPos - camera.up;
			}
		}
		else {
			if (env.isKeyPressing('D')) {
				cameraPos = cameraPos + camera.right / 10;
			}
			if (env.isKeyPressing('A')) {
				cameraPos = cameraPos - camera.right / 10;
			}
			if (env.isKeyPressing('W')) {
				cameraPos = cameraPos + camera.forward / 10;
			}
			if (env.isKeyPressing('S')) {
				cameraPos = cameraPos - camera.forward / 10;
			}
			if (env.isKeyPressing('E')) {
				cameraPos = cameraPos + camera.up / 10;
			}
			if (env.isKeyPressing('Q')) {
				cameraPos = cameraPos - camera.up / 10;
			}
		}
#pragma endregion
#pragma region ground processing

		for (int i = 0; i < 10;i++) {
			for (int j = 0; j < 10;j++) {
				ground[10 * i + j].Draw(Color(1,1,1,0.5), camera);
			}
		}
#pragma endregion

		if (isSlowdown) {
			say_theWorldTime--;
			if (say_theWorldTime == 0) { 
				_time = 0.0F;
				if (se_rain.isPlaying()) {
					se_rain.stop();
				}
			}
			if (say_theWorldTime <= 0) {
				timeScale = EasingQuartOut(_time, 1.0F, 0.0F);
			}
		}
		else {
			timeScale = EasingQuartIn(_time, 0.0F, 1.0F);
		}
		if (isBox1000) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					for (int k = 0; k < 10; k++) {
						int num = k * 100 + i * 10 + j;
						boxes[num].Rotation(_theta*timeScale + num, _theta*timeScale + num, _theta*timeScale + num);
						boxes[num].Draw(color256(i * 25, j * 25, k * 25), camera);
					}
				}
			}
		}
		if (isRain) {
			for (int i = 0; i < elemsof(rain); i++) {
				if (rain[i].y < -1.0F) {
					rain_speed[i] = dice(0.8F, 3.0F);
					rain_len[i] = dice(0.1F, 0.5F);
					rain_sp[i].x = dice(-25.0F, 25.0F);
					rain_sp[i].y = dice(50.0F, 100.0F);
					rain_sp[i].z = dice(-25.0F, 25.0F);
					rain_dy[i] = rain_sp[i].y;
					rain[i].Scaling(1.0F, rain_len[i], 1.0F);
					rain[i].Translate(rain_sp[i].x, rain_sp[i].y, rain_sp[i].z);
				}
				rain_dy[i] -= rain_speed[i]*timeScale;
				rain[i].Translate(rain_sp[i].x, rain_dy[i], rain_sp[i].z);
				rain[i].Draw(Color::white, camera);
			}
		}

		if (isFirework) {
			if (dice(1.0F) < 0.2F) {
				fireworks.push_back(Firework(dice));
			}
			for (int i = 0; i < fireworks.size();i++) {
				auto ite = fireworks.begin();
				for (int j = 0; j < i; j++) {
					++ite;
				}
				Firework f = *ite;
				f.run(camera, dice);
				if (f.done()) {
					fireworks.erase(ite);
				}
			}
		}
		if (isCreative) {
			if (env.isKeyPushed('Z')) {
				player_box.push_back(Box());
			}
			for (auto itr = player_box.begin(); itr != player_box.end();++itr) {
				itr->Draw(Color::white,camera);
			}
		}

#pragma region UI processing

		if (env.isButtonPushed(Mouse::LEFT)) {
			if (ui_exit.mouseOver(env.mousePosition())) {
				break;
			}
			if (ui_creative.mouseOver(env.mousePosition())) {
				isCreative = !isCreative;
				if(isCreative)ui_color[1] = Color::lime;
				else ui_color[1] = Color::white;
			}
			if (ui_rain.mouseOver(env.mousePosition())) {
				isRain = !isRain;
				if (isRain) {
					if(!isSlowdown) se_rain.play();
					ui_color[2] = Color::lime;
				}
				else {
					se_rain.stop();
					ui_color[2] = Color::white;
				}
			}
			if (ui_boxes.mouseOver(env.mousePosition())) {
				isBox1000 = !isBox1000;
				if (isBox1000)ui_color[3] = Color::lime;
				else ui_color[3] = Color::white;
			}
			if (ui_clock.mouseOver(env.mousePosition())) {
				isSlowdown = !isSlowdown;
				_time = 0.0F;
				if (isSlowdown) {
					se_clockS.play();
					say_theWorldTime = 100;
					ui_color[4] = Color::lime;
				}
				else {
					se_clockE.play();
					if(isRain) se_rain.play();
					ui_color[4] = Color::white;
				}
			}
			if (ui_firework.mouseOver(env.mousePosition())) {
				isFirework = !isFirework;
				if (isFirework) {
					ui_color[5] = Color::lime;
				}
				else {
					ui_color[5] = Color::white;
				}
			}
		}
		ui_exit.Draw(font, "EXIT", 30, ui_color[0], ui_color[0], NOT_FILL, CENTER, env.viewSize());
		ui_creative.Draw(font, "CREATE", 30, ui_color[1], ui_color[1], NOT_FILL, CENTER, env.viewSize());
		ui_rain.Draw(font, "RAIN", 30, ui_color[2], ui_color[2], NOT_FILL, CENTER, env.viewSize());
		ui_boxes.Draw(font, "BOXES", 30, ui_color[3], ui_color[3], NOT_FILL, CENTER, env.viewSize());
		ui_clock.Draw(font, "CLOCK", 30, ui_color[4], ui_color[4], NOT_FILL, CENTER, env.viewSize());
		ui_firework.Draw(font, "FIREWORK", 30, ui_color[5], ui_color[5], NOT_FILL, CENTER, env.viewSize());

#pragma endregion

		_time = std::min(_time+0.01F, 1.0F);
		env.end();
	}
}