#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	const int FPS = 200;
	const int frameDelay = 1000 / FPS;
	const float SPF = 0.005f;

	Uint32 frameStart;
	int frameTime;

	CircOb::Obj circ1;
	CircOb::Obj circ2;
	CircOb::Obj circ3;
	CircOb::Obj circ4;
	CircOb::Obj circ5;
	CircOb::Obj circ6;
	CircOb::Obj circ7;
	CircOb::Obj circ8;
	CircOb::Obj circ9;
	CircOb::Obj circ10;
	CircOb::Obj circ11;
	CircOb::setVals(circ1, "green", 25, 25, 60, -600, 0, 255, 0);
	CircOb::setVals(circ2, "red", 75, 75, 200, 200, 255, 0, 0);
	CircOb::setVals(circ3, "blue", 125, 125, 600, -600, 0, 0, 255);
	CircOb::setVals(circ4, "black", 175, 175, -600, 600, 0, 0, 0);
	CircOb::setVals(circ5, "yellow", 225, 225, -600, 600, 255, 255, 0);
	CircOb::setVals(circ6, "cyan", 275, 275, -600, 600, 0, 255, 255);
	CircOb::setVals(circ7, "purple", 325, 325, -600, 600, 255, 0, 255);
	CircOb::setVals(circ8, "bloop1", 375, 375, -600, 600, 255, 150, 255);
	CircOb::setVals(circ9, "bloop2", 425, 425, -600, 600, 150, 255, 255);
	CircOb::setVals(circ10, "bloop3", 475, 475, -600, 600, 255, 255, 150);
	CircOb::setVals(circ11, "bloop4", 25, 75, -600, 600, 255, 120, 160);





	game = new Game();
	game->init("bloop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, false);
	game->addObj(circ1);
	game->addObj(circ2);
	game->addObj(circ3);
	game->addObj(circ4);
	game->addObj(circ5);
	game->addObj(circ6);
	game->addObj(circ7);
	game->addObj(circ8);
	game->addObj(circ9);
	game->addObj(circ10);
	game->addObj(circ11);
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