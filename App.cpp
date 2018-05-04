#include "App.h"
#include "Rect.h"
#include <vector>;
#include <string>;

std::vector<Rect*> list_of_rects;

App::App(const char* label, int x, int y, int w, int h) : GlutApp(label, x, y, w, h) {
	// Initialize state variables
	mx = 100.0;
	my = 100.0;

	//creates clickable squares
	square::generateBoard();
	
	player1.turn=true;

}

void square::drawX(Rect* rect) {
	
	glBegin(GL_LINES);
	glColor3f(0.3, 0, 0.2);

	glVertex2f(rect->getX(), rect->getY());
	glVertex2f(rect->getX() + rect->getWidth(), rect->getY() - rect->getHeight());
	glVertex2f(rect->getX(), rect->getY() - rect->getHeight());
	glVertex2f(rect->getX() + rect->getWidth(), rect->getY());

	glEnd();

}

void square::drawO(Rect* rect) {

	glBegin(GL_LINE_LOOP);
	glColor3f(0.3, 0.5, 0);
	for (int ii = 0; ii < 30; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(30);//get the current angle 

		float x = rect->getWidth()/2.5 * cosf(theta);//calculate the x component 
		float y = rect->getWidth() / 2.5 * sinf(theta);//calculate the y component 

		glVertex2f(x + rect->getX() + rect->getWidth() / 2, y - rect->getHeight() / 2 + rect->getY());//output vertex 

	}
	glEnd();
}

void Board::drawBoard() {
	glBegin(GL_LINES);
	glVertex2f(-0.3f, -0.9f);
	glVertex2f(-0.3f, 0.9f);

	glVertex2f(0.3f, -0.9f);
	glVertex2f(0.3f, 0.9f);

	glVertex2f(-0.9f, -0.3f);
	glVertex2f(0.9f, -0.3f);

	glVertex2f(0.9f, 0.3f);
	glVertex2f(-0.9f, 0.3f);

	glVertex2f(-0.9f, -0.9f);
	glVertex2f(-0.9f, 0.9f);

	glVertex2f(-0.9f, 0.9f);
	glVertex2f(0.9f, 0.9f);

	glVertex2f(0.9f, 0.9f);
	glVertex2f(0.9f, -0.9f);

	glVertex2f(0.9f, -0.9f);
	glVertex2f(-0.9f, -0.9f);

	glEnd();
}

void square::generateBoard() {

	list_of_rects.push_back(new Rect(-0.89, 0.89, 0.58, 0.58)); // [0]
	list_of_rects.push_back(new Rect(-0.29, 0.89, 0.58, 0.58)); // [1]
	list_of_rects.push_back(new Rect(0.31, 0.89, 0.58, 0.58));  // [2]
	list_of_rects.push_back(new Rect(-0.89, 0.29, 0.58, 0.58)); // [3]
	list_of_rects.push_back(new Rect(-0.29, 0.29, 0.58, 0.58)); // [4]
	list_of_rects.push_back(new Rect(0.31, 0.29, 0.58, 0.58));  // [5]
	list_of_rects.push_back(new Rect(-0.89, -0.31, 0.58, 0.58)); // [6]
	list_of_rects.push_back(new Rect(-0.29, -0.31, 0.58, 0.58)); // [7]
	list_of_rects.push_back(new Rect(0.31, -0.31, 0.58, 0.58));  // [8]

}

bool player::winnerHelp(Rect rect1, Rect rect2, Rect rect3) {
	if (rect1.drawnOnType == rect2.drawnOnType && rect2.drawnOnType == rect3.drawnOnType && rect1.drawnOn && rect2.drawnOn && rect3.drawnOn) {
		if (rect1.drawnOnType == 'x') {
			std::cout << "Player 1 Wins" <<endl;
		}
		else {
			std::cout << "Player 2 Wins" <<endl;
		}
		return true;
	}
	return false;
}


