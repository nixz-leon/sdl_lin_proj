#include "CircObj.hpp"

void CircOb::findpos(Obj& ob, float time_step) {
        ob.position[x_comp] = ob.position[x_comp] + (ob.velocity[x_comp] * time_step) + ((0.5f) * (ob.acceleration[x_comp] * time_step * time_step));
		ob.position[y_comp] = ob.position[y_comp] + (ob.velocity[y_comp] * time_step) + ((0.5f) * (ob.acceleration[y_comp] * time_step * time_step));
}
void CircOb::setPos(Obj& ob, float x, float y) {
	ob.position[x_comp] = x;
	ob.position[y_comp] = y;
}
void CircOb::setVel(Obj& ob, float xv, float yv) {
	ob.velocity[x_comp] = xv;
	ob.velocity[y_comp] = yv;
}
void CircOb::setColor(Obj& ob,int r, int g, int b, int a) {
	ob.color[0] = r;
	ob.color[1] = g;
	ob.color[2] = b;
	ob.color[3] = a;
}
void CircOb::borderCollision(Obj& ob, int min_y, int max_y, int min_x, int max_x) {
	if (ob.position[x_comp]-ob.radius < min_x ){
		ob.velocity[x_comp] *= -1;
		ob.position[x_comp] = min_x + ob.radius;
	}
	if (ob.position[x_comp] + ob.radius > max_x) {
		ob.velocity[x_comp] *= -1;
		ob.position[x_comp] = max_x - ob.radius;
	}
	if (ob.position[y_comp]-ob.radius < min_y ) {
		ob.velocity[y_comp] *= -1;
		ob.position[y_comp] = min_y + ob.radius;
	}
	if (ob.position[y_comp] + ob.radius > max_y) {
		ob.velocity[y_comp] *= -1;
		ob.position[y_comp] = max_y - ob.radius;
	}
}
float CircOb::dot(float a[2], float b[2])
{
	return (a[x_comp] * b[x_comp]) + (a[y_comp] * b[y_comp]);
}

void  CircOb::scalarmult(float c, float v[2], float dest[2])
{
	dest[x_comp] = v[x_comp] * c;
	dest[y_comp] = v[y_comp] * c;
}

void CircOb::proj(float a[2], float b[2], float destination[2])
{
	float scalar = dot(a,b) / dot(b,b);
	scalarmult(scalar, b, destination);
}
void CircOb::sub(float a[2], float b[2])
{
	a[x_comp] = a[x_comp] - b[x_comp];
	a[y_comp] = a[y_comp] - b[y_comp];
}

//TODO I need to add the detmerinat check again, and check to see if the werid bounce remains.
void CircOb::circCollision(Obj& ob_a, Obj ob_b) {
	float reflection_axis[2];
	reflection_axis[x_comp] = ob_b.position[x_comp] - ob_a.position[x_comp];
	reflection_axis[y_comp] = ob_b.position[y_comp] - ob_a.position[y_comp];
	float dist = sqrt(dot(reflection_axis, reflection_axis));
	float mindist = ob_a.radius + ob_b.radius;
	std::cout << dist << ',' << mindist << std::endl;
	if (dist <= mindist) {
		float halfreflect[2];
		float fullreflect[2];
		proj(ob_a.velocity, reflection_axis, halfreflect);
		scalarmult(2, halfreflect, fullreflect);
		sub(ob_a.velocity, fullreflect);
	}
}


CircOb::Obj::~Obj()
{
}
