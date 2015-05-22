#ifndef CLOCK_H
#define CLOCK_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ObjLoader.h"

using namespace std;

class Clock
{
private:
	ObjLoader* clock;
	ObjLoader* hourhand;
	ObjLoader* minutehand;
	int listId_clock;
	int listId_hourhand;
	int listId_minutehand;
public:
	Clock();
	~Clock();
	void draw(int hour, int minute, bool first_render, GLuint texture);
};

#endif