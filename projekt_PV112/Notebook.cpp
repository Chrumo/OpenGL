#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "Notebook.h"
#include "colors.h"

Notebook::Notebook(){
	notebook = new ObjLoader();
	display = new ObjLoader();
	notebook = notebook->loadObject("notebook");
	display = display->loadObject("notebook-display");
	listId = glGenLists(1);
	glNewList(listId, GL_COMPILE);
	vector<Vector3f> vertices = notebook->GetVertices();
	vector<Vector3f> normals = notebook->GetNormals();
	vector<Triangle> triangles = notebook->GetTriangles();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, notebook_color);
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


	vertices = display->GetVertices();
	normals = display->GetNormals();
	triangles = display->GetTriangles();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
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

Notebook::~Notebook(){
	free(notebook);
	free(display);
}

void Notebook::draw(bool first_render){
	glCallList(listId);
}