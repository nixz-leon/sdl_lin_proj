#pragma once
#ifndef circobj_hpp
#define circobbj_hpp
#include <iostream>
#include <vector>
#include <cmath>
namespace CircOb {

	struct Obj {
		int color[4] = {100,150,50,150};
		int radius = 25;
		float position[2];
		float velocity[2] = {0,0};
		float acceleration[2] = {0,0};
		float density = 1;
		~Obj();
	};

	void findpos(Obj& ob, float time_step);
	//void add_force(Obj& ob, float force[2]);
	void setPos(Obj& ob, float x, float y);
	void setVel(Obj& ob, float xv, float yv);
	void setColor(Obj& ob, int r, int g, int b, int a);
	void display_pos_terminal(Obj ob);
	void display_vel_terminal(Obj ob);
	void display_acl_terminal(Obj ob);
	void borderCollision(Obj& ob, int min_y, int max_y, int min_x, int max_x);
	void circCollision(Obj& moving_ob, Obj static_ob);
	void proj(float a[2], float b[2], float destination[2]);
	float dot(float a[2], float b[2]);
	void scalarmult(float c, float v[2], float dest[2]);
	float quickdet(float a[2], float b[2]);
	void sub(float a[2], float b[2]);



}

enum {
	x_comp = 0,
	y_comp = 1
};


#endif