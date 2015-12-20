
//#include <GLUT/glut.h>
#include <gl/glut.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Ghost.h"
#include "Vector3D"

using namespace std;

Ghost::Ghost()
{
	float pos[3] = {0.0, 9.0, 0.0};
	float rot[3] = {0, 0, 0};
	string dir = "forward";
	bool vertNormsCalced = false;
	Vector3D vertNorms[23];
}


Ghost::Ghost(float x, float z)
{
	float pos[3] = {x, 9.0, z};
	float rot[3] = {0, 0, 0};
	string dir = "forward";
	bool vertNormsCalced = false;
	Vector3D vertNorms[23];
}


Ghost::Ghost(float x, float z, string startDir)
{
	float pos[3] = {x, 9.0, z};
	bool vertNormsCalced = false;
	Vector3D vertNorms[23];

	if(startDir == "forward")
	{
		float rot[] = {0, 0, 0};
		string dir = startDir;

	}else if(startDir == "left"){

		float rot[] = {0, 90, 0};
		string dir = startDir;

	}else if(startDir == "right"){

		float rot[] = {0, -90, 0};
		string dir = startDir;

	}else if(startDir == "backward"){

		float rot[] = {0, 180, 0};
		string dir = startDir;

	} else{
		// default case if given direction is incorrect
		float rot[] = {0, 0, 0};
		string dir = "forward";
	}	
}


void Ghost::move(std::string moveDir)
{
	if(dir == "forward")
	{
		rot[1] = 0;
		pos[2] += 0.25;

	}else if(dir == "left"){

		rot[1] = 90;
		pos[0] += 0.25;

	}else if(dir == "right"){

		rot[1] = -90;
		pos[0] -= 0.25;

	}else if(dir == "backward"){

		rot[1] = 180;
		pos[2] -= 0.25;

	}
}


Vector3D normAvg(Vector3D fNorm1, Vector3D fNorm2,
				 Vector3D fNorm3, Vector3D fNorm4 )
{	/* 
	 * Takes the face normals and calcs the
	 * corresponding vertex normal
	 */
	Vector3D vertNorm = Vector3D(fNorm1.x + fNorm2.x + fNorm3.x + fNorm4.x,
								 fNorm1.y + fNorm2.y + fNorm3.y + fNorm4.y,
								 fNorm1.z + fNorm2.z + fNorm3.z + fNorm4.z )
	return vertNorm;
}


void calcVertNorms()
{
	
}


