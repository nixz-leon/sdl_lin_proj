#include "Game.hpp"
#include <cstdlib>

Game* game = nullptr;
//All the math is contained in CircObj.cpp, to find and adjust radius go to circObj.hpp
int main(int argc, char* argv[]) {
	const int FPS = 144;
	const int frameDelay = 1000 / FPS;
	const float SPF = 0.00694444444f;

	Uint32 frameStart;
	int frameTime;
	int windowsize[2] = {2400, 1350};
	int numberofobjects;
	float rad;
	float initalv[2];
	std::cout << "how many objects: ";
	std::cin >> numberofobjects;
	std::cout << std::endl;
	std::cout << "Radius: ";
	std::cin >> rad;
	std::cout << std::endl;
	std::cout << "X component of velocity: ";
	std::cin >> initalv[0];
	std::cout << std::endl;
	std::cout << "Y component of velocity: ";
	std::cin >> initalv[1];
	int iteamperrow = getnextsquare(numberofobjects);
	float spaceingx = windowsize[0] / iteamperrow;
	float spaceingy = windowsize[1] / iteamperrow;
	int positionx = spaceingx/2;
	int positiony = spaceingy/2;
	int row_trakcer = 0;
	float range = (initalv[0] + initalv[1]) / 2;
	float minxv = initalv[0] - range;
	float minyv = initalv[1] - range;


	game = new Game();
	game->init("bloop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowsize[0], windowsize[1], false);
	while (numberofobjects > 0) {
		numberofobjects--;
		int colorvec[3] = { rand() % 255, rand() % 255, rand() % 255 };
		float posvec[2] = { positionx, positiony };
		float accelvec[2] = { 0,0 };
		Circ temp = Circ("ob", colorvec, rad, posvec, initalv, accelvec);
		game->addObj(temp);
		if (row_trakcer == iteamperrow-1) {
			positionx = spaceingx/2;
			positiony += spaceingy;
			row_trakcer = 0;
		}
		else {
			positionx += spaceingx;
			row_trakcer++;
		}
		initalv[0] = minxv + (rand() % (int)range);
		initalv[1] = minyv + (rand() % (int)range);
	}

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update(SPF);
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}
	game->clean();
	return 0;
}