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
float shakeDecay = 0.01F;
float shakeIntensity;
float coefShakeIntensity = 0.5F;
void CameraShake() {
	shakeIntensity = coefShakeIntensity;
}
Rect ground[100];
Box boxes[1000];
Line rain[500];
float rain_speed[500];
float rain_dy[500];
float rain_len[500];
Vector3 rain_sp[500];
Circle snow[800];
float snow_speed[800];
float snow_y[800];
float snow_z[800];
float snow_x[800];
Vector3 snow_sp[800];
float snow_quake[800];

int main() {
	AppEnv env(Size::WIDTH, Size::HEIGHT, Screen::DEFAULT);
	Vec2i wndPos(env.windowPosition());
	env.windowPosition(Vec2i(wndPos.x(),wndPos.y()+30));

	Random dice;
	dice.setSeed(std::time(nullptr));

	float _time = 0.0F;

	Camera camera;
	camera.projection(degToRad(60.0F), WIDTH*2, HEIGHT*2, 1.0F, 1000.0F);

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
	for (int i = 0; i < 800;i++) {
		snow[i].size = dice(1.0F,3.0F);
		snow_speed[i] = dice(0.2F, 1.0F);
		snow_sp[i].x = dice(-50.0F, 50.0F);
		snow_sp[i].y = dice(50.0F, 100.0F);
		snow_sp[i].z = dice(-50.0F, 50.0F);
		snow_y[i] = snow_sp[i].y;
		snow_x[i] = snow_sp[i].x;
		snow_z[i] = snow_sp[i].z;
		snow_quake[i] = dice(-0.2F,0.2F);
		snow[i].Translate(snow_sp[i].x, snow_sp[i].y, snow_sp[i].z);
	}

	Font font("res/Consolas.ttf");
	
	float _theta = 0;
	Vector2 nowMouse;
	Vector2 prevMouse;
	Vector2 mouseAxis;
	Vector2 mouse(1.0F,0.5F);

	Vector3 pos(-1.0F,0.0F,0.0F);
	Vector3 cameraPos;


	bool isRain = false;
	bool isBox1000 = false;
	bool isCreative = false;

	float timeScale = 1.0F;
	int say_theWorldTime = 100;
	bool isSlowdown = false;
	bool doCamShake = false;

	int doremiInterval = 10;
	int doremiCount = 0;

	bool isFirework = false;

	bool isSnow = false;


	Button ui_exit			(-WIDTH/2,		HEIGHT/2-53,50,50,env.viewSize());
	Button ui_creative		(-WIDTH/2 + 52, HEIGHT/2-53,65,50,env.viewSize());
	Button ui_rain			(-WIDTH/2 + 119,HEIGHT/2-53,65,50,env.viewSize());
	Button ui_boxes			(-WIDTH/2 + 186,HEIGHT/2-53,65,50,env.viewSize());
	Button ui_clock			(-WIDTH/2 + 253,HEIGHT/2-53,65,50,env.viewSize());
	Button ui_firework		(-WIDTH/2 + 320,HEIGHT/2-53,75,50,env.viewSize());
	Button ui_snow			(-WIDTH/2 + 397,HEIGHT/2-53,65,50,env.viewSize());

	Color ui_color[7];
	for (int i = 0; i < elemsof(ui_color);i++) {
		ui_color[i] = Color::white;
	}

	Media se_clockS("res/clockS.wav"); se_clockS.looping(false); se_clockS.gain(1.0F);
	Media se_clockE("res/clockE.wav"); se_clockE.looping(false);
	Media se_rain("res/rain.wav"); se_rain.looping(true);
	Media se_do("res/piano_do.wav"); se_do.looping(false);
	Media se_re("res/piano_re.wav"); se_re.looping(false);
	Media se_mi("res/piano_mi.wav"); se_mi.looping(false);
	Media se_fa("res/piano_fa.wav"); se_fa.looping(false);
	Media se_so("res/piano_so.wav"); se_so.looping(false);
	Media se_ra("res/piano_ra.wav"); se_ra.looping(false);
	Media se_si("res/piano_si.wav"); se_si.looping(false);
	Media se_pianoall("res/piano_all.wav"); se_pianoall.looping(false);
	Media se_snow("res/snow.wav"); se_snow.looping(true); se_snow.gain(0.5F);
	Media se_wind("res/wind.wav"); se_wind.looping(true);
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
		if (shakeIntensity > 0.0F) {
			cameraPos = cameraPos + Vector3(dice(-1.0F, 1.0F), dice(-1.0F, 1.0F), dice(-1.0F, 1.0F)).normalized()*shakeIntensity;
			shakeIntensity -= shakeDecay;
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
				ground[10 * i + j].Draw(Color(0.6F,0.6F,0.6F), camera);
			}
		}
