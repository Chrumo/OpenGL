#ifndef TABLE_H
#define TABLE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ObjLoader.h"
#include "Movement.h"

using namespace std;

class Table
{
private:
	ObjLoader* table;
	Movement* m;
	int listId;
	float x_min;
	float x_max;
	float z_min;
	float z_max;
public:
	Table(Movement* m);
	~Table();
	void draw(bool first_render, GLuint texture);
private:
	void setMinMax(float x, float z);
};

#endif