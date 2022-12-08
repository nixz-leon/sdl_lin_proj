#include "CircObj.hpp"

// since c++ passing in a point to an array, any function that needs to preform operations needs to be have a specified output array
void CircOb::findpos(Obj& ob, float time_step) {
	ob.velocity[x_comp] = ob.velocity[x_comp] + (ob.acceleration[x_comp] * time_step);
	ob.velocity[y_comp] = ob.velocity[y_comp] + (ob.acceleration[y_comp] * time_step);
	ob.position[x_comp] = ob.position[x_comp] + (ob.velocity[x_comp] * time_step) + ((0.5f) * (ob.acceleration[x_comp] * (time_step * time_step)));
	ob.position[y_comp] = ob.position[y_comp] + (ob.velocity[y_comp] * time_step) + ((0.5f) * (ob.acceleration[y_comp] * (time_step * time_step)));
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
void CircOb::budge(Obj& ob_a,Obj& ob_b)
{
	float error = 0.25f;
	float midpoint[2];
	midpoint[0] = (ob_a.position[x_comp] + ob_b.position[x_comp]) / 2;
	midpoint[1] = (ob_a.position[y_comp] + ob_b.position[y_comp]) / 2;
	float tempa[2];
	float tempb[2];
	tempa[0] = ob_a.position[0];
	tempa[1] = ob_a.position[1];
	tempb[0] = ob_b.position[0];
	tempb[1] = ob_b.position[1];
	sub(tempa, midpoint);
	sub(tempb, midpoint);
	float scalara = (ob_a.radius+error) / mag(tempa);
	float scalarb = (ob_b.radius+error) / mag(tempb);
	scalarmultimd(scalara, tempa);
	scalarmultimd(scalarb, tempb);
	add(tempa, midpoint);
	add(tempb, midpoint);
	setPos(ob_a, tempa[0], tempa[1]);
	setPos(ob_b, tempb[0], tempb[1]);

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
//Border collision is basically a just clamping function, this is just used for the edges of the screen
void CircOb::borderCollision(Obj& ob, int min_y, int max_y, int min_x, int max_x) {
	if (ob.position[x_comp] - ob.radius < min_x) {
		ob.velocity[x_comp] *= -1;
		ob.position[x_comp] = min_x + ob.radius;
	}
	if (ob.position[x_comp] + ob.radius > max_x) {
		ob.velocity[x_comp] *= -1;
		ob.position[x_comp] = max_x - ob.radius;
	}
	if (ob.position[y_comp] - ob.radius < min_y) {
		ob.velocity[y_comp] *= -1;
		ob.position[y_comp] = min_y + ob.radius;
	}
	if (ob.position[y_comp] + ob.radius > max_y) {
		ob.velocity[y_comp] *= -1;
		ob.position[y_comp] = max_y - ob.radius;
	}
}
//the sub functions takes in two arrays size 2, and subtracts b from a, and put the result into a
void CircOb::sub(float a[2], float b[2])
{
	a[x_comp] = a[x_comp] - b[x_comp];
	a[y_comp] = a[y_comp] - b[y_comp];
}
//the add functions takes in two arrays size 2, and adds them and put them into a
void CircOb::add(float a[2], float b[2])
{
	a[0] = a[0] + b[0];
	a[1] = a[1] + b[1];
}
//multiplies v by scalar c and puts into destination
void  CircOb::scalarmult(float c, float v[2], float dest[2])
{
	dest[x_comp] = v[x_comp] * c;
	dest[y_comp] = v[y_comp] * c;
}
//same as the function above but v acts as the destination array.
void CircOb::scalarmultimd(float c, float v[2]) {
	v[0] *= c;
	v[1] *= c;
}
// returns a float from the dot product of a and b
float CircOb::dot(float a[2], float b[2])
{
	return (a[x_comp] * b[x_comp]) + (a[y_comp] * b[y_comp]);
}
// returns the magnitude of a array
float CircOb::mag(float a[2])
{
	return sqrt(dot(a, a));
}
//returns the determinant of an agumented matrix composed of array a, and b 
float CircOb::quickdet(float a[2], float b[2])
{
	return ((a[0] * b[1]) - (b[0] * a[1]));
}
//projects array a, onto array b, and puts the component into a destination arry
void CircOb::proj(float a[2], float b[2], float destination[2])
{
	float scalar = dot(a,b) / dot(b,b);
	scalarmult(scalar, b, destination);
}
//checkforcollis finds the distance between the two circles and then compares it to the combined radius of the two circles and returns true if the circles overlap
bool CircOb::checkforcollis(Obj ob_a, Obj ob_b)
{
	float deltapos[2] = { ob_b.position[x_comp] - ob_a.position[x_comp], ob_b.position[y_comp] - ob_a.position[y_comp] };
	float dotedpos = dot(deltapos, deltapos);
	float radiuselm = (ob_a.radius + ob_b.radius)*(ob_a.radius + ob_b.radius);
	return dotedpos <= radiuselm;
}

void CircOb::circCollision(Obj& ob_a, Obj& ob_b) {
	// A centered is the delta of b from a, B centered is the delta of a from b.
	float acentered[2], bcentered[2], projecteda[2], projectedb[2];
	acentered[0] = ob_b.position[0] - ob_a.position[0];
	acentered[1] = ob_b.position[1] - ob_a.position[1];
	bcentered[0] = ob_a.position[0] - ob_b.position[0];
	bcentered[1] = ob_a.position[1] - ob_b.position[1];
	proj(ob_a.velocity, acentered, projecteda);
	proj(ob_b.velocity, bcentered, projectedb);
	//We initially subtracted the projected component of a from a, for its force on the object, same goes for projb
	sub(ob_a.velocity, projecteda);
	sub(ob_b.velocity, projectedb);
	//We then add the alteranative projection from the component to add its force on the respective object
	add(ob_a.velocity, projectedb);
	add(ob_b.velocity, projecteda);
	//We then move the two circles that have collided out of the collision range, so that we don't get multiple collisions actions for the same collision event
	budge(ob_a, ob_b);
}

bool CircOb::checkforcollisadv(Obj ob_a, Obj ob_b) {
	if (ob_a.check_able == false || ob_b.check_able == false) {
		return false;
	}
	float acentered[2], bcentered[2], projecteda[2], projectedb[2];
	acentered[0] = ob_b.position[0] - ob_a.position[0];
	acentered[1] = ob_b.position[1] - ob_a.position[1];
	bcentered[0] = ob_a.position[0] - ob_b.position[0];
	bcentered[1] = ob_a.position[1] - ob_b.position[1];
	proj(ob_a.velocity, acentered, projecteda);
	proj(ob_b.velocity, bcentered, projectedb);
	//We initially subtracted the projected component of a from a, for its force on the object, same goes for projb
	sub(ob_a.velocity, projecteda);
	sub(ob_b.velocity, projectedb);
	//We then add the alteranative projection from the component to add its force on the respective object
	add(ob_a.velocity, projectedb);
	add(ob_b.velocity, projecteda);
	//We then move the two circles that have collided out of the collision range, so that we don't get multiple collisions actions for the same collision event
	budge(ob_a, ob_b);
}

CircOb::Obj::~Obj()
{
}

