#include "Cabinet.h"
#include "Movement.h"
#include "colors.h"
#include <limits>
#include <ostream>

Cabinet::Cabinet(Movement* m){
	this->m = m;
	cabinet = new ObjLoader();
	cabinet_leftdoor = new ObjLoader();
	cabinet_rightdoor = new ObjLoader();
	cabinet = cabinet->loadObject("cabinet");
	cabinet_leftdoor = cabinet_leftdoor->loadObject("cabinet-leftdoor");
	cabinet_rightdoor = cabinet_rightdoor->loadObject("cabinet-rightdoor");
	x_min = std::numeric_limits<float>::max();
	x_max = std::numeric_limits<float>::min();
	z_min = x_min;
	z_max = x_max;
	
	listId = glGenLists(1);
	glNewList(listId, GL_COMPILE);
	vector<Vector3f> vertices = cabinet->GetVertices();
	vector<Vector3f> normals = cabinet->GetNormals();
	vector<Vector2f> textures = cabinet->GetTextures();
	vector<Triangle> triangles = cabinet->GetTriangles();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);
	glBegin(GL_TRIANGLES);
	for (std::vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		setMinMax(vertices[it->v0].x, vertices[it->v0].z);
		glNormal3f(normals[it->n0].x, normals[it->n0].y, normals[it->n0].z);
		glTexCoord2f(textures[it->t0].x, textures[it->t0].y);
		glVertex3f(vertices[it->v0].x, vertices[it->v0].y, vertices[it->v0].z);
		setMinMax(vertices[it->v1].x, vertices[it->v1].z);
		glNormal3f(normals[it->n1].x, normals[it->n1].y, normals[it->n1].z);
		glTexCoord2f(textures[it->t1].x, textures[it->t1].y);
		glVertex3f(vertices[it->v1].x, vertices[it->v1].y, vertices[it->v1].z);
		setMinMax(vertices[it->v2].x, vertices[it->v2].z);
		glNormal3f(normals[it->n2].x, normals[it->n2].y, normals[it->n2].z);
		glTexCoord2f(textures[it->t2].x, textures[it->t2].y);
		glVertex3f(vertices[it->v2].x, vertices[it->v2].y, vertices[it->v2].z);
	}
	glEnd();

	vertices = cabinet_rightdoor->GetVertices();
	normals = cabinet_rightdoor->GetNormals();
	textures = cabinet_rightdoor->GetTextures();
	triangles = cabinet_rightdoor->GetTriangles();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cabinet_door_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);
	glBegin(GL_TRIANGLES);
	for (std::vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		setMinMax(vertices[it->v0].x, vertices[it->v0].z);
		glNormal3f(normals[it->n0].x, normals[it->n0].y, normals[it->n0].z);
		glTexCoord2f(textures[it->t0].x, textures[it->t0].y);
		glVertex3f(vertices[it->v0].x, vertices[it->v0].y, vertices[it->v0].z);
		setMinMax(vertices[it->v1].x, vertices[it->v1].z);
		glNormal3f(normals[it->n1].x, normals[it->n1].y, normals[it->n1].z);
		glTexCoord2f(textures[it->t1].x, textures[it->t1].y);
		glVertex3f(vertices[it->v1].x, vertices[it->v1].y, vertices[it->v1].z);
		setMinMax(vertices[it->v2].x, vertices[it->v2].z);
		glNormal3f(normals[it->n2].x, normals[it->n2].y, normals[it->n2].z);
		glTexCoord2f(textures[it->t2].x, textures[it->t2].y);
		glVertex3f(vertices[it->v2].x, vertices[it->v2].y, vertices[it->v2].z);
	}
	glEnd();
	glEndList();

	listId_leftdoor = glGenLists(1);
	glNewList(listId_leftdoor, GL_COMPILE); 
	vertices = cabinet_leftdoor->GetVertices();
	normals = cabinet_leftdoor->GetNormals();
	textures = cabinet_leftdoor->GetTextures();
	triangles = cabinet_leftdoor->GetTriangles();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cabinet_door_color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);
	glBegin(GL_TRIANGLES);
	for (std::vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		setMinMax(vertices[it->v0].x, vertices[it->v0].z);
		glNormal3f(normals[it->n0].x, normals[it->n0].y, normals[it->n0].z);
		glTexCoord2f(textures[it->t0].x, textures[it->t0].y);
		glVertex3f(vertices[it->v0].x, vertices[it->v0].y, vertices[it->v0].z);
		setMinMax(vertices[it->v1].x, vertices[it->v1].z);
		glNormal3f(normals[it->n1].x, normals[it->n1].y, normals[it->n1].z);
		glTexCoord2f(textures[it->t1].x, textures[it->t1].y);
		glVertex3f(vertices[it->v1].x, vertices[it->v1].y, vertices[it->v1].z);
		setMinMax(vertices[it->v2].x, vertices[it->v2].z);
		glNormal3f(normals[it->n2].x, normals[it->n2].y, normals[it->n2].z);
		glTexCoord2f(textures[it->t2].x, textures[it->t2].y);
		glVertex3f(vertices[it->v2].x, vertices[it->v2].y, vertices[it->v2].z);
	}
	glEnd();
	glEndList();
}

Cabinet::~Cabinet(){
	free(cabinet);
	free(cabinet_leftdoor);
	free(cabinet_rightdoor);
}

void Cabinet::draw(bool first_render, float angle, GLuint texture){
	if (first_render){
		GLfloat mat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, mat);
		float x_diff = mat[12];
		float z_diff = mat[14];
		float x_mi = x_min - x_diff;
		float x_ma = x_max - x_diff;
		float z_mi = z_min - z_diff;
		float z_ma = z_max - z_diff;
		for (float x = x_mi; x < x_ma; x += 5){
			m->addPointToObjects(x, z_mi, true);
			m->addPointToObjects(x, z_ma, true);
		}
		for (float z = z_mi; z < z_ma; z += 5){
			m->addPointToObjects(x_mi, z, true);
			m->addPointToObjects(x_ma, z, true);
		}
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glCallList(listId);
	glTranslatef(-60.0f, 0.0f, 30.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glCallList(listId_leftdoor);
	glDisable(GL_TEXTURE_2D);
}

void Cabinet::setMinMax(float x, float z){
	if (x < x_min){
		x_min = x;
	}
	if (x > x_max){
		x_max = x;
	}
	if (z < z_min){
		z_min = z;
	}
	if (z > z_max){
		z_max = z;
	}
}