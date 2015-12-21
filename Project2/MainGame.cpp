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
#include <vector>
#include <time.h>

#include "Room.h"
#include "Ghost.h"

using namespace std;
/*
Group Members: 	Karl Knopf (1437217)
         	 	Syed Gardezi (1074314)
          		Alexander Guerrero (1133763)


Welcome to Night Light! You are a ghost trying to escape an haunted
mansion in order release your spirit and rest in peace. Ghosts do not
like light and will "spooked" if they are hit by too much of it.
Navitage through the corridors, avoid the light, free your spirit
and win the game!
*/

float pos[] = {0,+1,-3};
double viewPop[3];
float rot[] = {0, 0, 0};

float headRot[] = {0, 0, 0};

float camPos[] = {3.4,9,8.1};
float target[] = {0.0,0.0,0.0};
int lumenenceValue[1];

//Temp storage stuff
double modelViewMatrixStorage[16];
double modelProjectionMatrixStorage[16];
int modelViewportStorage[4];

//vector of rooms
vector <Room*> rooms;
int state;

float light_pos1[] = {0.0,10.0,-1.0,0.0};
float amb01[4] = {0.25,0.25,0.25,0};
float diff01[4] = {0.25,0.25,0.25,0};
float spec01[4] = {0.25,0.25,0.25,0};

float lightcutoffs[6] = {30.0,30.0,30.0,30.0,30.0,30.0};

//time functions
clock_t cl;
clock_t cur;
int timer;

Ghost ghost;

GLubyte* tex_Start; //sub texture
int width_start, height_start, maxi_start;

GLubyte* tex_End; //sub texture
int width_end, height_end, maxi_end;

GLubyte* tex_Dead; //sub texture
int width_dead, height_dead, maxi_dead;

/* LoadPPM -- loads the specified ppm file, and returns the image data as a GLubyte 
 *  (unsigned byte) array. Also returns the width and height of the image, and the
 *  maximum colour value by way of arguments
 *  usage: GLubyte myImg = LoadPPM("myImg.ppm", &width, &height, &max);
 */

