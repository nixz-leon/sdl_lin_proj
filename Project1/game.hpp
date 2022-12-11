#pragma once
#ifndef game_hpp
#define game_hpp
#include "SDL.h"
#include "CircObj.hpp"

class Game {
public:
	Game();
	~Game();
	
	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void addObj(CircOb::Obj ob);
	void handleEvents();
	void update(float frametime);
	void simplecompare();
	void advancedcompare();
	void DrawCircle(SDL_Renderer* renderer, CircOb::Obj circ);
	void render();
	void clean();
	void initcomparemat();
	void rangeassigment(std::vector<CircOb::Obj>& source, int maxdigit, int comp);
	void indexObjects();
	int getnextsquare(int number);
	bool running() { return isrunning; };
private:
	std::vector<std::vector<int>> lookupmatrix; // this is simply needed for faster look up times
	int sidelength;
	int max_x;
	int max_y;
	std::vector<CircOb::Obj> objects;
	int count = 0;
	bool isrunning;
	SDL_Window* window;
	SDL_Renderer* renderer;



};

#endif