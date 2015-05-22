#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ObjLoader.h"

using namespace std;

class Notebook
{
private:
	ObjLoader* notebook;
	ObjLoader* display;
	int listId;
public:
	Notebook();
	~Notebook();
	void draw(bool first_render);
};

#endif