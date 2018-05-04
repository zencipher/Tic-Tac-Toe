#ifndef Rect_h
#define Rect_h

//#include "App.cpp"
#include <string>
using namespace std;

class Rect {
public:
	float x, y, width, height;
	bool drawnOn;
	char drawnOnType;
	Rect(float x, float y, float width, float height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->drawnOn = false;
	}

	Rect() {
		this->x = 0;
		this->y = 0;
		this->width = 0;
		this->height = 0;
		this->drawnOn = false;
	}

	void setX(float x) {
		this->x = x;
	}
	float getX() const {
		return this->x;
	}
	void setY(float y) {
		this->y = y;
	}
	float getY() const {
		return y;
	}
	void setWidth(float width) {
		this->width = width;
	}
	float getWidth() const {
		return width;
	}
	void setHeight(float height) {
		this->height = height;
	}
	float getHeight() const {
		return height;
	}

	bool contains(float X,float Y) {
		if (Y < y && Y > (y - height) && X < (x + width) && X > x) {
			return true;
		}
		return false;
	}

};

#endif


