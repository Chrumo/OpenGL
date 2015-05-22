#ifndef WALL_H
#define WALL_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ObjLoader.h"

using namespace std;

class Wall
{
private:
	int listId;
public:
	Wall();
	~Wall();
	void draw();
	void drawWall(float x_from, float x_to, float z_from, float z_to, float x_step, float z_step);
};

#endif