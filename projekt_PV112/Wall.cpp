#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "Wall.h"
#include "colors.h"

Wall::Wall(){
	listId = glGenLists(1);
	glNewList(listId, GL_COMPILE);
	drawWall()
	glEndList();
}

Wall::~Wall(){
	free(bulb);
}

void Wall::draw(){
	glCallList(listId);
}

void Wall::drawWall(float x_from, float x_to, float z_from, float z_to, float x_step, float z_step)
{
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (float z = z_from; z < z_to; z += z_step)
	{
		glBegin(GL_QUAD_STRIP);
		for (float x = x_from; x < x_to; x += x_step)
		{
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(x, 0.0f, z);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(x, 0.0f, z + z_step);
		}
		glEnd();
	}
}