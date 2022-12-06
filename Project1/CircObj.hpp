#pragma once
#ifndef circobj_hpp
#define circobbj_hpp
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
namespace CircOb {

	struct Obj {
		std::string name;
		int color[4] = {100,150,50,150};
		int radius = 25;
		float position[2];
		float velocity[2] = {0,0};
		float acceleration[2] = {0,0};
		float mass = 1;
		~Obj();
	};

	void findpos(Obj& ob, float time_step);
	//void add_force(Obj& ob, float force[2]);
	void setPos(Obj& ob, float x, float y);
	void setVel(Obj& ob, float xv, float yv);
	void setName(Obj& ob, std::string new_name);
	void setColor(Obj& ob, int r, int g, int b, int a);
	void borderCollision(Obj& ob, int min_y, int max_y, int min_x, int max_x);
	void circCollision(Obj& ob_a, Obj& ob_b, float adjtime);
	void proj(float a[2], float b[2], float destination[2]);
	float dot(float a[2], float b[2]);
	float mag(float a[2]);
	void momentumstuff(Obj& ob_a, Obj& ob_b);
	void scalarmult(float c, float v[2], float dest[2]);
	float quickdet(float a[2], float b[2]);
	void sub(float a[2], float b[2]);
	bool checkforcollis(Obj& ob_a, Obj& ob_b, float timestep);
	void add(float a[2], float b[2]);



}

enum {
	x_comp = 0,
	y_comp = 1
};


#endif