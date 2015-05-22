#define _USE_MATH_DEFINES
#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "Clock.h"
#include "colors.h"
#include <cmath>

Clock::Clock(){
	clock = new ObjLoader();
	hourhand = new ObjLoader();
	minutehand = new ObjLoader();
	clock = clock->loadObject("clock");
	hourhand = hourhand->loadObject("clock-hourhand");
	minutehand = minutehand->loadObject("clock-minutehand");
	listId_clock = glGenLists(1);
	glNewList(listId_clock, GL_COMPILE);
	vector<Vector3f> vertices = clock->GetVertices();
	vector<Vector3f> normals = clock->GetNormals();
	vector<Vector2f> textures = clock->GetTextures();
	vector<Triangle> triangles = clock->GetTriangles();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);
	glBegin(GL_TRIANGLES);
	for (std::vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		glNormal3f(normals[it->n0].x, normals[it->n0].y, normals[it->n0].z);
		glTexCoord2f(textures[it->t0].x, textures[it->t0].y);
		glVertex3f(vertices[it->v0].x, vertices[it->v0].y, vertices[it->v0].z);
		glNormal3f(normals[it->n1].x, normals[it->n1].y, normals[it->n1].z);
		glTexCoord2f(textures[it->t1].x, textures[it->t1].y);
		glVertex3f(vertices[it->v1].x, vertices[it->v1].y, vertices[it->v1].z);
		glNormal3f(normals[it->n2].x, normals[it->n2].y, normals[it->n2].z);
		glTexCoord2f(textures[it->t2].x, textures[it->t2].y);
		glVertex3f(vertices[it->v2].x, vertices[it->v2].y, vertices[it->v2].z);
	}
	glEnd();
	glEndList();
	listId_hourhand = glGenLists(1);
	glNewList(listId_hourhand, GL_COMPILE);
	vertices = hourhand->GetVertices();
	normals = hourhand->GetNormals();
	triangles = hourhand->GetTriangles();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);
	glBegin(GL_TRIANGLES);
	for (std::vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		glNormal3f(normals[it->n0].x, normals[it->n0].y, normals[it->n0].z);
		glVertex3f(vertices[it->v0].x, vertices[it->v0].y, vertices[it->v0].z);
		glNormal3f(normals[it->n1].x, normals[it->n1].y, normals[it->n1].z);
		glVertex3f(vertices[it->v1].x, vertices[it->v1].y, vertices[it->v1].z);
		glNormal3f(normals[it->n2].x, normals[it->n2].y, normals[it->n2].z);
		glVertex3f(vertices[it->v2].x, vertices[it->v2].y, vertices[it->v2].z);
	}
	glEnd();
	glEndList();
	listId_minutehand = glGenLists(1);
	glNewList(listId_minutehand, GL_COMPILE); vertices = minutehand->GetVertices();
	normals = minutehand->GetNormals();
	triangles = minutehand->GetTriangles();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);
	glBegin(GL_TRIANGLES);;
	for (std::vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		glNormal3f(normals[it->n0].x, normals[it->n0].y, normals[it->n0].z);
		glVertex3f(vertices[it->v0].x, vertices[it->v0].y, vertices[it->v0].z);
		glNormal3f(normals[it->n1].x, normals[it->n1].y, normals[it->n1].z);
		glVertex3f(vertices[it->v1].x, vertices[it->v1].y, vertices[it->v1].z);
		glNormal3f(normals[it->n2].x, normals[it->n2].y, normals[it->n2].z);
		glVertex3f(vertices[it->v2].x, vertices[it->v2].y, vertices[it->v2].z);
	}
	glEnd();
	glEndList();
}

Clock::~Clock(){
	free(clock);
	free(hourhand);
	free(minutehand);
}

void Clock::draw(int hour, int minute, bool first_render, GLuint texture){
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glCallList(listId_clock);
	glDisable(GL_TEXTURE_2D);

	if (hour > 12) hour = hour - 12;
	float hour_angle = hour * 30.0f + minute * 0.5f;
	glTranslatef(0.0f, -3.0f, 0.0f);
	glRotatef(hour_angle, 0.0f, 0.0f, -1.0f);

	glCallList(listId_hourhand);

	float minute_angle = minute * 6.0f - hour_angle + 90.0f;
	glRotatef(minute_angle, 0.0f, 0.0f, -1.0f);
	glTranslatef(0.0f, 3.5f, 0.0f);
	
	glCallList(listId_minutehand);
}