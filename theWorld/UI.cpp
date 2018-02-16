#include "UI.h"

Button::Button() {
	this->x = 0.0F;
	this->y = 0.0F;
	this->w = 0.0F;
	this->h = 0.0F;
	this->screenSize = Vec2f(1920,1080);
	this->fitScreenSize = true;
}

Button::Button(float _x, float _y, float _w, float _h) {
	this->x = _x;
	this->y = _y;
	this->w = _w;
	this->h = _h;
	this->screenSize = Vec2f(0,0);
	this->fitScreenSize = false;
}
Button::Button(float _x, float _y, float _w, float _h, Vec2f _screenSize) {
	if (_screenSize.x() != 0 && _screenSize.y() != 0) {
		this->x = _x;
		this->y = _y;
		this->w = _w;
		this->h = _h;
		this->screenSize = _screenSize;
		this->fitScreenSize = true;
		this->xraito = (this->x / screenSize.x());
		this->yraito = (this->y / screenSize.y());
		this->wraito = (this->w / screenSize.x());
		this->hraito = (this->h / screenSize.y());
	}
	else {
		printf("Screen size '0' is invalid.");
		return;
	}
}

bool Button::onClick(Vec2f mouse, bool isClicked) {
	if (mouse.x() > this->fitx && mouse.x() < this->fitx+this->fitw &&
		mouse.y() > this->fity && mouse.y() < this->fity+this->fith &&
		isClicked) {
		return true;
	}
	return false;
}
bool Button::mouseOver(Vec2f mouse) {
	if (mouse.x() > this->fitx && mouse.x() < this->fitx + this->fitw &&
		mouse.y() > this->fity && mouse.y() < this->fity + this->fith) {
		return true;
	}
	return false;
}

void Button::Draw(Font font, std::string text, int fontSize, Color fontColor, Color buttonColor, Background pattern, HowToDisplay fontPos, Vec2f _screenSize) {
	if (this->fitScreenSize) {
		this->fitx = this->xraito*_screenSize.x();
		this->fity = this->yraito*_screenSize.y();
		this->fitw = this->wraito*_screenSize.x();
		this->fith = this->hraito*_screenSize.y();
		switch (pattern) {
		case FILL:
			drawFillBox(fitx, fity, fitw, fith, buttonColor);
			break;
		case NOT_FILL: {
			float x2 = fitx + fitw;
			float y2 = fity + fith;
			drawLine(fitx, fity, x2, fity, 3, buttonColor);
			drawLine(x2, fity, x2, y2, 3, buttonColor);
			drawLine(x2, y2, fitx, y2, 3, buttonColor);
			drawLine(fitx, y2, fitx, fity, 3, buttonColor);
		}
					   break;
		case NO_FRAME:
			break;
		}

		switch (fontPos) {
		case CENTER: {
			Vec2f size = font.drawSize(text);
			float _x = fitx + size.x() / 2.0F;
			float _y = fity + size.y() / 2.0F;
			float bx = fitx + fitw / 2.0F;
			float by = fity + fith / 2.0F;
			float diffx = bx - _x;
			float diffy = by - _y;
			Vec2f dispPos(fitx + diffx, fity + diffy);
			font.size(fontSize);
			font.draw(text, dispPos, fontColor);
			break;
		}
		default:
			break;
		}
	}
	else {
		return;
	}
}