void App::draw() {
	//if (player2.turn && player2.ai) {
	//Sleep(1000);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set Color
	glColor3d(1.0, 1.0, 1.0);
	
	//draw the outline of the board
	Board::drawBoard();
	
	for (int i = 0; i < list_of_rects.size(); i++) {
		glColor3f(0, 0, 0);
		if (list_of_rects[i]->contains(mx,my) || list_of_rects[i]->drawnOn) {
			if (player1.turn && list_of_rects[i]->contains(mx, my) && !list_of_rects[i]->drawnOn){
				list_of_rects[i]->drawnOnType = 'x';
				list_of_rects[i]->drawnOn = true;
				player1.turn = false;
				player2.turn = true;
			}
			else if(player2.turn  && (list_of_rects[i]->contains(mx, my))&&!list_of_rects[i]->drawnOn) {
				list_of_rects[i]->drawnOnType = 'o';
				list_of_rects[i]->drawnOn = true;
				player2.turn = false;
				player1.turn = true;
			}
			if (list_of_rects[i]->drawnOnType == 'x'&&list_of_rects[i]->drawnOn)
				square::drawX(list_of_rects[i]);
			else if(list_of_rects[i]->drawnOnType == 'o'&&list_of_rects[i]->drawnOn)
				square::drawO(list_of_rects[i]);
		}

		if (player2.turn && player2.ai) {
			aiTurn();
			
		}
	}


	if (player::winnerHelp(*list_of_rects[0], *list_of_rects[1], *list_of_rects[2]) || player::winnerHelp(*list_of_rects[3], *list_of_rects[4], *list_of_rects[5]) || player::winnerHelp(*list_of_rects[6], *list_of_rects[7], *list_of_rects[8]) || player::winnerHelp(*list_of_rects[0], *list_of_rects[3], *list_of_rects[6]) || player::winnerHelp(*list_of_rects[1], *list_of_rects[4], *list_of_rects[7]) || player::winnerHelp(*list_of_rects[2], *list_of_rects[5], *list_of_rects[8]) || player::winnerHelp(*list_of_rects[0], *list_of_rects[4], *list_of_rects[8]) || player::winnerHelp(*list_of_rects[2], *list_of_rects[4], *list_of_rects[6])) {

		reset();
		if (player2.turn && player2.ai) {
			redraw();
		}
		
	}
	bool alldrawn = true;
	for (int i = 0; i < list_of_rects.size(); i++) {
		if (!list_of_rects[i]->drawnOn)
			alldrawn = false;

	}
	if (alldrawn) {
		std::cout << "It's a tie!" <<endl;
		reset();
		if (player2.turn && player2.ai) {
			redraw();
		}
	}



	glFlush();
	glutSwapBuffers();
}
void App::aiTurn() {
	for (int i = 0; i < list_of_rects.size(); i++) {
		if (!list_of_rects[i]->drawnOn) {
			list_of_rects[i]->drawnOn = true;
			list_of_rects[i]->drawnOnType = 'o';
			break;
		}
	}
	player2.turn = false;
	player1.turn = true;
}
void App::reset() {
	for (int i = 0; i < list_of_rects.size(); i++) {
		list_of_rects[i]->drawnOn = false;
		list_of_rects[i]->drawnOnType = NULL;
	}
	player1.turn = true;
	player2.turn = false;
	mx = 100.0;
	my = 100.0;
	//redraw();
}

void App::mouseDown(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	// Redraw the scene
	redraw();
}

void App::mouseDrag(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	// Redraw the scene
	redraw();
}

void App::keyPress(unsigned char key) {
	if (key == 27) {
		// Exit the app when Esc key is pressed
		exit(0);
	}
	if (key == 49) { // single player pressing '1'
		std::cout << "You selected 1 player" <<endl;
		App::reset();
		player2.ai = true;
		redraw();
		

	}
	if (key == 50) { // two players pressing '2'
		std::cout << "You selected 2 players" <<endl;
		App::reset();
		player2.ai = false;
		redraw();
	}
}
