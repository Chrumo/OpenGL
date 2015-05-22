#define _USE_MATH_DEFINES

#ifndef _UNICODE
#define _UNICODE 1
#endif
#define IL_USE_PRAGMA_LIBS
#include "IL/devil_cpp_wrapper.hpp"
#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "ObjLoader.h"
#include "Cabinet.h"
#include "Table.h"
#include "Lamp.h"
#include "Clock.h"
#include "Library.h"
#include "Notebook.h"
#include "Vase.h"
#include "Bulb.h"
#include "colors.h"
#include "Movement.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#define GL_MIRRORED_REPEAT                0x8370
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_CLAMP_TO_BORDER                0x812D
#define GL_LIGHT_MODEL_COLOR_CONTROL      0x81F8
#define GL_SEPARATE_SPECULAR_COLOR        0x81FA

int win_width = 640;
int win_height = 480;

float cabinet_door_angle = 45.0f;
float green_light_angle = 0.0f;

int hour = 0;
int minute = 0;
int wallListId = 0;

bool real_time = false;
bool first_render = true;
bool mouse_control = true;
bool cabinet_open = false;
bool cabinet_close = true;
bool fog_enabled = false;
bool battery_on = false;
bool light_off = false; // all light except light3 are off

Cabinet* cabinet;
GLuint cabinet_texture;
Table* table;
GLuint table_texture;
Lamp* lamp;
Clock* clocks;
GLuint clocks_texture;
Library* library;
GLuint library_texture;
Notebook* notebook;
Vase* vase;
GLuint vase_texture;
Bulb* bulb;
Movement* movement;
GLuint carpet_texture;
GLuint wall_texture;

