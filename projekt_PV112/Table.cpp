#include "GL/glut.h"
#include "GL/freeglut_ext.h"
#include "Table.h"
#include "Movement.h"
#include "colors.h"

Table::Table(Movement* m){
	this->m = m;
	table = new ObjLoader();
	table = table->loadObject("table");
	x_min = std::numeric_limits<float>::max();
	x_max = std::numeric_limits<float>::min();
	z_min = x_min;
	z_max = x_max;

	listId = glGenLists(1);
	glNewList(listId, GL_COMPILE);
	vector<Vector3f> vertices = table->GetVertices();
	vector<Vector3f> normals = table->GetNormals();
	vector<Vector2f> textures = table->GetTextures();
	vector<Triangle> triangles = table->GetTriangles();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, table_color);
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

Table::~Table(){
	free(table);
}

void Table::draw(bool first_render, GLuint texture){
	if (first_render){
		GLfloat mat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, mat);
		float x_diff = mat[12];
		float z_diff = mat[14];
		x_min -= x_diff;
		x_max -= x_diff;
		z_min -= z_diff;
		z_max -= z_diff;
		for (int x = x_min; x < x_max; x += 5){
			m->addPointToObjects(x, z_min, false);
			m->addPointToObjects(x, z_max, false);
		}
		for (int z = z_min; z < z_max; z += 5){
			m->addPointToObjects(x_min, z, false);
			m->addPointToObjects(x_max, z, false);
		}
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glCallList(listId);
	glDisable(GL_TEXTURE_2D);
}

void Table::setMinMax(float x, float z){
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