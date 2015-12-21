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
#include "Room.h"

float verts[8][3] = { {-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
//have variables for up to 5 lights
GLubyte* tex; //texture
GLubyte* tex_sub; //sub texture
int width, height, maxi;

int width_sub, height_sub, maxi_sub;
float x,y,tx,ty,xcos,ysin,radian,radius;
float angle = 0.0f;

float focalPoint[3];

/* LIGHTING */
GLenum lights_array[] = {GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6};
int lights_enabled[] = {0,0,0,0,0,0};
float light_pos[6][4] = {-1.0,15.0,-10.0,1.0,-1.0,15.0,-10.0,1.0,-1.0,15.0,-10.0,1.0,-1.0,15.0,-10.0,1.0,-1.0,15.0,-10.0,1.0,-1.0,15.0,-10.0,1.0};
float lightcutoff[6] = {30.0,30.0,30.0,30.0,30.0,30.0};
float amb0[4] = {1,1,1,1};
float diff0[4] = {1,1,1,1};
float spec0[4] = {1,1,1,1};
float  spotDir[] = { 0.0f, -1.0f, 0.0f };

/*Background Lights*/
//float light_pos01[] = {0.0,10.0,0.0,0.0};
//float amb01[4] = {0.1,0.1,0.1,1};
//float diff01[4] = {0.1,0.1,0.1,1};
//float spec01[4] = {0.1,0.1,0.1,1};
//should not be in this section, move backround lights to main

Room::Room(int roomType,char* textureName,char* subTextureName){
	tex = LoadPPM(textureName, &width, &height, &maxi);
	tex_sub = LoadPPM(subTextureName, &width_sub, &height_sub, &maxi_sub);
}


/* drawPolygon - takes 4 indices and an array of vertices
 *   and draws a polygon using the vertices indexed by the indices
 */
void Room::drawPolygon(int a, int b, int c, int d, float v[8][3],int side,int face){
	glBegin(GL_POLYGON);

		if(side == 0||side == 5){ //floor
			glNormal3f(0,1,0);
		}
		else if(side == 1||side == 4){ //left wall
			glNormal3f(0,1,0);
		}
		else if(side == 2 ||side ==3){ //right wall
			glNormal3f(0,1,0);

		}
		
		if(side ==4 && face ==1){
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(v[d]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(v[c]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(v[b]);
			glTexCoord2f(0.0, 0.0);
			glVertex3fv(v[a]);
			glTexCoord2f(0.0, 1.0);
		}
		else if(side ==3 && face ==1){
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(v[d]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(v[c]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(v[b]);
			glTexCoord2f(0.0, 0.0);
			glVertex3fv(v[a]);
			glTexCoord2f(0.0, 1.0);
		}
		else{
			glTexCoord2f(0.0, 1.0);
			glVertex3fv(v[a]);
			glTexCoord2f(1.0, 1.0);
			glVertex3fv(v[b]);
			glTexCoord2f(1.0, 0.0);
			glVertex3fv(v[c]);
			glTexCoord2f(0.0, 0.0);
			glVertex3fv(v[d]);
		}
	glEnd();
}

/* cube - takes an array of 8 vertices, and draws 6 faces
 *  with drawPolygon, making up a box
 */
void Room::cube(float v[8][3],int wall)
{
	if(wall == 3 || wall == 2){
	drawPolygon(0, 3, 2, 1, v,wall,1);
	drawPolygon(1, 0, 4, 5, v,wall,0);
	drawPolygon(5, 1, 2, 6, v,wall,0);
	drawPolygon(2, 3, 7, 6, v,wall,0);
	drawPolygon(6, 5, 4, 7, v,wall,1);
	drawPolygon(4, 0, 3, 7, v,wall,0);
	}	
	else{
	drawPolygon(0, 3, 2, 1, v,wall,0);
	drawPolygon(1, 0, 4, 5, v,wall,1);
	drawPolygon(5, 1, 2, 6, v,wall,0);
	drawPolygon(2, 3, 7, 6, v,wall,1);
	drawPolygon(6, 5, 4, 7, v,wall,0);
	drawPolygon(4, 0, 3, 7, v,wall,0);
	}	
}

/* drawBox - takes centre point, width, height and depth of a box,
 *  calculates its corner vertices, and draws it with the cube function
 */
void Room::drawBox(float* c, float w, float h, float d,int wall) //([0,0,0],10,1,10)
{
   //set texture
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,w,h, 0, GL_RGB,GL_UNSIGNED_BYTE, tex);


	float vertices[8][3] = { {c[0]-w/2, c[1]-h/2, c[2]+d/2},
							 {c[0]-w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]+d/2}, 
							 {c[0]-w/2, c[1]-h/2, c[2]-d/2}, 
							 {c[0]-w/2, c[1]+h/2, c[2]-d/2}, 
							 {c[0]+w/2, c[1]+h/2, c[2]-d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]-d/2} };

	cube(vertices,wall);
}
//draw a light in the Room
void Room::drawLight(int i){

	glLightfv(lights_array[i],GL_POSITION,light_pos[i]);
	glLightf(lights_array[i],GL_SPOT_CUTOFF,lightcutoff[i]);
	glLightfv(lights_array[i],GL_SPOT_DIRECTION,spotDir);
	//all lights are the same for now
    glLightfv(lights_array[i], GL_AMBIENT, amb0);
    glLightfv(lights_array[i], GL_DIFFUSE, diff0);
    glLightfv(lights_array[i], GL_SPECULAR, spec0);
    
    //draw light ball
    glPushMatrix();
	glTranslatef(light_pos[i][0],light_pos[i][1],light_pos[i][2]);
	glutSolidSphere(0.2, 12, 10);
	glPopMatrix();

	//draw the 2Dcircle on the ground
	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_sub, height_sub, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_sub); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_POLYGON);
	radius = (light_pos[i][1]-1)*(float)tan(lightcutoff[i]*M_PI/180.0f);
	glNormal3f(0,1,0);
    for (angle=360.0; angle>0.0; angle-=2.0)
    {
    	radian = angle * (M_PI /180.0f);

		xcos = (float)cos(radian);
		ysin = (float)sin(radian);
		x = xcos * radius  + light_pos[i][0]; //need to change to center of spotlight, and size of spotlight
		y = ysin * radius  + light_pos[i][2]; //need to change to center of spotlight, and size of spotlight
		tx = xcos * 0.5 + 0.5;
		ty = ysin * 0.5 + 0.5;
		glTexCoord2f(tx, ty);
		glVertex3f(x,0.6,y);
	}

    glEnd();
    glDisable(GL_TEXTURE_2D);

}
//Typically the following would be child classes
void Room::drawRoom(float* c, float w, float h, float d,float* lights,float* cutoffs){

	//draw room
	//set texture properties

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	focalPoint[0]= c[0];
	focalPoint[1] = c[1];
	focalPoint[2] = c[2];

	this->drawBox(focalPoint,w,h,d,0); //draw floor

	focalPoint[0] = focalPoint[0] - w/2.0;
	focalPoint[1] = focalPoint[1] + h /2.0 + w/4.0 +0.1;
	this->drawBox(focalPoint,h,w/2.0,d,1); //draw right wall

	focalPoint[0] *= -1.0;
	this->drawBox(focalPoint,h,w/2.0,d,4); //draw left wall
	//create temp walls

	//this->drawBox(focalPoint,d,w/2.0,h,3);
	if(w > 10){
		float newD = (w - 10.0) /2;
		focalPoint[0] -= newD;
		focalPoint[2] = (d)/2 -5; //3

		this->drawBox(focalPoint,newD,w/2.0,h/2,3); //front

		focalPoint[2] = -((d)/2 +5);
		this->drawBox(focalPoint,newD,w/2.0,h/2,2);

		focalPoint[0] -= (10);
		this->drawBox(focalPoint,newD,w/2.0,h/2,2);
		//focalPoint[2] = w/2 -h;

		focalPoint[2] = (d)/2 -5;
		this->drawBox(focalPoint,newD,w/2,h/2,3); //front

	}
	glDisable(GL_TEXTURE_2D);

	//draw lights
	glEnable(GL_LIGHTING);
	for(int i = 0; i < 6; i++){
		if(lights[0+i*3] != 0 || lights[1+i*3] != 0|| lights[2+i*3] != 0){
			glEnable(lights_array[i]); //turn on this light
			lights_enabled[i] = 1; //show that this light is enabled
			//set the lights position
			light_pos[i][0] = lights[0+i*3];
			light_pos[i][1] = lights[1+i*3];
			light_pos[i][2] = lights[2+i*3];
			light_pos[i][3] = 1.0;
			lightcutoff[i] = cutoffs[i];

			drawLight(i);
		}
	}

}

void Room::drawConnector(float* c, float w, float h, float d,float* lights){

	//draw room
	//set texture properties

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	focalPoint[0]= c[0];
	focalPoint[1] = c[1];
	focalPoint[2] = c[2];

	this->drawBox(focalPoint,w,h,d,0); //draw floor

	focalPoint[0] = focalPoint[0] - w/2.0;
	focalPoint[1] = focalPoint[1] + h /2.0 + w/4.0 +0.1;
	this->drawBox(focalPoint,h,w/2.0,d,1); //draw right wall

	focalPoint[0] *= -1.0;
	//this->drawBox(focalPoint,h,w/2.0,d,4); //draw left wall
	//draw back wall
	focalPoint[0] -= focalPoint[0];
	focalPoint[2] += focalPoint[2];
	this->drawBox(focalPoint,d,w/2.0,h,2);

	glDisable(GL_TEXTURE_2D);
}

void Room::drawStartRoom(float* c, float w, float h, float d,float* lights){

	//draw room
	//set texture properties

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	focalPoint[0]= c[0];
	focalPoint[1] = c[1];
	focalPoint[2] = c[2];

	this->drawBox(focalPoint,w,h,d,0); //draw floor

	focalPoint[0] = focalPoint[0] - w/2.0;
	focalPoint[1] = focalPoint[1] + h /2.0 + w/4.0 +0.1;
	this->drawBox(focalPoint,h,w/2.0,d,1); //draw right wall

	focalPoint[0] *= -1.0;
	this->drawBox(focalPoint,h,w/2.0,d,4); //draw left wall

	//draw back wall
	focalPoint[0] -= focalPoint[0];
	focalPoint[2] -= focalPoint[2];
	this->drawBox(focalPoint,d,w/2.0,h,3);
	//draw side walls

	glDisable(GL_TEXTURE_2D);

}