void drawText(const char *text, int length, int x, int y){
	glMatrixMode(GL_PROJECTION);
	double matrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void key_pressed(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 27:	// Escape
		exit(0);
		break;
	case 't':
		glutFullScreenToggle();
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'l':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 'm':
		if (mouse_control){
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		else{
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		mouse_control = !mouse_control;
		break;
	case 'w':
		movement->moveForward(12);
		glutPostRedisplay();
		break;
	case 's':
		movement->moveBackward(12);
		glutPostRedisplay();
		break;
	case 'a':
		movement->moveLeft(8);
		glutPostRedisplay();
		break;
	case 'd':
		movement->moveRight(8);
		glutPostRedisplay();
		break;
	case 'r': //set time to real time
		real_time = !real_time;
		glutPostRedisplay();
		break;
	case 'e': //open/close doors
		if (movement->getAbleToOpenCloseCabinets()){
			cabinet_close = !cabinet_close;
			cabinet_open = !cabinet_open;
			fog_enabled = !fog_enabled;
			if (fog_enabled){
				glEnable(GL_FOG);
				float fog_color[] = { 0.7f, 0.7f, 0.7f, 0.0f };
				glFogfv(GL_FOG_COLOR, fog_color);
				glClearColor(fog_color[0], fog_color[1], fog_color[2], 0.0f);

				glFogi(GL_FOG_MODE, GL_EXP2);
				glFogf(GL_FOG_START, 25.0f);
				glFogf(GL_FOG_END, 750.0f);
				glFogf(GL_FOG_DENSITY, 0.003f);
				glFogi(GL_FOG_HINT, GL_DONT_CARE);

				glDisable(GL_LIGHT0);
				if (!light_off){
					glEnable(GL_LIGHT1);
					glEnable(GL_LIGHT2);
				}
			}
			else{
				glDisable(GL_FOG);

				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
				if (!light_off){
					glEnable(GL_LIGHT0);
				}
			}
		}
		glutPostRedisplay();
		break;
	case 'g':
		battery_on = !battery_on;
		if (battery_on){
			glEnable(GL_LIGHT3);
		}
		else{
			glDisable(GL_LIGHT3);
		}
		glutPostRedisplay();
		break;
	case 'h':
		light_off = !light_off;
		if (light_off){
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
		}
		else{
			if (fog_enabled){
				glEnable(GL_LIGHT1);
				glEnable(GL_LIGHT2);
			}
			else{
				glEnable(GL_LIGHT0);
			}
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white2);
		}
		glutPostRedisplay();
		break;
	};
}

void mouse_moved(int x, int y){
	if (mouse_control == false || first_render) return;
	float half_x_win = win_width / 2.0f;
	float half_y_win = win_height / 2.0f;
	if ((x == half_x_win || x == half_x_win + 1 || x == half_x_win - 1) && (y == half_y_win || y == half_y_win + 1 || y == half_y_win - 1)) {
		return;
	}
	float rotation = movement->getRotation();
	float y_rotation = movement->getYRotation();
	rotation -= (x - half_x_win) / 2.0f;
	y_rotation -= (y - half_y_win) / 3.5f;
	movement->setRotation(rotation);
	movement->setYRotation(y_rotation);
	glutWarpPointer(win_width / 2, win_height / 2);
	glutPostRedisplay();
}

void drawWall(float x_from, float x_to, float z_from, float z_to, float x_step, float z_step,
				float s_from, float s_to, float t_from, float t_to)
{
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (float z = z_from, t = t_to, t_step = (z_step / (z_to - z_from) * (t_from - t_to)); z < z_to; z += z_step, t += t_step)
	{
		glBegin(GL_QUAD_STRIP);
		for (float x = x_from, s = s_from, s_step = (x_step / (x_to - x_from) * (s_to - s_from)); x < x_to; x += x_step, s += s_step)
		{
			glTexCoord2f(s, t);				glVertex3f(x, 0.0f, z);
			glTexCoord2f(s, t + t_step);	glVertex3f(x, 0.0f, z + z_step);
		}
		glEnd();
	}
}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white2);
	glShadeModel(GL_SMOOTH);
	
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT); 

	glutWarpPointer(win_width / 2, win_height / 2);
	glutSetCursor(GLUT_CURSOR_NONE);

	ilImage image;

	movement = new Movement();
	cabinet = new Cabinet(movement);
	glGenTextures(1, &cabinet_texture);
	glBindTexture(GL_TEXTURE_2D, cabinet_texture);
	image.Load(L"Textures/cabinet_wood_texture.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

	table = new Table(movement);
	glGenTextures(1, &table_texture);
	glBindTexture(GL_TEXTURE_2D, table_texture);
	image.Load(L"Textures/table_wood_texture.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

	lamp = new Lamp();
	clocks = new Clock();
	glGenTextures(1, &clocks_texture);
	glBindTexture(GL_TEXTURE_2D, clocks_texture);
	image.Load(L"Textures/clock_texture.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

	library = new Library(movement);
	glGenTextures(1, &library_texture);
	glBindTexture(GL_TEXTURE_2D, library_texture);
	image.Load(L"Textures/library_texture.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

	notebook = new Notebook();
	vase = new Vase(movement);
	glGenTextures(1, &vase_texture);
	glBindTexture(GL_TEXTURE_2D, vase_texture);
	image.Load(L"Textures/vase_texture.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

	bulb = new Bulb();

	glGenTextures(1, &carpet_texture);
	glBindTexture(GL_TEXTURE_2D, carpet_texture);
	image.Load(L"Textures/carpet_texture.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

	glGenTextures(1, &wall_texture);
	glBindTexture(GL_TEXTURE_2D, wall_texture);
	image.Load(L"Textures/wall_texture.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

	glBindTexture(GL_TEXTURE_2D, 0); //unbind any texture

	wallListId = glGenLists(1);
	glNewList(wallListId, GL_COMPILE);
	glPushMatrix();
	glTranslatef(-350.0f, 0.0f, 0.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wall_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 12.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wall_texture);
	drawWall(0.0f, 305.0f, -350.0f, 350.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(345.0f, 0.0f, 0.0f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wall_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 12.5f);
	drawWall(0.0f, 305.0f, -350.0f, 350.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 350.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wall_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 12.5f);
	drawWall(-350.0f, 350.0f, 0.0f, 300.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -350.0f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wall_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 12.5f);
	drawWall(-345.0f, 355.0f, 0.0f, 300.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, floor_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 5.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, carpet_texture);
	drawWall(-350.0f, 350.0f, -350.0f, 350.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 300.0f, 0.0f);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wall_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0f);
	drawWall(-350.0f, 350.0f, -350.0f, 350.0f, 5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	glPopMatrix();
	glEndList();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	movement->computeLookAtPoint();
	float x_move = movement->getXMove();
	float z_move = movement->getZMove();
	float x_rot = movement->getXRot();
	float y_rot = movement->getYRot();
	float z_rot = movement->getZRot();
	glLoadIdentity();
	gluLookAt(x_move, 155.0f, z_move, x_rot, y_rot + 155.0f, z_rot, 0.0f, 1.0f, 0.0f);
	
	//setting light

	glPushMatrix();
	float l0_pos[] = { 0.0f, 285.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, black);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white2);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white2);
	glPopMatrix();

	glPushMatrix();
	float l1_pos[] = { 0.0f, 285.0f, 0.0f, 1.0f };
	glRotatef(green_light_angle, 0.0f, 1.0f, 0.0f);
	float l1_dir[] = { 340.0f, -165.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1_dir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 35.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5f);
	glLightfv(GL_LIGHT1, GL_AMBIENT, green);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, green2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, green2);
	glPopMatrix();

	glPushMatrix();
	float l2_pos[] = { 0.0f, 285.0f, 0.0f, 1.0f };
	glRotatef(green_light_angle, 0.0f, 1.0f, 0.0f);
	float l2_dir[] = { -340.0f, -165.0f, 0.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, l2_pos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l2_dir);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 35.0f);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.5f);
	glLightfv(GL_LIGHT2, GL_AMBIENT, red);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, red2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, red2);
	glPopMatrix();

	//battery light
	glPushMatrix();
	float l3_pos[] = { x_move, 155.0f, z_move, 1.0f };
	x_rot = movement->getXDir();
	y_rot = movement->getYDir();
	z_rot = movement->getZDir();
	float l3_dir[] = { x_rot, y_rot, z_rot};
	glLightfv(GL_LIGHT3, GL_POSITION, l3_pos);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, l3_dir);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 20.0f);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 0.5f);
	glLightfv(GL_LIGHT3, GL_AMBIENT, cyan);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, cyan2);
	glLightfv(GL_LIGHT3, GL_SPECULAR, cyan2);
	glPopMatrix();

	//drawing objects

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -315.0f);
	cabinet->draw(first_render, cabinet_door_angle, cabinet_texture);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-123.0f, 0.0f, -315.0f);
	cabinet->draw(first_render, cabinet_door_angle, cabinet_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(123.0f, 0.0f, -315.0f);
	cabinet->draw(first_render, cabinet_door_angle, cabinet_texture);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(300.0f, 0.0f, 100.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	table->draw(first_render, table_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(320.0f, 70.0f, 140.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	lamp->draw(first_render);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(320.0f, 70.0f, 60.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	lamp->draw(first_render);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-300.0f, 200.0f, -349.0f);
	if (real_time){
		time_t rawtime;
		struct tm * timeinfo = new struct tm();
		time(&rawtime);
		localtime_s(timeinfo, &rawtime);
		hour = timeinfo->tm_hour;
		minute = timeinfo->tm_min;
	}
	clocks->draw(hour, minute, first_render, clocks_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(300.0f, 0.0f, 215.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	library->draw(first_render, library_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(300.0f, 0.0f, 297.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	library->draw(first_render, library_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(300.0f, 73.0f, 100.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	notebook->draw(first_render);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-300.0f, 0.0f, 300.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	vase->draw(first_render, vase_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 281.5f, 0.0f);
	if (fog_enabled){ // green light on
		bulb->draw(first_render, bulb_off_color);
	}
	else{
		bulb->draw(first_render, bulb_on_color);
	}
	glPopMatrix();
	
	glCallList(wallListId);

	//show text
	if (movement->getAbleToOpenCloseCabinets()){
		std::string text = "press E";
		drawText(text.data(), text.length(), win_width / 2, 3*win_height / 4);
	}

	first_render = false;
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	win_width = width;
	win_height = height;

	glViewport(0, 0, win_width, win_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, double(win_width) / double(win_height), 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

/*
--- 0 starts multiple recursion
--- 1 controls clock
--- 2 controls cabinet doors
--- 3 controls angle of green light
*/
void timer(int t)
{
	if (t == 0){
		glutTimerFunc(1000, timer, 1);
		glutTimerFunc(10, timer, 2);
		glutTimerFunc(5, timer, 3);
	}
	else if (t == 1){
		if (real_time){
			glutTimerFunc(1000, timer, 1);
			return;
		}
		minute++;
		if (minute == 60){
			hour++;
			hour %= 12;
		}
		minute %= 60;
		glutTimerFunc(1000, timer, 1);
	}
	else if (t == 2){
		if (cabinet_close){
			cabinet_door_angle += 0.5f;
			if (cabinet_door_angle >= 45){
				cabinet_close = false;
			}
		}
		if (cabinet_open){
			cabinet_door_angle -= 0.5f;
			if (cabinet_door_angle <= 0){
				cabinet_open = false;
			}
		}
		glutTimerFunc(10, timer, 2);
	}
	else if(t == 3){ //implies that green light is enabled
		if (fog_enabled){
			green_light_angle += 2.5;
		}
		glutTimerFunc(5, timer, 3);
	}
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Init window
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow("Projekt");

	// Register callbacks
	glutDisplayFunc(render);
	glutKeyboardFunc(key_pressed);
	glutPassiveMotionFunc(mouse_moved);
	glutReshapeFunc(reshape);
	glutTimerFunc(50, timer, 0);

	init();

	//Main loop
	glutMainLoop();

	free(cabinet);
	free(table);
	free(lamp);
	free(clocks);
	free(library);
	free(notebook);
	free(vase);
	free(bulb);
	free(movement);

	return 0;
}