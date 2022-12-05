#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	const float SPF = 0.01666666f;

	Uint32 frameStart;
	int frameTime;

	CircOb::Obj firstcirc;
	CircOb::setPos(firstcirc, 100, 300);
	CircOb::setVel(firstcirc, 60, -600);
	CircOb::Obj secondcirc;
	CircOb::setPos(secondcirc, 100, 100);
	CircOb::setVel(secondcirc, 0, 600);
	CircOb::setColor(secondcirc, 255, 0, 0, 2);


	game = new Game();
	game->init("bloop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, false);
	game->addObj(firstcirc);
	game->addObj(secondcirc);
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