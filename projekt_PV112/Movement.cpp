#include "Movement.h"
#include <iostream>
#include <cmath>

Movement::Movement(){
	x_move = 0.0f;
	z_move = 0.0f;
	rotation = 180.0f;
	y_rotation = 0.0f;
	x_rot = 0.0f;
	y_rot = 0.0f;
	z_rot = 1.0f;
}

void Movement::moveForward(int speed){
	x_move -= sin(M_PI * rotation / 180.0) * speed;
	z_move -= cos(M_PI * rotation / 180.0) * speed;
	if (isObjectInWay(x_move, z_move) || x_move > 340.0f || x_move < -340.0f || z_move > 340.0f || z_move < -340.0f){
		x_move += sin(M_PI * rotation / 180.0) * speed;
		z_move += cos(M_PI * rotation / 180.0) * speed;
	}
	return;
}

void Movement::moveBackward(int speed){
	x_move += sin(M_PI * rotation / 180.0) * speed;
	z_move += cos(M_PI * rotation / 180.0) * speed;
	if (isObjectInWay(x_move, z_move) || x_move > 340.0f || x_move < -340.0f || z_move > 340.0f || z_move < -340.0f){
		x_move -= sin(M_PI * rotation / 180.0) * speed;
		z_move -= cos(M_PI * rotation / 180.0) * speed;
	}
}

void Movement::moveLeft(int speed){
	x_move -= sin(M_PI * (90 + rotation) / 180.0) * speed;
	z_move -= cos(M_PI * (90 + rotation) / 180.0) * speed;
	if (isObjectInWay(x_move, z_move) || x_move > 340.0f || x_move < -340.0f || z_move > 340.0f || z_move < -340.0f){
		x_move += sin(M_PI * (90 + rotation) / 180.0) * speed;
		z_move += cos(M_PI * (90 + rotation) / 180.0) * speed;
	}
}

void Movement::moveRight(int speed){
	x_move += sin(M_PI * (90 + rotation) / 180.0) * speed;
	z_move += cos(M_PI * (90 + rotation) / 180.0) * speed;
	if (isObjectInWay(x_move, z_move) || x_move > 340.0f || x_move < -340.0f || z_move > 340.0f || z_move < -340.0f){
		x_move -= sin(M_PI * (90 + rotation) / 180.0) * speed;
		z_move -= cos(M_PI * (90 + rotation) / 180.0) * speed;
	}
}

void Movement::computeLookAtPoint(){
	x_rot = x_move - (float)sin(M_PI * rotation / 180.0f);
	y_rot = (float)sin(M_PI * y_rotation / 180.0f);
	z_rot = z_move - (float)cos(M_PI * rotation / 180.0f);
}

float Movement::getXDir(){
	return (float)-sin(M_PI * rotation / 180.0f);
}

float Movement::getYDir(){
	return (float)sin(M_PI * y_rotation / 180.0f);
}

float Movement::getZDir(){
	return (float)-cos(M_PI * rotation / 180.0f);
}

void Movement::addPointToObjects(float x, float z, bool cabinet){
	if (cabinet){
		cabinets.push_back(x);
		cabinets.push_back(z);
	}
	objects.push_back(x);
	objects.push_back(z);
}

float Movement::getXMove(){
	return x_move;
}
float Movement::getZMove(){
	return z_move;
}
float Movement::getRotation(){
	return rotation;
}
float Movement::getYRotation(){
	return y_rotation;
}
float Movement::getXRot(){
	return x_rot;
}
float Movement::getYRot(){
	return y_rot;
}
float Movement::getZRot(){
	return z_rot;
}
void Movement::setRotation(float rot){
	rotation = rot;
	rotation = fmod(rotation, 360.0f);
}
bool Movement::getAbleToOpenCloseCabinets(){
	return ableToOpenCloseCabinets;
}



void Movement::setYRotation(float y_rot){
	y_rotation = y_rot;
	if (y_rotation > 80) y_rotation = 80;
	if (y_rotation < -80) y_rotation = -80;
}

bool Movement::isObjectInWay(float x, float z){
	bool isX = true;
	float x_v = 0;
	float z_v = 0;
	float dist = 0;
	ableToOpenCloseCabinets = false;
	for (std::vector<float>::iterator it = cabinets.begin(); it != cabinets.end(); ++it) {
		if (isX){
			x_v = *it;
		}
		else{
			z_v = *it;
			dist = sqrtf((x_v - x)*(x_v - x) + (z_v - z)*(z_v - z));
			if (dist < 100){
				ableToOpenCloseCabinets = true;
				break;
			}
		}
		isX = !isX;
	}
	isX = true;
	for (std::vector<float>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if (isX){
			x_v = *it;
		}
		else{
			z_v = *it;
			dist = sqrtf((x_v - x)*(x_v - x) + (z_v - z)*(z_v - z));
			if (dist < 8){
				return true;
			}
		}
		isX = !isX;
	}
	return false;
}