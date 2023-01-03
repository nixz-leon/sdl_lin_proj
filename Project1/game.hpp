#pragma once
#ifndef game_hpp
#define game_hpp
#include "SDL.h"
#include "Objects.hpp"
#include <thread>
#include "Filesystem.hpp"

struct index_con {
	int first;
	int second;
};

class Game {
public:
	Game();
	~Game();
	
	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void addObj(Circ ob);
	void addObjs(std::vector<Circ> list);
	void handleEvents();
	void update(float frametime);
	bool excute_eventlist(std::vector<index_con> vec, float timestep);
	void simplecompare(float timestep);
	void DrawCircle(SDL_Renderer* renderer, Circ circ);
	void render();
	void clean();
	bool running() { return isrunning; };
	inline std::vector<Circ>  returnobs() { return objects; };
private:
	int sidelength;
	int max_x;
	int max_y;
	int mousex;
	int mousey;
	std::vector<Circ> objects;
	std::vector<Circ> buttons;
	int count = 0;
	bool isrunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
int getnextsquare(int number);
#endif