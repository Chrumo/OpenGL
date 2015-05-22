#ifndef MOVEMENT_H
#define MOVEMENT_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

using namespace std;

class Movement
{
private:
	float x_move;
	float z_move;
	float rotation;
	float y_rotation;
	float x_rot;
	float y_rot;
	float z_rot;
	
	vector<float> objects;
	vector<float> cabinets;

	bool ableToOpenCloseCabinets = false;

public:
	Movement();

	void moveForward(int speed);

	void moveBackward(int speed);

	void moveLeft(int speed);

	void moveRight(int speed);

	void computeLookAtPoint();

	void addPointToObjects(float x, float z, bool cabinet);

	float getXMove();
	float getZMove();
	float getRotation();
	float getYRotation();
	float getXRot();
	float getYRot();
	float getZRot();
	float getXDir();
	float getYDir();
	float getZDir();

	bool getAbleToOpenCloseCabinets();

	void setRotation(float rot);
	void setYRotation(float y_rot);

private:
	bool isObjectInWay(float x, float z);
};

#endif