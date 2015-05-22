#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "Lamp.h"
#include "colors.h"

Lamp::Lamp(){
	lamp = new ObjLoader();
	lamp = lamp->loadObject("lamp");
	listId = glGenLists(1);
	glNewList(listId, GL_COMPILE);
	vector<Vector3f> vertices = lamp->GetVertices();
	vector<Vector3f> normals = lamp->GetNormals();
	vector<Triangle> triangles = lamp->GetTriangles();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lamp_color);
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
}

Lamp::~Lamp(){
	free(lamp);
}

void Lamp::draw(bool first_render){
	glCallList(listId);
}