#ifndef VASE_H
#define VASE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Movement.h"
#include "ObjLoader.h"

using namespace std;

class Vase
{
private:
	ObjLoader* vase;
	Movement* m;
	int listId;
	float x_min;
	float x_max;
	float z_min;
	float z_max;
public:
	Vase(Movement* m);
	~Vase();
	void draw(bool first_render, GLuint texture);
private:
	void setMinMax(float x, float z);
};

#endif