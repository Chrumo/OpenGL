#ifndef LAMP_H
#define LAMP_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ObjLoader.h"

using namespace std;

class Lamp
{
private:
	ObjLoader* lamp;
	int listId;

public:
	Lamp();
	~Lamp();
	void draw(bool first_render);
};

#endif