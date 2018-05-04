#ifndef App_hpp
#define App_hpp

#include <vector>

#include "GlutApp.h"
#include "Rect.h"

class player{
public:
	bool turn;
	bool winner = false;
	bool ai = false;
	static bool winnerHelp(Rect rect1, Rect rect2, Rect rect3);
	
};
class App : public GlutApp {
	// Maintain app state here
	float mx;
	float my;
	player player1;
	player player2;

public:
	// Constructor, to initialize state
	App(const char* label, int x, int y, int w, int h);

	// These are the events we want to handle
	void draw();
	void keyPress(unsigned char key);
	void mouseDown(float x, float y);
	void mouseDrag(float x, float y);
	void reset();
	void aiTurn();
};

class Board : public GlutApp {
public:
	static void drawBoard();

};

class square : public GlutApp {
public:
	static void drawX(Rect* rect);
	static void drawO(Rect*rect);
	static void generateBoard();
	bool isEmpty();
};


#endif
