#include "Objects.hpp"

inline float calcInvSqRoot(float n) {

	const float threehalfs = 1.5F;
	float y = n;

	long i = *(long*)&y;

	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;

	y = y * (threehalfs - ((n * 0.5F) * y * y));

	return y;
}


Circ::Circ()
{
	name = "";
	rad = 0;
	position[0] = 0.f;
	position[1] = 0.f;
	velocity[0] = 0.f;
	velocity[1] = 0.f;
	acceleration[0] = 0.f;
	acceleration[1] = 0.f;
}

Circ::Circ(std::string new_name, int new_color[3], int new_r, float new_p[2], float new_v[2], float new_a[2], bool physics_type)
{
	name = new_name;
	color[0] = new_color[0];
	color[1] = new_color[1];
	color[2] = new_color[2];
	rad = new_r;
	position[0] = new_p[0];
	position[1] = new_p[1];
	if (physics_type) {
		velocity[0] = new_v[0];
		velocity[1] = new_v[1];
		acceleration[0] = new_a[0];
		acceleration[1] = new_a[1];
	}
	else {
		velocity[0] = 0;
		velocity[1] = 0;
		acceleration[0] = 0;
		acceleration[1] = 0;
	}
	
}

void Circ::edgecollision(int min_x, int max_x, int min_y, int max_y)
{
	if (position[x_comp] - rad < min_x) {
		velocity[x_comp] *= -1;
		position[x_comp] = min_x + rad;
	}
	if (position[x_comp] + rad > max_x) {
		velocity[x_comp] *= -1;
		position[x_comp] = max_x - rad;
	}
	if (position[y_comp] - rad < min_y) {
		velocity[y_comp] *= -1;
		position[y_comp] = min_y + rad;
	}
	if (position[y_comp] + rad > max_y) {
		velocity[y_comp] *= -1;
		position[y_comp] = max_y - rad;
	}
}



bool Circ::buttoncheck(int x, int y)
{
	float distancevec[2];
	distancevec[0] = x - position[0];
	distancevec[1] = y - position[1];
	float temp = dot(distancevec, distancevec);
	float max = rad * rad;
	if (temp < max) {
		return true;
	}
	return false;
}

Circ::~Circ()
{
}


inline void proj(float a[2], float b[2], float dest[2])
{
	float scalar = dot(a, b);
	scalarmult(scalar, b, dest);
}

inline void normalize(float a[2])
{
	float temp = dot(a, a);
	float scalar = calcInvSqRoot(temp);
	scalarmult(scalar, a);
}

void collisionevent(Circ& a, Circ& b, float timestep)
{
	//first part, check for collision

	//second part, if collision, then adjust velocities

	//third part budge the objects away from each other
	float deltapos[2];
	sub(a.position, b.position, deltapos);
	float squaredsize = dot(deltapos, deltapos);
	float mindistance = (a.rad + b.rad) * (a.rad + b.rad);
	if (squaredsize <= mindistance) {
		if (a.isdynamic() && b.isdynamic() ) {
			//Start of the velocity changing
			float centered[2], bcentered[2], projecteda[2], projectedb[2];
			sub(b.position, a.position, centered);
			sub(a.position, b.position, bcentered);
			bcentered[0] = a.position[0] - b.position[0];
			bcentered[1] = a.position[1] - b.position[1];
			normalize(centered);
			normalize(bcentered);
			proj(a.velocity, centered, projecteda);
			proj(b.velocity, centered, projectedb);
			sub(a.velocity, projecteda);
			sub(b.velocity, projectedb);
			add(a.velocity, projectedb);
			add(b.velocity, projecteda);
			//end of section
			//start of budge
			float error = 0.25f;
			float midpoint[2];
			add(a.position, b.position, midpoint);
			scalarmult(0.5f, midpoint);
			float tempa[2], tempb[2];
			set(tempa, a.position);
			set(tempb, b.position);
			sub(tempa, midpoint);
			sub(tempb, midpoint);
			normalize(tempa);
			normalize(tempb);
			float scalara = (a.rad + error);
			float scalarb = (b.rad + error);
			scalarmult(scalara, tempa);
			scalarmult(scalarb, tempb);
			add(tempa, midpoint);
			add(tempb, midpoint);
			a.setpos(tempa[0], tempa[1]);
			b.setpos(tempb[0], tempb[1]);
		}
		else if (!b.isdynamic()) {
			float centered[2], projected[2];
			sub(b.position, a.position, centered);
			normalize(centered);
			proj(a.velocity, centered, projected);
			scalarmult(2.f, projected);
			sub(a.velocity, projected);
			//
			sub(a.position, b.position);
			normalize(a.position);
			float scalar = a.rad + b.rad + 0.25f;
			scalarmult(scalar, a.position);
			add(a.position, b.position);
		}
		else {
			float centered[2], projected[2];
			sub(a.position, b.position, centered);
			normalize(centered);
			proj(b.velocity, centered, projected);
			scalarmult(2.f, projected);
			sub(b.velocity, projected);
			//
			sub(b.position, a.position);
			normalize(b.position);
			float scalar = a.rad + b.rad + 0.25f;
			scalarmult(scalar, b.position);
			add(b.position, a.position);
		}
	}
}




//Next todo is add in a file system, where you can write to and save state files, which just record the object list
//That way I can add in the ground work for different screens.
// This also means other update functions
// and adding a menu.cpp as an alternative to game.cpp
// Maybe an editor.cpp for making maps and stuffs.
