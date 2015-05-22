#ifndef CABINET_H
#define CABINET_H

#include <fstream>
#include <iostream>
#include <string>
#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include <vector>
#include "Movement.h"
#include "ObjLoader.h"

using namespace std;

class Cabinet
{
private:
	ObjLoader* cabinet;
	ObjLoader* cabinet_leftdoor;
	ObjLoader* cabinet_rightdoor;
	Movement* m;
	int listId;
	int listId_leftdoor;
	float x_min;
	float x_max;
	float z_min;
	float z_max;
	GLuint texture;
public:
	Cabinet(Movement* m);
	~Cabinet();
	void draw(bool first_render, float angle, GLuint texture);
private:
	void setMinMax(float x, float z);
};

#endif