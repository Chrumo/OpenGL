#ifndef BULB_H
#define BULB_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ObjLoader.h"

using namespace std;

class Bulb
{
private:
	ObjLoader* bulb;
	int listId;
public:
	Bulb();
	~Bulb();
	void draw(bool first_render, const float* color);
};

#endif