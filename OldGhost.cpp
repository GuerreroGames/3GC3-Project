/* 
 * Based off Snowman sample 
 * by R. Teather
 */

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
#include <stdlib.h>

#include "Ghost.h"

float cols[6][3] = { {1,0,0}, {0,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };

float pos[] = {0,9,0};
float rot[] = {0, 0, 0};
float camPos[] = {-25, 40, -25};
float angle = 0.0f;

float light_pos[] = {0,20,0,1};
float amb[4]  = {1, 1, 1, 1};
float diff[4] = {1, 1, 1, 1};
float spec[4] = {1, 1, 1, 1};

Ghost ghost;

/* drawPolygon - takes 4 indices and an array of vertices
 *   and draws a polygon using the vertices indexed by the indices
 */
void drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}

void drawAxis()
{
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,10,0);
		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,10);
	glEnd();
}

/* cube - takes an array of 8 vertices, and draws 6 faces
 *  with drawPolygon, making up a box
 */
void cube(float v[8][3])
{
	glColor3fv(cols[1]);
	drawPolygon(0, 3, 2, 1, v);

	glColor3fv(cols[2]);
	drawPolygon(1, 0, 4, 5, v);

	glColor3fv(cols[3]);
	drawPolygon(5, 1, 2, 6, v);
	
	glColor3fv(cols[4]);
	drawPolygon(2, 3, 7, 6, v);
	
	glColor3fv(cols[5]);
	drawPolygon(6, 5, 4, 7, v);

	glColor3fv(cols[0]);
	drawPolygon(4, 0, 3, 7, v);
}

/* drawBox - takes centre point, width, height and depth of a box,
 *  calculates its corner vertices, and draws it with the cube function
 */
void drawBox(float* c, float w, float h, float d)
{
	float vertices[8][3] = { {c[0]-w/2, c[1]-h/2, c[2]+d/2},
							 {c[0]-w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]+d/2}, 
							 {c[0]-w/2, c[1]-h/2, c[2]-d/2}, 
							 {c[0]-w/2, c[1]+h/2, c[2]-d/2}, 
							 {c[0]+w/2, c[1]+h/2, c[2]-d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]-d/2} };

	cube(vertices);
}


void keyboard(unsigned char key, int x, int y)
{

	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;

		case 'a':
		case 'A':
			ghost.move("left");
			break;

		case 'w':
		case 'W':
			ghost.move("forward");
			break;

		case 'd':
		case 'D':
			ghost.move("right");
			break;

		case 's':
		case 'S':
			ghost.move("backward");
			break;		

		case 'z':
		case 'Z':
			camPos[1] += 0.5;
			break;	

		case 'x':
		case 'X':
			camPos[1] -= 0.5;
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
			camPos[0]-= 2;
			break;

		case GLUT_KEY_RIGHT:
			camPos[0]+= 2;
			break;

		case GLUT_KEY_UP:
			camPos[2] -= 2;
			break;

		case GLUT_KEY_DOWN:
			camPos[2] += 2;
			break;
	}
	
	glutPostRedisplay();
}

