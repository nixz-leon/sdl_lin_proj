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
}

void Game::simplecompare(){
	int max = objects.size();
	for (int i = 0; i < max - 1; i++) {
		for (int j = i + 1; j < max; j++) {
			if (CircOb::checkforcollis(objects[i], objects[j])) {
				CircOb::circCollision(objects[i], objects[j]);
			}
		}
	}
	for (int i = 0; i < max; i++) {
		CircOb::borderCollision(objects[i], 0, max_y, 0, max_x);
	}
}

void Game::advancedcompare()
{
	indexObjects();
	//std::cout << "start" << std::endl;
	//std::cout << lookupmatrix[0][0] << std::endl;
	for (int h = 0; h < lookupmatrix.size(); h++) {
		for (int j = 0; j < lookupmatrix[h].size(); j++) {
			//std::cout << lookupmatrix[h][j] << ',';
		}
		//std::cout << std::endl;
	}
	for (int i = 0; i < objects.size(); i++) {
		for (int h = 0; h < lookupmatrix.size(); h++) {
			for (int j = 0; j < lookupmatrix[h].size(); j++) {
				//std::cout << lookupmatrix[h][j] << ',';
			}
			//std::cout << std::endl;
		}
		int x_index = objects[i].comparindex[x_comp];
		int y_index = objects[i].comparindex[y_comp];
		if (x_index + 1 < lookupmatrix.size()) {
			//std::cout << 'x' << x_index << "+1" << std::endl;
			if (lookupmatrix[x_index + 1][y_index] != -1) {
				int lookupindex = lookupmatrix[x_index + 1][y_index];
				//std::cout << i << "compared to " << lookupindex << std::endl;
				CircOb::circCollision(objects[i], objects[lookupindex]);
			}
		}
		if ((x_index - 1 >= 0)) {
			//std::cout << 'x' << x_index << "-1" << std::endl;
			if (lookupmatrix[x_index - 1][y_index] != -1) {
				int lookupindex = lookupmatrix[x_index - 1][y_index];
				//std::cout << i << "compared to " << lookupindex << std::endl;
				CircOb::circCollision(objects[i], objects[lookupindex]);
			}
		}
		if (y_index + 1 < lookupmatrix[x_index].size()) {
			//std::cout << 'y' << y_index << "+1" << std::endl;
			if (lookupmatrix[x_index][y_index+1] != -1) {
				int lookupindex = lookupmatrix[x_index][y_index+1];
				//std::cout << i << "compared to " << lookupindex << std::endl;
				CircOb::circCollision(objects[i], objects[lookupindex]);
			}
		}
		if ((y_index - 1 > 0)) {
			//std::cout << 'y' << y_index << "-1" << std::endl;
			if (lookupmatrix[x_index][y_index-1] != -1) {
				int lookupindex = lookupmatrix[x_index][y_index-1];
				//std::cout << i << "compared to " << lookupindex << std::endl;
				CircOb::circCollision(objects[i], objects[lookupindex]);
			}
		}
		CircOb::borderCollision(objects[i], 0, max_y, 0, max_x);
		lookupmatrix[x_index][y_index] = -1;
	}
	//std::cout << "end" << std::endl;
}

void Game::update(float frametime) {
	
	simplecompare();
	//advancedcompare();
	int max = objects.size();
	for (int i = 0; i < max; i++) {
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

void Game::initcomparemat()
{
	//currently we will be looking to make a square matrix
	int elms = getnextsquare(objects.size());
	for (int i = 0; i < elms; i++) {
		std::vector<int> temp;
		for (int j = 0; j < elms; j++) {
			temp.push_back(-1);
		}
		lookupmatrix.push_back(temp);
	}
	sidelength = elms;
}

int getdigatpos(float number, int pos) {
	int temp = (int)number;
	int mod = 10;
	int divsor = pow(10, pos);
	return (temp / divsor) % mod;
}

void Game::rangeassigment(std::vector<CircOb::Obj>& source, int maxdigit, int comp)
{
	std::vector<CircOb::Obj>temp;
	for (int i = 0; i < source.size(); i++) {
		temp.push_back(source[i]);
	}
	for (int i = 0; i < maxdigit; i++) {
		std::vector<std::vector<CircOb::Obj>> buckets(10);
		for (int j = 0; j < temp.size(); j++) {
			int val = getdigatpos(temp[j].position[comp], i);
			buckets[val].push_back(temp[j]);
		}
		int index = 0;
		for (int k = 0; k < buckets.size(); k++) {
			for (int l = 0; l < buckets[k].size(); l++) {
				temp[index] = buckets[k][l];
				index++;
			}
		}
		buckets.clear();
	}
	int index = 0;
	for (int i = 0; i < temp.size(); i++) {
		std::cout << temp[i].position[y_comp] << std::endl;// change the default state on the objects check to false, and from there i can set it to true later on
		source[i] = temp[i];
		source[i].comparindex[comp] = index;
		if (i % sidelength == sidelength - 1) {
			index++;
		}
	}
	temp.clear();

}

int countdigs(int number) {
	int ndigs = 0;
	while (number != 0) {
		number = number / 10;
		ndigs++;
	}
	return ndigs++;
}

void Game::indexObjects()
{
	rangeassigment(objects, countdigs(max_x), x_comp);
	rangeassigment(objects, countdigs(max_y), y_comp);
	for (int i = 0; i < objects.size(); i++) {
		int index_x = objects[i].comparindex[x_comp];
		int index_y = objects[i].comparindex[y_comp];
		objects[i].quickindex = i;
		lookupmatrix[index_x][index_y] = i;
		//std::cout << lookupmatrix[index_x][index_y] << ';';
	}
	//for (int i = 0; i < comparematrix.size(); i++) {
		//for (int j = 0; j < comparematrix[i].size(); j++) {
			//std::cout << comparematrix[i][j].position[x_comp] << ',';
	//	}
	//}
	//std::cout << std::endl;
}

int getnextsquare(int number) {
	int temp = sqrt(number);
	if (temp * temp < number) {
		temp++;
	}
	return temp;
}

//now I need to impliment the algo that goes through the objects list and does the comparison to the 4 objects touching it.