GLubyte* LoadPPM(char* file, int* width, int* height, int* max)
{
	GLubyte* img;
	FILE *fd;
	int n, m;
	int  k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;
	
	fd = fopen(file, "r");
	fscanf(fd,"%[^\n] ",b);
	if(b[0]!='P'|| b[1] != '3')
	{
		printf("%s is not a PPM file!\n",file); 
		exit(0);
	}
	printf("%s is a PPM file\n", file);
	fscanf(fd, "%c",&c);
	while(c == '#') 
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd); 
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	nm = n*m;

	img = (GLubyte*)(malloc(3*sizeof(GLuint)*nm));


	s=255.0/k;


	for(i=0;i<nm;i++) 
	{
		fscanf(fd,"%d %d %d",&red, &green, &blue );
		img[3*nm-3*i-3]=red*s;
		img[3*nm-3*i-2]=green*s;
		img[3*nm-3*i-1]=blue*s;
	}

	*width = n;
	*height = m;
	*max = k;

	return img;
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;

		case 'a':
		case 'A':
			if(state ==1 || state ==5){
				camPos[0] -= 0.3*0.25;
				pos[0] -= 0.3*0.25;
				rot[1] = -90;
				ghost.move("right");
			}
			if(state ==2){
				camPos[2] -= 0.3*0.25;
				pos[2] -= 0.3*0.25;
				rot[1] = 180;
				ghost.move("backward");
			}
			if(state ==3){
				camPos[0] += 0.3*0.25;
				pos[0] += 0.3*0.25;
				rot[1] = 90;
				ghost.move("left");
			}
			if(state ==4){
				camPos[2] += 0.3*0.25;
				pos[2] += 0.3*0.25;
				rot[1] = 0;
				ghost.move("forward");
			}
			break;

		case 'w':
		case 'W':
			if(state == 1|| state ==5){
				camPos[2] -= 0.3*0.25;
				pos[2] -= 0.3*0.25;
				rot[1] = 180;
				ghost.move("backward");
			}
			if(state ==2){
				camPos[0] += 0.3*0.25;
				pos[0] += 0.3*0.25;
				rot[1] = 90;
				ghost.move("left");
			}
			if(state ==3){
				camPos[2] += 0.3*0.25;
				pos[2] += 0.3*0.25;
				rot[1] = 0;
				ghost.move("forward");
			}
			if(state ==4){
				camPos[0] -= 0.3*0.25;
				pos[0] -= 0.3*0.25;
				rot[1] = -90;
				ghost.move("right");
			}
			break;

		case 'd':
		case 'D':
			if(state == 1|| state ==5){
				camPos[0] += 0.3*0.25;
				pos[0]+=0.3*0.25;
				rot[1] = 90;
				ghost.move("left");
			}
			if(state ==2){
				camPos[2] += 0.3*0.25;
				pos[2] += 0.3*0.25;
				rot[1] = 0;
				ghost.move("forward");
			}
			if(state ==3){
				camPos[0] -= 0.3*0.25;
				pos[0] -= 0.3*0.25;
				rot[1] = -90;
				ghost.move("right");
			}
			if(state ==4){
				camPos[2] -= 0.3*0.25;
				pos[2] -= 0.3*0.25;
				rot[1] = 180;
				ghost.move("backward");
			}
			break;

		case 's':
		case 'S':
			if(state == 1|| state ==5){
				camPos[2] += 0.3*0.25;
				pos[2] += 0.3*0.25;
				rot[1] = 0;
				ghost.move("forward");
			}
			if(state ==2){
				camPos[0] -= 0.3*0.25;
				pos[0] -= 0.3*0.25;
				rot[1] = -90;
				ghost.move("right");
			}
			if(state ==3){
				camPos[2] -= 0.3*0.25;
				pos[2] -= 0.3*0.25;
				rot[1] = 180;
				ghost.move("backward");
			}
			if(state ==4){
				camPos[0] += 0.3*0.25;
				pos[0] += 0.3*0.25;
				rot[1] = 90;
				ghost.move("left");
			}
			break;

		case 'y':
		case 'Y':
			if(headRot[1] < 85)
				headRot[1] += 1;
			break;

		case 'u':
		case 'U':
			if(headRot[1] > -85)
				headRot[1] -= 1;
			break;
		case 32:
			if(state == 0){
				state = 1;
			}
			if(state == 5){
				camPos[0] = 3.4;
				camPos[1] = 9;
				camPos[2] = 8.1;
				pos[0] = 0;
				pos[1] = 1;
				pos[2] = -3;
				light_pos1[0] = 0.0;
				light_pos1[1] = 10.0;
				light_pos1[2] = -1.0;
				ghost = Ghost(0,0,0.3,"backward");
				state = 1;
			}
			if(state == 6){
				camPos[0] = 3.4;
				camPos[1] = 9;
				camPos[2] = 8.1;
				pos[0] = 0;
				pos[1] = 1;
				pos[2] = -3;
				light_pos1[0] = 0.0;
				light_pos1[1] = 10.0;
				light_pos1[2] = -1.0;
				ghost = Ghost(0,0,0.3,"backward");
				state = 1;
			}
			break;
			
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch(key)
	{
		case GLUT_KEY_LEFT:
			camPos[0]-=0.1;
			break;

		case GLUT_KEY_RIGHT:
			camPos[0]+=0.1;
			break;

		case GLUT_KEY_UP:
			camPos[2] -= 0.1;
			break;

		case GLUT_KEY_DOWN:
			camPos[2] += 0.1;
			break;
		
		case GLUT_KEY_HOME:
			camPos[1] += 0.1;
			break;

		case GLUT_KEY_END:
			camPos[1] -= 0.1;
			break;

	}
	glutPostRedisplay();
}


