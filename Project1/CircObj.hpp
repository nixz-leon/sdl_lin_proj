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
		int color[4] = {0,0,0,2};
		int radius = 5;
		float position[2];
		float velocity[2] = {0,0};
		float acceleration[2] = {0,0};
		float mass = 1;
		int comparindex[2];
		int quickindex;
		bool check_able = true;
		~Obj();
	};

	void findpos(Obj& ob, float time_step);
	//void add_force(Obj& ob, float force[2]);
	void setVals(Obj& ob, std::string new_name, float x, float y, float vx, float vy, int r, int g, int b);
	void setPos(Obj& ob, float x, float y);
	void budge(Obj& ob_a, Obj& ob_b);
	void setVel(Obj& ob, float xv, float yv);
	void setName(Obj& ob, std::string new_name);
	void setColor(Obj& ob, int r, int g, int b, int a);
	void borderCollision(Obj& ob, int min_y, int max_y, int min_x, int max_x);
	void circCollision(Obj& ob_a, Obj& ob_b);
	void proj(float a[2], float b[2], float destination[2]);
	void normproj(float a[2], float b[2], float destination[2]);
	float dot(float a[2], float b[2]);
	void scalarmult(float c, float v[2], float dest[2]);
	void scalarmultimd(float c, float v[2]);
	void sub(float a[2], float b[2]);
	bool checkforcollis(Obj ob_a, Obj ob_b);
	void add(float a[2], float b[2]);
	void normalize(float vector[2]);



}

enum {
	x_comp = 0,
	y_comp = 1
};


#endif