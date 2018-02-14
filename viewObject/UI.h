#pragma once
#include"lib/graph.hpp"
#include"lib/font.hpp"

enum Background {
	FILL = 0,
	NOT_FILL = 1,
	NO_FRAME = 2
};

enum HowToDisplay {
	CENTER = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 3,
	BOTTOM = 4
};

struct Button {
	float x;
	float y;
	float w;
	float h;
	Vec2f screenSize;
	bool fitScreenSize;

	Button();
	Button(float _x, float _y, float _w, float _h);
	Button(float _x, float _y, float _w, float _h, Vec2f _screenSize);

	void Draw(Font font, std::string text, 
		int fontSize, Color fontColor, Color buttonColor, 
		Background pattern,
		HowToDisplay fontPos,
		Vec2f screenSize);

	bool onClick(Vec2f mouse,bool isClicked);
	bool mouseOver(Vec2f mouse);

private:
	float xraito;
	float yraito;
	float wraito;
	float hraito;
	float fitx;
	float fity;
	float fitw;
	float fith;
};