void Ghost::draw()
{   
	if(vertNormsCalced != true){ calcVertNorms(); }

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


	glPopMatrix(); // back to body coords


	glPushMatrix(); // right eye
	glTranslatef(1.5, 1, 4);
	glColor3f(0,0,0);
	glutSolidSphere(1, 8, 8);

	glPushMatrix(); // eye centre
	glTranslatef(0, 0, 0.8);
	glColor3f(1,1,1);
	glutSolidSphere(0.3, 8, 8);
	glPopMatrix();

	glPopMatrix(); // back to body coords


	glPushMatrix(); // ghost tail
	glTranslatef(0.0, -5, 0.0);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);

		glVertex3f(3.536, 5.0, -3.536); // p1
		glVertex3f(2.337, 3.840, -4.006); // p4 
		glVertex3f(0.0, 3.840, -5.471); // p5
		glVertex3f(0.0, 5.0, -5.0); // p2

		glVertex3f(0.0, 5.0, -5.0); // p2
		glVertex3f(0.0, 3.840, -5.471); // p5
		glVertex3f(-2.337, 3.840, -4.006); // p6
		glVertex3f(-3.536, 5.0, -3.536); // p3

		glVertex3f(3.536, 5.0, -3.536); // p1
		glVertex3f(3.266, 3.087, -3.266); // p7
		glVertex3f(1.009, 2.963, -6.363); // p8
		glVertex3f(2.337, 3.840, -4.006); // p6

		glVertex3f(-2.337, 3.840, -4.006); // p6
		glVertex3f(-1.009, 2.963, -6.363); // p10
		glVertex3f(-3.266, 3.087, -3.266); // p11
		glVertex3f(-3.536, 5.0, -3.536); // p3

		glVertex3f(2.337, 3.840, -4.006); // p4
		glVertex3f(1.009, 2.963, -6.363); // p8
		glVertex3f(0.0, 2.963, -7.716); // p9
		glVertex3f(0.0, 3.840, -5.471); // p5

		glVertex3f(0.0, 3.840, -5.471); // p5
		glVertex3f(0.0, 2.963, -7.716); // p9
		glVertex3f(-1.009, 2.963, -6.363); // p10
		glVertex3f(-2.337, 3.840, -4.006); // p6

		glVertex3f(3.266, 3.087, -3.266); // p7
		glVertex3f(2.5, 1.464, -2.5); // p12
		glVertex3f(0.824, 1.454, -5.1); // p13
		glVertex3f(1.009, 2.963, -6.363); // p8

		glVertex3f(-1.009, 2.963, -6.363); // p10
		glVertex3f(-0.824, 1.454, -5.1); // p15
		glVertex3f(-2.5, 1.464, -2.5); // p9
		glVertex3f(-3.266, 3.087, -3.266); // p11

		glVertex3f(1.009, 2.963, -6.363); // p8
		glVertex3f(0.824, 1.454, -5.1); // p13
		glVertex3f(0.0, 1.454, -6.135); // p14
		glVertex3f(0.0, 2.963, -7.716); // p9

		glVertex3f(0.0, 2.963, -7.716); // p9
		glVertex3f(0.0, 1.454, -6.135); // p14
		glVertex3f(-0.824, 1.454, -5.1); // p15
		glVertex3f(-1.009, 2.963, -6.363); // p10

		glVertex3f(2.5, 1.464, -2.5); // p12
		glVertex3f(1.353, 0.381, -1.353); // p17
		glVertex3f(0.605, 0.364, -3.261); // p18
		glVertex3f(0.824, 1.454, -5.1); // p13

		glVertex3f(-0.824, 1.454, -5.1); // p15
		glVertex3f(-0.605, 0.364, -3.261); // p20
		glVertex3f(-1.353, 0.381, -1.353); // p21
		glVertex3f(-2.5, 1.464, -2.5); // p16

		glVertex3f(0.824, 1.454, -5.1); // p13
		glVertex3f(0.605, 0.364, -3.261); // p18
		glVertex3f(0.0, 0.364, -3.821); // p19
		glVertex3f(0.0, 1.454, -6.135); // p14

		glVertex3f(0.0, 1.454, -6.135); // p14
		glVertex3f(0.0, 0.364, -3.821); // p19
		glVertex3f(-0.605, 0.364, -3.261); // p20
		glVertex3f(-0.824, 1.454, -5.1); // p15

		glVertex3f(1.353, 0.381, -1.353); // p17
		glVertex3f(0.0, 0.0, -1.832); // p22
		glVertex3f(0.0, 0.364, -3.821); // p19
		glVertex3f(0.605, 0.364, -3.261); // p18

		glVertex3f(-0.605, 0.364, -3.261); // p20
		glVertex3f(0.0, 0.364, -3.821); // p19
		glVertex3f(0.0, 0.0, -1.832); // p22
		glVertex3f(-1.353, 0.381, -1.353); // p21

		glVertex3f(1.353, 0.381, -1.353); // p17
		glVertex3f(0.0, 0.0, 0.0); // p23
		glVertex3f(-1.353, 0.381, -1.353); // p21
		glVertex3f(0.0, 0.0, -1.832); // p22

	glEnd();
	
	glPopMatrix();

	glPopMatrix();
}

int main(int argc, char** argv)
{
	Ghost ghost = Ghost();
	return(0);
}