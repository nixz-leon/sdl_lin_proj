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
	int windowsize[2] = {2000, 1300};
	int numberofobjects;
	int initalv[2];
	std::cout << "how many objects: ";
	std::cin >> numberofobjects;
	std::cout << std::endl;
	std::cout << "X component of velocity: ";
	std::cin >> initalv[0];
	std::cout << std::endl;
	std::cout << "Y component of velocity: ";
	std::cin >> initalv[1];

	int iteamperrow = getnextsquare(numberofobjects);
	float spaceingx = windowsize[x_comp] / iteamperrow;
	float spaceingy = windowsize[y_comp] / iteamperrow;
	int positionx = spaceingx;
	int positiony = spaceingy;


	game = new Game();
	game->init("bloop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowsize[0], windowsize[1], false);
	while (numberofobjects > 0) {
		CircOb::Obj temp;
		CircOb::setVals(temp, "ob", positionx, positiony, initalv[0], initalv[1], rand() % 255, rand() % 255, rand() % 255);
		game->addObj(temp);
		if ((positionx + spaceingx + 20) >= windowsize[x_comp]) {
			positionx = spaceingx;
			positiony += spaceingy;
		}
		else {
			positionx += spaceingx;
		}
		initalv[0] += rand() % 10;
		initalv[1] += rand() % 10;
		numberofobjects--;
	}

	game->initcomparemat();
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