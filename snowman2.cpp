/* Snowman sample 
 * by R. Teather
 * Modified by: K.Knopf
 */

#include <gl/glut.h>
#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

float verts[8][3] = { {-1,-1,1}, {-1,1,1}, {1,1,1}, {1,-1,1}, {-1,-1,-1}, {-1,1,-1}, {1,1,-1}, {1,-1,-1} };
float cols[6][3] = { {0,1,1}, {0,1,1}, {0,1,1}, {0,1,1}, {0,1,1}, {0,1,1} };



float pos[] = {-3,1,+3};
double viewPop[3];
float rot[] = {0, 0, 0};
float headRot[] = {0, 0, 0};
//float camPos[] = {0, 5, 12};
float camPos[] = {-5,10,14};
float target[] = {0.0,0.0,0.0};
float angle = 0.0f;
int lumenenceValue[1];

GLubyte* tex; //texture
GLubyte* tex_sub; //sub texture
int width, height, maxi;

float x,y,tx,ty,xcos,ysin,radian,radius;

//Temp storage stuff
double modelViewMatrixStorage[16];
double modelProjectionMatrixStorage[16];
int modelViewportStorage[4];


int ang = 0;	//angle for rotating cube
int cnt = 0;
float eye[] = {5,5,5};

/* LIGHTING */
float light_pos[] = {-1.0,15.0,-10.0,1.0};
float amb0[4] = {1,1,1,1};
float diff0[4] = {1,1,1,1};
float spec0[4] = {1,1,1,1};
float lightcutoff0 = 30.0;
float  spotDir[] = { 0.0f, -1.0f, 0.0f };


float light_pos1[] = {0.0,10.0,0.0,0.0};
float amb01[4] = {0.1,0.1,0.1,1};
float diff01[4] = {0.1,0.1,0.1,1};
float spec01[4] = {0.1,0.1,0.1,1};

/* MATERIALS */
float m_amb_Wall[] = {1.0,1.0,1.0,1.0};
float m_diff_Wall[] = {1.01, 1.01, 1.01, 1.0};
float m_spec_Wall[] = {0.50,0.50,0.50,1.0};
float shiny_Wall = 0.25;

float m_amb_Char[] = {0.33,0.22,0.03,1.0};
float m_diff_Char[] = {0.78, 0.57, 0.11, 1.0};
float m_spec_Char[] = {0.99,0.91,0.81,1.0};
float shiny_Char = 1.0;


/* drawPolygon - takes 4 indices and an array of vertices
 *   and draws a polygon using the vertices indexed by the indices
 */
void drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
		//draw map
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(v[a]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(v[b]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(v[c]);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(v[d]);
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
void drawBox(float* c, float w, float h, float d) //([0,0,0],10,1,10)
{

	/* MATERIALS */
  //  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb_Wall);
 //   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,m_diff_Wall);
 ////   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,m_spec_Wall);
//    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,shiny_Wall);

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
		//	if(pos[0] > -4.4)
			pos[0] -= 1.3*0.1;
			rot[1] = -90;
			break;

		case 'w':
		case 'W':
			//if(pos[2] > -4.4) //need to unbound forward movement
			//if(pos[2] < -1.5){
				//camPos[2] = 10.0;
			//	target[2] = -10.0;
			//	camPos[2] = 8.1;
			//	camPos[0] = 3.4;
			//}
			//camPos[2] -= 0.1;
			pos[2] -= 1.3*0.1;
			rot[1] = 180;
			break;

		case 'd':
		case 'D':
			//if(pos[0] < 4.4)
				pos[0]+=1.3*0.1;
			rot[1] = 90;
			break;

		case 's':
		case 'S':
			//if(pos[2] < 4.4)
			//	camPos[2] += 0.1;
				pos[2] += 1.3*0.1;
			rot[1] = 0;
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

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2, 2, -2, 2, -2, 2);
	gluPerspective(45, 1, 1, 100);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//add texture code here!
	//load marble texture
	//tex = LoadPPM("marble.ppm", &width, &height, &maxi);
}


void DrawGhost(float* pos, float* rot)
{
	glPushMatrix(); // ghost body
	glScalef(0.3,0.3,0.3);
	glTranslatef(0.0,6.0,0.0);

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
void DrawSnowman(float* pos, float* rot)
{
	/* MATERIALS */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,m_amb_Char);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,m_diff_Char);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,m_spec_Char);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,shiny_Char);

	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[1], 0, 1, 0);

	//draw body
	glColor3f(1,1,1);
	glutSolidSphere(1, 16, 16);

	//draw buttons
	glPushMatrix();
	glTranslatef(0, 0.35, 0.9);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.15, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.05, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();


	glPushMatrix();
	//translate relative to body, and draw head
	glTranslatef(0, 1.25, 0);
	glRotatef(headRot[1], 0, 1, 0); //turn the head relative to the body
	glColor3f(1,1,1);
	glutSolidSphere(0.5, 16, 16);
	
	//translate and draw right eye
	glPushMatrix();
	glTranslatef(0.2, 0.15, 0.45);
	glColor3f(0,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw left eye
	glPushMatrix();
	glTranslatef(-0.2, 0.15, 0.45);
	glColor3f(0,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw nose
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1,0.4,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPopMatrix();//body
	glPopMatrix();//snowman
}

//need a drawRoom and a drawConnectorRoom functions to easily draw rooms


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	float origin[3] = {0,0,-5};
	float origin2[3] = {-5,5,-5};
	float origin3[3] = {5,5,-5};


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0+0.3*pos[2], 0,1,0);
	glColor3f(1,1,1);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,10.0f);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
   // glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,100.0f);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
    
    glPushMatrix();
	glTranslatef(light_pos[0],light_pos[1],light_pos[2]);
	glutSolidSphere(0.2, 12, 10);
	glPopMatrix();

	glLightfv(GL_LIGHT1,GL_POSITION,light_pos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb01);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff01);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec01);

	DrawGhost(pos, rot);
	//Textures

	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex); 

	//set texture properties

	//glColor3f(0,1,0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	drawBox(origin, 10, 1, 20);
	drawBox(origin2,1,10,20);
	drawBox(origin3,1,10,20);
	glDisable(GL_TEXTURE_2D);
	//draw the 2Dcircle on the ground
	glEnable(GL_TEXTURE_2D); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_sub); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_POLYGON);
	radius = (light_pos[1]-1)*(float)tan(lightcutoff0*M_PI/360.0f);
	glNormal3f(0,1,0);
    for (angle=0.0; angle<360.0; angle+=2.0)
    {
    	radian = angle * (M_PI /180.0f);

		xcos = (float)cos(radian);
		ysin = (float)sin(radian);
		x = xcos * radius  + light_pos[0]; //need to change to center of spotlight, and size of spotlight
		y = ysin * radius  + light_pos[2]; //need to change to center of spotlight, and size of spotlight
		tx = xcos * 0.5 + 0.5;
		ty = ysin * 0.5 + 0.5;
		glTexCoord3f(tx,0.6, ty);
		glVertex3f(x,0.6,y);
	}

    glEnd();
    glDisable(GL_TEXTURE_2D);




	//create a set of 4-5 pixels that exist on the character
	// translate them with position and rotation
	// check them at each step
	//check pixel at pos (x + 0, y + 1, z + 16);
	// need to traslate to pixel location and then apply algorithm
	// use glGetPixels to return pixel lumenense
	//GluProject use to get the pixel locations
	// 
	glGetDoublev(GL_MODELVIEW_MATRIX,modelViewMatrixStorage);
	glGetDoublev(GL_PROJECTION_MATRIX,modelProjectionMatrixStorage);
	glGetIntegerv(GL_VIEWPORT,modelViewportStorage);

	gluProject(pos[0],pos[1],pos[2],modelViewMatrixStorage,modelProjectionMatrixStorage,modelViewportStorage, &viewPop[0], &viewPop[1], &viewPop[2]);
	glReadPixels(viewPop[0],viewPop[1],1,1,GL_RED,GL_FLOAT,lumenenceValue);
	//printf("%d \n",lumenenceValue[0]);
	//printf(viewPop[0]);
	//printf(viewPop[1]);
	if(lumenenceValue[0] > 1025548449){
		//string g("Dead");
		//glRasterPos2f(500,500);
		//glColor3f(1.0, 1.0, 1.0);
		//for(int i =0; i <  g.length(); i++){
		//	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g[i]);
		//}
		//printf("Dead \n") ;
	}
	//printf(" %f \n",camPos[0]);
	//printf(" %f \n",camPos[1]);
	//printf(" %f \n",camPos[2]);

	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("SNOWMAN 2: LIGHT SHOW");	//creates the window

	//image1 = LoadPPM("interface.ppm", &width, &height, &maxi);

	tex = LoadPPM("concrete.ppm", &width, &height, &maxi);
	tex_sub = LoadPPM("concrete-light.ppm", &width, &height, &maxi);
	/* LIGHTING */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//glEnable(GL_CULL_FACE); // Allows backface culling
	//glCullFace(GL_BACK);


	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);


	glEnable(GL_DEPTH_TEST);
	init();

	//Textures

	//glEnable(GL_TEXTURE_2D); 
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex); 

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}