#include "CircObj.hpp"

void CircOb::findpos(Obj& ob, float time_step) {
        ob.position[x_comp] = ob.position[x_comp] + (ob.velocity[x_comp] * time_step) + ((0.5f) * (ob.acceleration[x_comp] * time_step * time_step));
		ob.position[y_comp] = ob.position[y_comp] + (ob.velocity[y_comp] * time_step) + ((0.5f) * (ob.acceleration[y_comp] * time_step * time_step));
}
void CircOb::setName(Obj& ob, std::string new_name) {
	ob.name = new_name;
}
void CircOb::setVals(Obj& ob, std::string new_name, float x, float y, float vx, float vy, int r, int g, int b)
{
	ob.name = new_name;
	setPos(ob, x, y);
	setVel(ob, vx, vy);
	ob.color[0] = r;
	ob.color[1] = g;
	ob.color[2] = b;
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
float CircOb::mag(float a[2])
{
	return sqrt(dot(a, a));
}
void CircOb::momentumstuff(Obj& ob_a, Obj& ob_b)
{
	float vela = mag(ob_a.velocity);
	float velb = mag(ob_b.velocity);
	float totalmomentum = (ob_a.mass * vela) + (ob_b.mass * velb);
	float newvela = totalmomentum / (2);
	float newvelb = totalmomentum / (2);
	float scalar_a = newvela / vela;
	float scalar_b = newvelb / velb;
	float temp1[2];
	float temp2[2];
	scalarmult(scalar_a, ob_a.velocity, temp1);
	scalarmult(scalar_b, ob_b.velocity, temp2);
	setVel(ob_a, temp1[x_comp], temp1[y_comp]);
	setVel(ob_b, temp2[x_comp], temp2[y_comp]);

}
void  CircOb::scalarmult(float c, float v[2], float dest[2])
{
	dest[x_comp] = v[x_comp] * c;
	dest[y_comp] = v[y_comp] * c;
}

float CircOb::quickdet(float a[2], float b[2])
{
	return ((a[0] * b[1]) - (b[0] * a[1]));
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
bool CircOb::checkforcollis(Obj& ob_a, Obj& ob_b, float timestep)
{
	Obj temp_a = ob_a;
	Obj temp_b = ob_b;
	float deltapos[2] = { ob_b.position[x_comp] - ob_a.position[x_comp], ob_b.position[y_comp] - ob_a.position[y_comp] };
	float dotedpos = mag(deltapos);
	float radiuselm = (ob_a.radius + ob_b.radius);
	return dotedpos <= radiuselm;
}
void CircOb::add(float a[2], float b[2])
{
	a[0] = a[0] + b[0];
	a[1] = a[1] + b[1];
}
// think about maybe changing the circle collision to also change position to adjust and prevent 


void CircOb::circCollision(Obj& ob_a, Obj& ob_b, float adjtime) {
	float acentered[2];
	float bcentered[2];
	acentered[0] = ob_b.position[0] - ob_a.position[0];
	acentered[1] = ob_b.position[1] - ob_a.position[1];
	bcentered[0] = ob_a.position[0] - ob_b.position[0];
	bcentered[1] = ob_a.position[1] - ob_b.position[1];
	std::cout << "start" << std::endl;
	std::cout << ob_a.name << " with " << ob_b.name << std::endl;
	std::cout << ob_a.velocity[0] << ',' << ob_a.velocity[1] << std::endl;
	std::cout << ob_b.velocity[0] << ',' << ob_b.velocity[1] << std::endl;
	std::cout << ob_a.position[0] << ',' << ob_a.position[1] << std::endl;
	std::cout << ob_b.position[0] << ',' << ob_b.position[1] << std::endl;
		//momentumstuff(ob_a, ob_b);
	//std::cout << mag(ob_a.velocity) << ',' << mag(ob_b.velocity) << std::endl;
	std::cout << "det" << quickdet(ob_a.velocity, acentered) << std::endl;
	std::cout << "det" << quickdet(ob_b.velocity, bcentered) << std::endl;
	bool flaga = quickdet(ob_a.velocity, acentered) != 0;
	bool flagb = quickdet(ob_b.velocity, bcentered) != 0;
	//I need to re introduce the quick det situation
	float projected1[2];
	float projected2[2];
	float changea[2];
	float changeb[2];
	if (flaga && flagb) {
		proj(ob_a.velocity, acentered, projected1);
		proj(ob_b.velocity, bcentered, projected2);
		std::cout << "proj" << projected1[0] << ',' << projected1[1] << std::endl;
		std::cout << "proj" << projected2[0] << ',' << projected2[1] << std::endl;
		scalarmult(2, projected1, changea);
		scalarmult(2, projected2, changeb);
		sub(ob_a.velocity, projected1);
		sub(ob_b.velocity, projected2);
		add(ob_a.velocity, projected2);
		add(ob_b.velocity, projected1);
	}
	else if (flaga && !flagb) {
		std::cout << "bloop4" << std::endl;
		proj(ob_a.velocity, acentered, projected1);
		std::cout << "proj" << projected2[0] << ',' << projected1[1] << std::endl;
		sub(ob_a.velocity, projected1);
		add(ob_b.velocity, projected1);
	}
	else {
		std::cout << "bloop5" << std::endl;
		proj(ob_b.velocity, bcentered, projected2);
		std::cout << "proj" << projected2[0] << ',' << projected2[1] << std::endl;
		add(ob_a.velocity, projected2);
		sub(ob_b.velocity, projected2);
	}
	while (checkforcollis(ob_a, ob_b, adjtime)) {
		findpos(ob_a, adjtime / 50);
		findpos(ob_b, adjtime / 50);
	}
	std::cout << "momentum" << std::endl;
	
	std::cout << "end" << std::endl;
	
}



CircOb::Obj::~Obj()
{
}
