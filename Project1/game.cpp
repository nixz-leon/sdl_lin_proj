#include "game.hpp"
/*
float clamp(float min, float current, float max) {
	if (current < min) {
		return min;
	}
	if (current > max) {
		return max;
	}

	return current;
}
*/

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen == true) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!... " << std::endl;

		window = SDL_CreateWindow(title, x, y, width, height, flags);
		max_x = width;
		max_y = height;
		if (window) {
			std::cout << "Window Created!.." << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created!.." << std::endl;
		}
		
		isrunning = true;
	}
	else {
		isrunning = false;
	}

}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isrunning = false;
		break;
	default:
		break;
	}
	

}

void Game::addObj(CircOb::Obj ob){
	objects.push_back(ob);
	collisionstatus.push_back(false);
}

void Game::update(float frametime) {
	int max = objects.size();
	for (int i = 0; i < max - 1; i++) {
		for (int j = i + 1; j < max; j++) {
			if (CircOb::checkforcollis(objects[i], objects[j], frametime)) {
				CircOb::circCollision(objects[i], objects[j], frametime);
			}
		}
	}
	for (int i = 0; i < max; i++) {
		CircOb::borderCollision(objects[i], 0, max_y, 0, max_x);
		CircOb::findpos(objects[i], frametime);
	}
}

void Game::DrawCircle(SDL_Renderer* renderer, CircOb::Obj circ){
	SDL_SetRenderDrawColor(renderer, circ.color[0], circ.color[1], circ.color[2], circ.color[3]);
	for (int w = 0; w < circ.radius * 2; w++)
	{
		for (int h = 0; h < circ.radius * 2; h++)
		{
			int dx = (int)circ.radius - w; // horizontal offset
			int dy = (int)circ.radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (circ.radius * circ.radius))
			{
				SDL_RenderDrawPoint(renderer, circ.position[x_comp] + dx, circ.position[y_comp] + dy);
			}
		}
	}

}


void Game::render() {
	SDL_RenderClear(renderer);

	for (int i = 0; i < objects.size(); i++) {
		DrawCircle(renderer, objects[i]);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderPresent(renderer);

}




void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

