#ifndef _ROOM_H_	//guard against cyclic dependancy
#define _ROOM_H_

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

class Room{
public:
	float verts[8][3] ;
	GLubyte* tex; //texture
	GLubyte* tex_sub; //sub texture
	int width, height, maxi;

	int width_sub, height_sub, maxi_sub;
	float x,y,tx,ty,xcos,ysin,radian,radius;

	float focalPoint[3];

	Room(int roomType,char* textureName,char* subTextureName);
	void drawPolygon(int a, int b, int c, int d, float v[8][3],int side,int face);
	void cube(float v[8][3],int wall);
	void drawBox(float* c, float w, float h, float d,int wall);
	void drawLight(int i);
	void drawRoom(float* c, float w, float h, float d,float* lights,float* cutoffs);
	void drawConnector(float* c, float w, float h, float d,float* lights);
	void drawStartRoom(float* c, float w, float h, float d,float* lights);

};

GLubyte* LoadPPM(char* file, int* width, int* height, int* max);

#endif
