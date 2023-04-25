#pragma once
#ifndef circobj_hpp
#define circobbj_hpp
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
class Circ {
public:
	Circ();
	Circ(std::string name, int color[3], int rad, float position[2], float velocity[2], float acceleration[2], bool physics_type);
	void edgecollision(int min_x, int max_x, int min_y, int max_y);
	inline void updatepos(float timestep)
	{
		velocity[x_comp] = velocity[x_comp] + (acceleration[x_comp] * timestep);
		velocity[y_comp] = velocity[y_comp] + (acceleration[y_comp] * timestep);
		position[x_comp] = position[x_comp] + (velocity[x_comp] * timestep) + ((0.5f) * (acceleration[x_comp] * (timestep * timestep)));
		position[y_comp] = position[y_comp] + (velocity[y_comp] * timestep) + ((0.5f) * (acceleration[y_comp] * (timestep * timestep)));
	};
	inline void setpos(float x, float y) { position[x_comp] = x; position[y_comp] = y; };
	inline bool isdynamic() { return dynamic_physics; };
	bool buttoncheck(int x, int y);
	~Circ();
	std::string name;
	int color[4] = { 0,0,0,0 };
	float rad = 20;
	float position[2];
	float velocity[2];
	float acceleration[2];
	bool dynamic_physics = true;
	enum {
		x_comp = 0,
		y_comp = 1
	};
};
inline void add(float a[2], float b[2]) { a[0] += b[0]; a[1] += b[1];};
inline void add(float a[2], float b[2], float c[2]) { c[0] = a[0] + b[0]; c[1] = a[1] + b[1]; };
inline void sub(float a[2], float b[2]) { a[0] -= b[0]; a[1] -= b[1]; };
inline void sub(float a[2], float b[2], float c[2]) { c[0] = a[0] - b[0]; c[1] = a[1] - b[1]; };
inline void scalarmult(float c, float a[2]) { a[0] *= c; a[1] *= c; };
inline void scalarmult(float c, float a[2], float b[2]) { b[0] = a[0]*c; b[1] =a[1]*c; };
inline float dot(float a[2], float b[2]) { return (a[0] * b[0]) + (a[1] * b[1]); }
inline void set(float a[2], float b[2]) { a[0] = b[0]; a[1] = b[1]; };
inline void proj(float a[2], float b[2], float dest[2]);
inline void normalize(float a[2]);
void collisionevent(Circ& a, Circ& b, float timestep);




//rotation matrix for the purposes of 
//{c,-s}
//{s,c}

/*
class rect {
public:
	int center[2];
	int color[4];
	float firstcorn[2];
	float secondcorn[2];
	float thirdcorn[2];
	float fourthcorn[2];
	bool dynamic_physics = false;
	rect();
	rect(std::string name, int color[3], int width, int height, int rotation);
	rect(std::string name, int color[3], int firstcorner[2], int secondcorner[2], int thirdcorner[2], int fourthcorner[2]);
	inline void rotateobject(float angle);
	inline bool checkforpointoverlap(int x, int y);

};
*/


#endif