#pragma endregion

		if (env.isKeyPushed('X')) {
			doCamShake = !doCamShake;
		}
		if (isSlowdown) {
			say_theWorldTime--;
			if (say_theWorldTime == 0) { 
				_time = 0.0F;
				if (doCamShake) {
					coefShakeIntensity = 0.8F;
					CameraShake();
				}
				if (se_rain.isPlaying()) {
					se_rain.stop();
				}
				if (se_snow.isPlaying()) {
					se_snow.pause();
				}
				if (se_wind.isPlaying()) {
					se_wind.stop();
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
			bool ismouseover = false;
			doremiInterval--;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					for (int k = 0; k < 10; k++) {
						int num = k * 100 + i * 10 + j;
						if (!ismouseover) {
							float minx = 0.0F, maxx = 0.0F;
							float miny = 0.0F, maxy = 0.0F;
							minx = std::min({ boxes[num].vtx[0].x,boxes[num].vtx[1].x, boxes[num].vtx[2].x, boxes[num].vtx[3].x,
								boxes[num].vtx[4].x, boxes[num].vtx[5].x, boxes[num].vtx[6].x, boxes[num].vtx[7].x });
							maxx = std::max({ boxes[num].vtx[0].x,boxes[num].vtx[1].x, boxes[num].vtx[2].x, boxes[num].vtx[3].x,
								boxes[num].vtx[4].x, boxes[num].vtx[5].x, boxes[num].vtx[6].x, boxes[num].vtx[7].x });
							miny = std::min({ boxes[num].vtx[0].y,boxes[num].vtx[1].y, boxes[num].vtx[2].y, boxes[num].vtx[3].y,
								boxes[num].vtx[4].y, boxes[num].vtx[5].y, boxes[num].vtx[6].y, boxes[num].vtx[7].y });
							maxy = std::max({ boxes[num].vtx[0].y,boxes[num].vtx[1].y, boxes[num].vtx[2].y, boxes[num].vtx[3].y,
								boxes[num].vtx[4].y, boxes[num].vtx[5].y, boxes[num].vtx[6].y, boxes[num].vtx[7].y });
							if (nowMouse.x > minx && nowMouse.x < maxx &&
								nowMouse.y > miny && nowMouse.y < maxy &&
								boxes[num].vtx[0].z < 1.0F && boxes[num].vtx[0].z >= 0.1F &&
								boxes[num].vtx[1].z < 1.0F && boxes[num].vtx[1].z >= 0.1F &&
								boxes[num].vtx[2].z < 1.0F && boxes[num].vtx[2].z >= 0.1F &&
								boxes[num].vtx[3].z < 1.0F && boxes[num].vtx[3].z >= 0.1F &&
								boxes[num].vtx[4].z < 1.0F && boxes[num].vtx[4].z >= 0.1F &&
								boxes[num].vtx[5].z < 1.0F && boxes[num].vtx[5].z >= 0.1F &&
								boxes[num].vtx[6].z < 1.0F && boxes[num].vtx[6].z >= 0.1F &&
								boxes[num].vtx[7].z < 1.0F && boxes[num].vtx[7].z >= 0.1F &&
								doremiInterval <= 0) {
								if (isSlowdown) {
									doremiCount++;
								}
								else {
									int rand = dice(0,6);
									switch (rand) {
									case 0: {
										se_do.play();
										break;
									}
									case 1: {
										se_re.play();
										break;
									}
									case 2: {
										se_mi.play();
										break;
									}
									case 3: {
										se_fa.play();
										break;
									}
									case 4: {
										se_so.play();
										break;
									}
									case 5: {
										se_ra.play();
										break;
									}
									default: {
										se_si.play();
										break;
									}
									}
									ismouseover = true;
									doremiInterval = 15;
								}
							}
						}
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
			if (dice(0.1F,1.0F) < 0.2F) {
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

		if (isSnow) {
			for (int i = 0; i < 800; i++) {
				if (snow[i].y < -1.0F) {
					snow[i].size = dice(1.0F, 3.0F);
					snow_speed[i] = dice(0.2F, 1.0F);
					snow_sp[i].x = dice(-50.0F, 50.0F);
					snow_sp[i].y = dice(50.0F, 100.0F);
					snow_sp[i].z = dice(-50.0F, 50.0F);
					snow_y[i] = snow_sp[i].y;
					snow_x[i] = snow_sp[i].x;
					snow_z[i] = snow_sp[i].z;
					snow_quake[i] = dice(-0.3F, 0.3F);
					snow[i].Translate(snow_sp[i].x, snow_sp[i].y, snow_sp[i].z);
				}
				snow_y[i] -= snow_speed[i] * timeScale;
				snow_x[i] += snow_quake[i] * timeScale;
				snow_z[i] += snow_quake[i] * timeScale;
				snow[i].Translate(snow_x[i], snow_y[i], snow_z[i]);
				snow[i].Draw(Color::white, camera);
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
					if (doCamShake) {
						coefShakeIntensity = 0.3F;
						CameraShake();
					}
					if(isRain) se_rain.play();
					if (isSnow) {
						se_snow.play();
						se_wind.play();
					}
					ui_color[4] = Color::white;
					if (doremiCount > 0) {
						se_pianoall.play();
					}
					doremiCount = 0;
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
			if (ui_snow.mouseOver(env.mousePosition())) {
				isSnow = !isSnow;
				if (isSnow) {
					if (!isSlowdown) {
						se_snow.play();
						se_wind.play();
					}
					ui_color[6] = Color::lime;
				}
				else {
					se_snow.pause();
					se_wind.stop();
					ui_color[6] = Color::white;
				}
			}
		}
		ui_exit.Draw(font, "EXIT", 30, ui_color[0], ui_color[0], NOT_FILL, CENTER, env.viewSize());
		ui_creative.Draw(font, "CREATE", 30, ui_color[1], ui_color[1], NOT_FILL, CENTER, env.viewSize());
		ui_rain.Draw(font, "RAIN", 30, ui_color[2], ui_color[2], NOT_FILL, CENTER, env.viewSize());
		ui_boxes.Draw(font, "BOXES", 30, ui_color[3], ui_color[3], NOT_FILL, CENTER, env.viewSize());
		ui_clock.Draw(font, "CLOCK", 30, ui_color[4], ui_color[4], NOT_FILL, CENTER, env.viewSize());
		ui_firework.Draw(font, "FIREWORK", 30, ui_color[5], ui_color[5], NOT_FILL, CENTER, env.viewSize());
		ui_snow.Draw(font, "SNOW", 30, ui_color[6], ui_color[6], NOT_FILL,CENTER,env.viewSize());

#pragma endregion

		_time = std::min(_time+0.01F, 1.0F);
		env.end();
	}
}