void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	glEnable(GL_BLEND); //?
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Room *startRoom = new Room(2,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(startRoom);
	Room *firstRoom = new Room(0,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(firstRoom);
	Room *firstConnectorRoom = new Room(1,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(firstConnectorRoom);
	Room *secondRoom = new Room(0,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(secondRoom);
	Room *secondConnectorRoom = new Room(1,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(secondConnectorRoom);
	Room *thirdRoom = new Room(0,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(thirdRoom);
	Room *thirdConnectorRoom = new Room(1,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(thirdConnectorRoom);
	Room *fourthRoom = new Room(0,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(fourthRoom);
	Room *fourthConnectorRoom = new Room(1,"concrete.ppm","concrete-light.ppm");
	rooms.push_back(fourthConnectorRoom);
	cl = clock();
}

void checkState(float pos[]){
		if(state == 1 && pos[2] < -36){
			state = 2;
			camPos[0] = pos[0] -10.4; //0
			camPos[2] = pos[2] - 2.1; //-30
		}

		if(state == 2 && pos[0] > 27){
			state = 3;
			camPos[0] = pos[0] +5.4; //0
			camPos[2] = pos[2] - 10; //-30
		}

		if(state == 3 && pos[2] > 12){
			state = 4;
			camPos[0] = pos[0] +10.4; //0
			camPos[2] = pos[2] + 3; //-30
		}

		if(state == 4 && pos[0] < 0){
			state = 5;

		}


}

/*checkDeath- checks if you are dead
*/

void checkDeath(float pos[]){
	glGetDoublev(GL_MODELVIEW_MATRIX,modelViewMatrixStorage);
	glGetDoublev(GL_PROJECTION_MATRIX,modelProjectionMatrixStorage);
	glGetIntegerv(GL_VIEWPORT,modelViewportStorage);

	gluProject(pos[0],pos[1],pos[2],modelViewMatrixStorage,modelProjectionMatrixStorage,modelViewportStorage, &viewPop[0], &viewPop[1], &viewPop[2]);
	glReadPixels(viewPop[0],viewPop[1],1,1,GL_RGBA,GL_FLOAT,lumenenceValue);
	if(lumenenceValue[0] > 1060000000){
		state = 6; 
		printf("Dead \n") ;
	}

}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{	
	float origin[3] = {0,0,-5};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(state ==0 || state == 5 || state ==6){
		gluLookAt(2.0, 0, 0, 0,0,0, 0,1,0);
	}
	else{
		gluLookAt(camPos[0], camPos[1], camPos[2], pos[0],pos[1],pos[2], 0,1,0);
	}

	glPushMatrix();
	glTranslatef(light_pos1[0],light_pos1[1],light_pos1[2]);
	glutSolidSphere(0.2, 12, 10);
	glPopMatrix();

	glLightfv(GL_LIGHT0,GL_POSITION,light_pos1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb01);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff01);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec01);
   	
   	if(state == 0){
   		glEnable(GL_TEXTURE_2D); 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_start, height_start, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_Start); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   		glBegin(GL_QUADS);
   		glNormal3f(1,0,0);
		glTexCoord2f(0, 0);
		glVertex3f(0,-1,-1);
		glTexCoord2f(0,1);
		glVertex3f(0,1,-1);
		glTexCoord2f(1, 1);
		glVertex3f(0,1,1);
		glTexCoord2f(1, 0);
		glVertex3f(0,-1,1);

		glEnd();
   		glDisable(GL_TEXTURE_2D);
   	}
   	if(state == 5){
   		glEnable(GL_TEXTURE_2D); 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_end, height_end, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_End); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   		glBegin(GL_QUADS);
   		glNormal3f(1,0,0);
		glTexCoord2f(0, 0);
		glVertex3f(0,-1,-1);
		glTexCoord2f(0,1);
		glVertex3f(0,1,-1);
		glTexCoord2f(1, 1);
		glVertex3f(0,1,1);
		glTexCoord2f(1, 0);
		glVertex3f(0,-1,1);

		glEnd();
   		glDisable(GL_TEXTURE_2D);
   	}
   	if(state == 6){
   		glEnable(GL_TEXTURE_2D); 
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_dead, height_dead, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_Dead); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   		glBegin(GL_QUADS);
   		glNormal3f(1,0,0);
		glTexCoord2f(0, 0);
		glVertex3f(0,-1,-1);
		glTexCoord2f(0,1);
		glVertex3f(0,1,-1);
		glTexCoord2f(1, 1);
		glVertex3f(0,1,1);
		glTexCoord2f(1, 0);
		glVertex3f(0,-1,1);

		glEnd();
   		glDisable(GL_TEXTURE_2D);
   	}

	if(state == 1){ //initial state after start
		//set background light position
		light_pos1[0] = 0.0;
		light_pos1[1] = 10.0;
		light_pos1[2] = -1.0; 
		glLightfv(GL_LIGHT0,GL_POSITION,light_pos1);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb01);
   	 	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff01);
   	 	glLightfv(GL_LIGHT0, GL_SPECULAR, spec01);


		float startLights[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
		glPushMatrix();
			rooms[0]->drawStartRoom(origin, 10.0, 1.0, 10.0,startLights);
		glPopMatrix();

		startLights[0] = -4.0;
		startLights[1] = 8.0;
		startLights[2] = -5.0;
		lightcutoffs[0] = 30.0;
		glPushMatrix();
			glTranslatef(0.0,0.0,-15.0);
			rooms[1]->drawRoom(origin,10.0, 1.0, 20.0,startLights,lightcutoffs);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0,0.0,-30.0);
			rooms[2]->drawConnector(origin,10.0, 1.0, 10.0,startLights);
		glPopMatrix();
	}
	if(state == 2){
		//set background light position 
		light_pos1[0] = -1.0;
		light_pos1[1] = 10.0;
		light_pos1[2] = -15.0; 
		glLightfv(GL_LIGHT0,GL_POSITION,light_pos1);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb01);
   	 	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff01);
   	 	glLightfv(GL_LIGHT0, GL_SPECULAR, spec01);

   	 	float startLights[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
   	 	startLights[0] = -4.0;
		startLights[1] = 8.0;
		startLights[2] = -5.0;
		lightcutoffs[0] = 30.0;
		glPushMatrix();
			glTranslatef(0.0,0.0,-15.0);
			rooms[1]->drawRoom(origin,10.0, 1.0, 20.0,startLights,lightcutoffs);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0,0.0,-30.0);
			rooms[2]->drawConnector(origin,10.0, 1.0, 10.0,startLights);
		glPopMatrix();
		//free lights
		startLights[0] = 0.0;
		startLights[1] = 0.0;
		startLights[2] = 0.0;
		//set new lights
		startLights[3] = 0.0;
		startLights[4] = 8.0;
		startLights[5] = -10.0;
		startLights[6] = 0.0;
		startLights[7] = 8.0;
		startLights[8] = 0.0;
		lightcutoffs[1] = 20.0;
		lightcutoffs[2] = 20.0;
		glPushMatrix();
			glTranslatef(+20.0,0.0,-35.0);
			glRotatef(90,0,1,0);
			rooms[3]->drawRoom(origin,12.0, 1.0, 20.0,startLights,lightcutoffs);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(25.0,0.0,-35.0);
			glRotatef(270,0,1,0);
			rooms[4]->drawConnector(origin,10.0, 1.0, 10.0,startLights);
		glPopMatrix();
	}
	if(state == 3){
		//set background light position 
		light_pos1[0] = 35.0;
		light_pos1[1] = 10.0;
		light_pos1[2] = -16.0; 
		glLightfv(GL_LIGHT0,GL_POSITION,light_pos1);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb01);
   	 	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff01);
   	 	glLightfv(GL_LIGHT0, GL_SPECULAR, spec01);
   	 	float startLights[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

		//set new lights
		startLights[3] = 0.0;
		startLights[4] = 8.0;
		startLights[5] = -10.0;
		startLights[6] = 0.0;
		startLights[7] = 8.0;
		startLights[8] = 0.0;
		lightcutoffs[1] = 20.0;
		lightcutoffs[2] = 20.0;
		glPushMatrix();
			glTranslatef(+20.0,0.0,-35.0);
			glRotatef(90,0,1,0);
			rooms[3]->drawRoom(origin,12.0, 1.0, 20.0,startLights,lightcutoffs);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(25.0,0.0,-35.0);
			glRotatef(270,0,1,0);
			rooms[4]->drawConnector(origin,10.0, 1.0, 10.0,startLights);
		glPopMatrix();
		//free other lights
		startLights[3] = 0.0;
		startLights[4] = 0.0;
		startLights[5] = 0.0;
		startLights[6] = 0.0;
		startLights[7] = 0.0;
		startLights[8] = 0.0;
		//set lights for room
		startLights[0] = -7.0;
		startLights[1] = 10.0;
		startLights[2] = -13.0;
		startLights[9] = +7.0;
		startLights[10] = 10.0;
		startLights[11] = -13.0;

		startLights[12] = -3.0;
		startLights[13] = 5.0;
		startLights[14] = +5.0;
		startLights[15] = 3.0;
		startLights[16] = 5.0;
		startLights[17] = +5.0;
		lightcutoffs[0] = 33.0;
		lightcutoffs[3] = 33.0;
		lightcutoffs[4] = 20.0;
		lightcutoffs[5] = 20.0;
		glPushMatrix();
			glTranslatef(30.0,0.0,-15.0);
			glRotatef(180,0,1,0);
			rooms[5]->drawRoom(origin,12.0, 1.0, 40.0,startLights, lightcutoffs);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(30.0,0.0,10.0);
			glRotatef(180,0,1,0);
			rooms[6]->drawConnector(origin,10.0, 1.0, 10.0,startLights);
		glPopMatrix();
	}

	if(state == 4){
		//set background light position 
		light_pos1[0] = 35.0;
		light_pos1[1] = 10.0;
		light_pos1[2] = -16.0; 
		glLightfv(GL_LIGHT0,GL_POSITION,light_pos1);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb01);
   	 	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff01);
   	 	glLightfv(GL_LIGHT0, GL_SPECULAR, spec01);
   	 	float startLights[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

   	 	//set lights for room
		startLights[0] = -7.0;
		startLights[1] = 10.0;
		startLights[2] = -13.0;
		startLights[9] = +7.0;
		startLights[10] = 10.0;
		startLights[11] = -13.0;

		startLights[12] = -3.0;
		startLights[13] = 5.0;
		startLights[14] = +5.0;
		startLights[15] = 3.0;
		startLights[16] = 5.0;
		startLights[17] = +5.0;
		lightcutoffs[0] = 33.0;
		lightcutoffs[3] = 33.0;
		lightcutoffs[4] = 20.0;
		lightcutoffs[5] = 20.0;
		glPushMatrix();
			glTranslatef(30.0,0.0,-15.0);
			glRotatef(180,0,1,0);
			rooms[5]->drawRoom(origin,12.0, 1.0, 40.0,startLights, lightcutoffs);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(30.0,0.0,10.0);
			glRotatef(180,0,1,0);
			rooms[6]->drawConnector(origin,10.0, 1.0, 10.0,startLights);
		glPopMatrix();
		//free previous lights
		startLights[0] = 0.0;
		startLights[1] = 0.0;
		startLights[2] = 0.0;
		startLights[9] = 0.0;
		startLights[10] = 0.0;
		startLights[11] = 0.0;

		startLights[12] = 0.0;
		startLights[13] = 0.0;
		startLights[14] = 0.0;
		startLights[15] = 0.0;
		startLights[16] = 0.0;
		startLights[17] = 0.0;
		//set lights for room

		cur = clock();
		timer = cur-cl;

		startLights[3] = 0.0 + (timer%50)/10.0;
		startLights[4] = 8.0;
		startLights[5] = 2.0;
		lightcutoffs[1] = 10.0;

		glPushMatrix();
			glTranslatef(10.0,0.0,15.0);
			glRotatef(270,0,1,0);
			rooms[7]->drawRoom(origin,10.0, 1.0, 20.0,startLights, lightcutoffs);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(5.0,0.0,15.0);
			glRotatef(90,0,1,0);
			rooms[8]->drawConnector(origin,10.0, 1.0, 10.0,startLights);
		glPopMatrix();

	}
	if(state != 0 ){
		ghost.draw();
		checkState(pos);
		checkDeath(pos);
	}
	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{ 
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("NIGHT LIGHT: THE GAME");	//creates the window

	tex_Start = LoadPPM("Start.ppm", &width_start, &height_start, &maxi_start);
	tex_End = LoadPPM("Win.ppm", &width_end, &height_end, &maxi_end);
	tex_Dead = LoadPPM("Spooked.ppm", &width_dead, &height_dead, &maxi_dead);
	state = 0;
	/* LIGHTING */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_CULL_FACE); // Allows backface culling
	glCullFace(GL_BACK);

	ghost = Ghost(0,0,0.3,"backward");

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glEnable(GL_DEPTH_TEST);
	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}