void init(void)
{
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

}
/*
void DrawSnowman(float* pos, float* rot)
{
	glPushMatrix(); // ghost body

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[1], 0, 1, 0);

	glColor3f(1,1,1);
	glutSolidSphere(5, 8, 8);



	glPushMatrix(); // left eye

	glTranslatef(-1.5, 1, 4);
	glColor3f(0,0,0);
	glutSolidSphere(1, 8, 8);

	glPushMatrix(); // eye centre
	glTranslatef(0, 0, 0.8);
	glColor3f(1,1,1);
	glutSolidSphere(0.3, 8, 8);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix(); // right eye

	glTranslatef(1.5, 1, 4);
	glColor3f(0,0,0);
	glutSolidSphere(1, 8, 8);

	glPushMatrix(); // eye centre
	glTranslatef(0, 0, 0.8);
	glColor3f(1,1,1);
	glutSolidSphere(0.3, 8, 8);
	glPopMatrix();

	glPopMatrix();



	glPushMatrix(); // ghost tail

	glTranslatef(0.0, -5, 0.0);
	
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);

		glVertex3f(3.536, 5.0, -3.536);
		glVertex3f(2.337, 3.840, -4.006);
		glVertex3f(0.0, 3.840, -5.471);
		glVertex3f(0.0, 5.0, -5.0);

		glVertex3f(0.0, 5.0, -5.0);
		glVertex3f(0.0, 3.840, -5.471);
		glVertex3f(-2.337, 3.840, -4.006);
		glVertex3f(-3.536, 5.0, -3.536);

		glVertex3f(3.536, 5.0, -3.536);
		glVertex3f(3.266, 3.087, -3.266);
		glVertex3f(1.009, 2.963, -6.363);
		glVertex3f(2.337, 3.840, -4.006);

		glVertex3f(-2.337, 3.840, -4.006);
		glVertex3f(-1.009, 2.963, -6.363);
		glVertex3f(-3.266, 3.087, -3.266);
		glVertex3f(-3.536, 5.0, -3.536);

		glVertex3f(2.337, 3.840, -4.006);
		glVertex3f(1.009, 2.963, -6.363);
		glVertex3f(0.0, 2.963, -7.716);
		glVertex3f(0.0, 3.840, -5.471);

		glVertex3f(0.0, 3.840, -5.471);
		glVertex3f(0.0, 2.963, -7.716);
		glVertex3f(-1.009, 2.963, -6.363);
		glVertex3f(-2.337, 3.840, -4.006);

		glVertex3f(3.266, 3.087, -3.266);
		glVertex3f(2.5, 1.464, -2.5);
		glVertex3f(0.824, 1.454, -5.1);
		glVertex3f(1.009, 2.963, -6.363);

		glVertex3f(-1.009, 2.963, -6.363);
		glVertex3f(-0.824, 1.454, -5.1);
		glVertex3f(-2.5, 1.464, -2.5);
		glVertex3f(-3.266, 3.087, -3.266);

		glVertex3f(1.009, 2.963, -6.363);
		glVertex3f(0.824, 1.454, -5.1);
		glVertex3f(0.0, 1.454, -6.135);
		glVertex3f(0.0, 2.963, -7.716);

		glVertex3f(0.0, 2.963, -7.716);
		glVertex3f(0.0, 1.454, -6.135);
		glVertex3f(-0.824, 1.454, -5.1);
		glVertex3f(-1.009, 2.963, -6.363);

		glVertex3f(2.5, 1.464, -2.5);
		glVertex3f(1.353, 0.381, -1.353);
		glVertex3f(0.605, 0.364, -3.261);
		glVertex3f(0.824, 1.454, -5.1);

		glVertex3f(-0.824, 1.454, -5.1);
		glVertex3f(-0.605, 0.364, -3.261);
		glVertex3f(-1.353, 0.381, -1.353);
		glVertex3f(-2.5, 1.464, -2.5);

		glVertex3f(0.824, 1.454, -5.1);
		glVertex3f(0.605, 0.364, -3.261);
		glVertex3f(0.0, 0.364, -3.821);
		glVertex3f(0.0, 1.454, -6.135);

		glVertex3f(0.0, 1.454, -6.135);
		glVertex3f(0.0, 0.364, -3.821);
		glVertex3f(-0.605, 0.364, -3.261);
		glVertex3f(-0.824, 1.454, -5.1);

		glVertex3f(1.353, 0.381, -1.353);
		glVertex3f(0.0, 0.0, -1.832);
		glVertex3f(0.0, 0.364, -3.821);
		glVertex3f(0.605, 0.364, -3.261);

		glVertex3f(-0.605, 0.364, -3.261);
		glVertex3f(0.0, 0.364, -3.821);
		glVertex3f(0.0, 0.0, -1.832);
		glVertex3f(-1.353, 0.381, -1.353);

		glVertex3f(1.353, 0.381, -1.353);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-1.353, 0.381, -1.353);
		glVertex3f(0.0, 0.0, -1.832);

	glEnd();
	
	glPopMatrix();

	glPopMatrix();
}
*/

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{	

	float m_amb[] = {0.3, 0.0, 0.0, 1.0};
	float m_dif[] = {0.6, 0.0, 0.0, 1.0};
	float m_spec[] = {0.8, 0.6, 0.6, 1.0};
	float shiny = 27;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	float origin[3] = {0,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);

	drawBox(origin, 25, 1, 25);
	drawAxis();
	ghost.draw();
	
	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Ghost Character");	//creates the window

	ghost = Ghost();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glEnable(GL_DEPTH_TEST);
	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}