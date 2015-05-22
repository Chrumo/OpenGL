#ifndef LIBRARY_H
#define LIBRARY_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Movement.h"
#include "ObjLoader.h"

using namespace std;

class Library
{
private:
	ObjLoader* library;
	Movement* m;
	int listId;
	float x_min;
	float x_max;
	float z_min;
	float z_max;
public:
	Library(Movement* m);
	~Library();
	void draw(bool first_render, GLuint texture);
private:
	void setMinMax(float x, float z);
};

#endif