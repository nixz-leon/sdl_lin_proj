#include "game.hpp"

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

void Game::addObj(Circ ob) {
	objects.push_back(ob);
}

void Game::addObjs(std::vector<Circ> list)
{
	objects = list;
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isrunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (objects[0].buttoncheck(mousex, mousey)) {
				objects[0].setpos(mousex, mousey);
			}
		default:
				break;
		}
	}
	

}

void Game::update(float frametime) {

	simplecompare(frametime / 2);
	//advancedcompare();
	SDL_GetMouseState(&mousex, &mousey);
	int max = objects.size();
	for (int i = 0; i < max; i++) {
		objects[i].updatepos(frametime);
	}
}


void Game::simplecompare(float timestep){
	int max = objects.size();
	for (int i = 0; i < max - 1; i++) {
		for (int j = i + 1; j < max; j++) {
			collisionevent(objects[i], objects[j], timestep);
		}
	}
	for (int i = 0; i < max; i++) {
		objects[i].edgecollision(0, max_x, 0, max_y);
	}
}

void Game::DrawCircle(SDL_Renderer* renderer, Circ circ){
	SDL_SetRenderDrawColor(renderer, circ.color[0], circ.color[1], circ.color[2], circ.color[3]);
	SDL_Point points[1255];
	int number = 0;
	for (int w = 0; w < circ.rad * 2; w++)
	{
		for (int h = 0; h < circ.rad * 2; h++)
		{
			int dx = (int)circ.rad - w; // horizontal offset
			int dy = (int)circ.rad - h; // vertical offset
			if ((dx * dx + dy * dy) <= (circ.rad * circ.rad))
			{
				points[number].x = circ.position[0] + dx;
				points[number].y = circ.position[1] + dy;
				//SDL_RenderDrawPoint(renderer, circ.position[x_comp] + dx, circ.position[y_comp] + dy);
				number++;
			}
		}
	}
	SDL_RenderDrawPoints(renderer, points, number - 1);
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


int getnextsquare(int number) {
	int temp = sqrt(number);
	if (temp * temp < number) {
		temp++;
	}
	return temp;
}

//now I need to impliment the algo that goes through the objects list and does the comparison to the 4 objects touching it.
