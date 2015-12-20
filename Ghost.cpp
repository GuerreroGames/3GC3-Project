
//#include <GLUT/glut.h>
#include <gl/glut.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>  

#include "Ghost.h"
#include "Vector3D.h"

using namespace std;

Ghost::Ghost()
{
	float pos[3] = {0.0, 9.0, 0.0};
	float rot[3] = {0, 0, 0};
	string dir = "forward";
	float scale = 1;

	Point3D tailPoints[37] = {
		Point3D(3.536, 5.0, -3.536), Point3D(0.0, 5.0, -5.0),
		Point3D(-3.536, 5.0, -3.536), Point3D(2.337, 3.840, -4.006),
		Point3D(0.0, 3.840, -5.471), Point3D(-2.337, 3.840, -4.006),
		Point3D(3.266, 3.087, -3.266), Point3D(1.009, 2.963, -6.363),
		Point3D(0.0, 2.963, -7.716), Point3D(-1.009, 2.963, -6.363),
		Point3D(-3.266, 3.087, -3.266), Point3D(2.5, 1.464, -2.5),
		Point3D(0.824, 1.454, -5.1), Point3D(0.0, 1.454, -6.135),
		Point3D(-0.824, 1.454, -5.1), Point3D(-2.5, 1.464, -2.5),
		Point3D(1.353, 0.381, -1.353), Point3D(0.605, 0.364, -3.261),
		Point3D(0.0, 0.364, -3.821), Point3D(-0.605, 0.364, -3.261),
		Point3D(-1.353, 0.381, -1.353), Point3D(0.0, 0.0, -1.832),
		Point3D(0.0, 0.0, 0.0), Point3D(3.266, 6.913, -3.266),
		Point3D(0.0, 6.913, -4.619), Point3D(-3.266, 6.913, -3.266),
		Point3D(-5.0, 5.0, 0.0), Point3D(-4.619, 3.087, 0.0),
		Point3D(-3.536, 1.464, 0.0), Point3D(-1.913, 0.381, 0.0),
		Point3D(-1.353, 0.381, 1.353), Point3D(0.0, 0.381, 1.913),
		Point3D(1.353, 0.381, 1.353), Point3D(1.913, 0.381, 0.0),
		Point3D(3.536, 1.464, 0.0), Point3D(4.619, 3.087, 0.0),
		Point3D(5.0, 5.0, 0.0) };
	bool vertNormsCalced = false;
	Vector3D vertNorms[23];
}


Ghost::Ghost(float x, float z, float scaleSize)
{
	float pos[3] = {x, 9.0, z};
	float rot[3] = {0, 0, 0};
	string dir = "forward";
	float scale = scaleSize;


	Point3D tailPoints[37] = {
		Point3D(3.536, 5.0, -3.536), Point3D(0.0, 5.0, -5.0),
		Point3D(-3.536, 5.0, -3.536), Point3D(2.337, 3.840, -4.006),
		Point3D(0.0, 3.840, -5.471), Point3D(-2.337, 3.840, -4.006),
		Point3D(3.266, 3.087, -3.266), Point3D(1.009, 2.963, -6.363),
		Point3D(0.0, 2.963, -7.716), Point3D(-1.009, 2.963, -6.363),
		Point3D(-3.266, 3.087, -3.266), Point3D(2.5, 1.464, -2.5),
		Point3D(0.824, 1.454, -5.1), Point3D(0.0, 1.454, -6.135),
		Point3D(-0.824, 1.454, -5.1), Point3D(-2.5, 1.464, -2.5),
		Point3D(1.353, 0.381, -1.353), Point3D(0.605, 0.364, -3.261),
		Point3D(0.0, 0.364, -3.821), Point3D(-0.605, 0.364, -3.261),
		Point3D(-1.353, 0.381, -1.353), Point3D(0.0, 0.0, -1.832),
		Point3D(0.0, 0.0, 0.0), Point3D(3.266, 6.913, -3.266),
		Point3D(0.0, 6.913, -4.619), Point3D(-3.266, 6.913, -3.266),
		Point3D(-5.0, 5.0, 0.0), Point3D(-4.619, 3.087, 0.0),
		Point3D(-3.536, 1.464, 0.0), Point3D(-1.913, 0.381, 0.0),
		Point3D(-1.353, 0.381, 1.353), Point3D(0.0, 0.381, 1.913),
		Point3D(1.353, 0.381, 1.353), Point3D(1.913, 0.381, 0.0),
		Point3D(3.536, 1.464, 0.0), Point3D(4.619, 3.087, 0.0),
		Point3D(5.0, 5.0, 0.0) };
	bool vertNormsCalced = false;
	Vector3D vertNorms[23];
}


Ghost::Ghost(float x, float z, float scaleSize, string startDir)
{
	float pos[3] = {x, 9.0, z};
	float scale = scaleSize;

	Point3D tailPoints[37] = {
		Point3D(3.536, 5.0, -3.536), Point3D(0.0, 5.0, -5.0),
		Point3D(-3.536, 5.0, -3.536), Point3D(2.337, 3.840, -4.006),
		Point3D(0.0, 3.840, -5.471), Point3D(-2.337, 3.840, -4.006),
		Point3D(3.266, 3.087, -3.266), Point3D(1.009, 2.963, -6.363),
		Point3D(0.0, 2.963, -7.716), Point3D(-1.009, 2.963, -6.363),
		Point3D(-3.266, 3.087, -3.266), Point3D(2.5, 1.464, -2.5),
		Point3D(0.824, 1.454, -5.1), Point3D(0.0, 1.454, -6.135),
		Point3D(-0.824, 1.454, -5.1), Point3D(-2.5, 1.464, -2.5),
		Point3D(1.353, 0.381, -1.353), Point3D(0.605, 0.364, -3.261),
		Point3D(0.0, 0.364, -3.821), Point3D(-0.605, 0.364, -3.261),
		Point3D(-1.353, 0.381, -1.353), Point3D(0.0, 0.0, -1.832),
		Point3D(0.0, 0.0, 0.0), Point3D(3.266, 6.913, -3.266),
		Point3D(0.0, 6.913, -4.619), Point3D(-3.266, 6.913, -3.266),
		Point3D(-5.0, 5.0, 0.0), Point3D(-4.619, 3.087, 0.0),
		Point3D(-3.536, 1.464, 0.0), Point3D(-1.913, 0.381, 0.0),
		Point3D(-1.353, 0.381, 1.353), Point3D(0.0, 0.381, 1.913),
		Point3D(1.353, 0.381, 1.353), Point3D(1.913, 0.381, 0.0),
		Point3D(3.536, 1.464, 0.0), Point3D(4.619, 3.087, 0.0),
		Point3D(5.0, 5.0, 0.0) };
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


Vector3D Ghost::normAvg(Vector3D fNorm1, Vector3D fNorm2,
				 Vector3D fNorm3, Vector3D fNorm4 )
{	/* 
	 * Takes the face normals and calcs the
	 * corresponding normalized vertex normal
	 */
	Vector3D vertNorm = Vector3D(fNorm1.x + fNorm2.x + fNorm3.x + fNorm4.x,
								 fNorm1.y + fNorm2.y + fNorm3.y + fNorm4.y,
								 fNorm1.z + fNorm2.z + fNorm3.z + fNorm4.z );

	float magnitude = sqrt((vertNorm.x * vertNorm.x) + (vertNorm.y * vertNorm.y) + (vertNorm.z * vertNorm.z) ); 
 
	printf("magnitude: %f\n", magnitude);
	vertNorm = Vector3D(vertNorm.x / magnitude, 
						vertNorm.y / magnitude,
						vertNorm.z /magnitude);
	return vertNorm;
}


Vector3D Ghost::crossProd(Vector3D A, Vector3D B)
{ 	
	Vector3D crossProd = Vector3D(  (A.y * B.z) - (A.z * B.y), 
									(A.z * B.x) - (A.x * B.z), 
									(A.x * B.y) - (A.y * B.x) );
	return crossProd;
}


Vector3D Ghost::createVec(Point3D A, Point3D B)
{ // points from A --> B
	Vector3D vec = Vector3D(B.x-A.x, B.y-A.y, B.z-A.z);
	return vec;
}


void Ghost::calcVertNorms()
{
	Vector3D NWfaceNorm = Vector3D();
	Vector3D NEfaceNorm = Vector3D();
	Vector3D SEfaceNorm = Vector3D();
	Vector3D SWfaceNorm = Vector3D();

	// A & B for face norm calc
	Vector3D A = Vector3D();
	Vector3D B = Vector3D();

/*****************************************************************************/
	A = createVec(tailPoints[0], tailPoints[23]);
	B = createVec(tailPoints[0], tailPoints[36]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[0], tailPoints[1]);
	B = createVec(tailPoints[0], tailPoints[23]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[0], tailPoints[6]);
	B = createVec(tailPoints[0], tailPoints[1]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[0], tailPoints[36]);
	B = createVec(tailPoints[0], tailPoints[6]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[0] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[1], tailPoints[24]);
	B = createVec(tailPoints[1], tailPoints[0]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[1], tailPoints[2]);
	B = createVec(tailPoints[1], tailPoints[24]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[1], tailPoints[4]);
	B = createVec(tailPoints[1], tailPoints[2]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[1], tailPoints[0]);
	B = createVec(tailPoints[1], tailPoints[4]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[1] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[2], tailPoints[25]);
	B = createVec(tailPoints[2], tailPoints[1]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[2], tailPoints[26]);
	B = createVec(tailPoints[2], tailPoints[25]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[2], tailPoints[10]);
	B = createVec(tailPoints[2], tailPoints[26]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[2], tailPoints[1]);
	B = createVec(tailPoints[2], tailPoints[10]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[2] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[3], tailPoints[0]);
	B = createVec(tailPoints[3], tailPoints[6]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[3], tailPoints[4]);
	B = createVec(tailPoints[3], tailPoints[0]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[3], tailPoints[7]);
	B = createVec(tailPoints[3], tailPoints[4]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[3], tailPoints[6]);
	B = createVec(tailPoints[3], tailPoints[7]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[3] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[4], tailPoints[1]);
	B = createVec(tailPoints[4], tailPoints[3]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[4], tailPoints[5]);
	B = createVec(tailPoints[4], tailPoints[1]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[4], tailPoints[8]);
	B = createVec(tailPoints[4], tailPoints[5]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[4], tailPoints[3]);
	B = createVec(tailPoints[4], tailPoints[8]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[4] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[5], tailPoints[2]);
	B = createVec(tailPoints[5], tailPoints[4]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[5], tailPoints[10]);
	B = createVec(tailPoints[5], tailPoints[2]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[5], tailPoints[9]);
	B = createVec(tailPoints[5], tailPoints[10]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[5], tailPoints[4]);
	B = createVec(tailPoints[5], tailPoints[9]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[5] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[6], tailPoints[0]);
	B = createVec(tailPoints[6], tailPoints[35]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[6], tailPoints[7]);
	B = createVec(tailPoints[6], tailPoints[0]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[6], tailPoints[11]);
	B = createVec(tailPoints[6], tailPoints[7]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[6], tailPoints[35]);
	B = createVec(tailPoints[6], tailPoints[11]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[6] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[7], tailPoints[3]);
	B = createVec(tailPoints[7], tailPoints[6]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[7], tailPoints[8]);
	B = createVec(tailPoints[7], tailPoints[3]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[7], tailPoints[12]);
	B = createVec(tailPoints[7], tailPoints[8]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[7], tailPoints[6]);
	B = createVec(tailPoints[7], tailPoints[12]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[7] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[8], tailPoints[4]);
	B = createVec(tailPoints[8], tailPoints[7]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[8], tailPoints[9]);
	B = createVec(tailPoints[8], tailPoints[4]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[8], tailPoints[13]);
	B = createVec(tailPoints[8], tailPoints[9]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[8], tailPoints[7]);
	B = createVec(tailPoints[8], tailPoints[13]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[8] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[9], tailPoints[5]);
	B = createVec(tailPoints[9], tailPoints[8]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[9], tailPoints[10]);
	B = createVec(tailPoints[9], tailPoints[5]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[9], tailPoints[14]);
	B = createVec(tailPoints[9], tailPoints[10]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[9], tailPoints[8]);
	B = createVec(tailPoints[9], tailPoints[14]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[9] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[10], tailPoints[2]);
	B = createVec(tailPoints[10], tailPoints[9]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[10], tailPoints[27]);
	B = createVec(tailPoints[10], tailPoints[2]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[10], tailPoints[15]);
	B = createVec(tailPoints[10], tailPoints[27]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[10], tailPoints[9]);
	B = createVec(tailPoints[10], tailPoints[15]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[10] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[11], tailPoints[6]);
	B = createVec(tailPoints[11], tailPoints[34]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[11], tailPoints[12]);
	B = createVec(tailPoints[11], tailPoints[6]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[11], tailPoints[16]);
	B = createVec(tailPoints[11], tailPoints[12]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[11], tailPoints[34]);
	B = createVec(tailPoints[11], tailPoints[16]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[11] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[12], tailPoints[7]);
	B = createVec(tailPoints[12], tailPoints[11]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[12], tailPoints[13]);
	B = createVec(tailPoints[12], tailPoints[7]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[12], tailPoints[17]);
	B = createVec(tailPoints[12], tailPoints[13]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[12], tailPoints[11]);
	B = createVec(tailPoints[12], tailPoints[17]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[12] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[13], tailPoints[8]);
	B = createVec(tailPoints[13], tailPoints[12]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[13], tailPoints[14]);
	B = createVec(tailPoints[13], tailPoints[8]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[13], tailPoints[18]);
	B = createVec(tailPoints[13], tailPoints[14]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[13], tailPoints[12]);
	B = createVec(tailPoints[13], tailPoints[18]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[13] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[14], tailPoints[9]);
	B = createVec(tailPoints[14], tailPoints[13]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[14], tailPoints[15]);
	B = createVec(tailPoints[14], tailPoints[9]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[14], tailPoints[15]);
	B = createVec(tailPoints[14], tailPoints[19]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[14], tailPoints[13]);
	B = createVec(tailPoints[14], tailPoints[19]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[14] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[15], tailPoints[10]);
	B = createVec(tailPoints[15], tailPoints[14]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[15], tailPoints[28]);
	B = createVec(tailPoints[15], tailPoints[10]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[15], tailPoints[20]);
	B = createVec(tailPoints[15], tailPoints[28]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[15], tailPoints[14]);
	B = createVec(tailPoints[15], tailPoints[20]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[15] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[16], tailPoints[11]);
	B = createVec(tailPoints[16], tailPoints[33]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[16], tailPoints[17]);
	B = createVec(tailPoints[16], tailPoints[11]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[16], tailPoints[21]);
	B = createVec(tailPoints[16], tailPoints[17]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[16], tailPoints[33]);
	B = createVec(tailPoints[16], tailPoints[22]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[16] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[17], tailPoints[12]);
	B = createVec(tailPoints[17], tailPoints[16]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[17], tailPoints[18]);
	B = createVec(tailPoints[17], tailPoints[12]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[17], tailPoints[21]);
	B = createVec(tailPoints[17], tailPoints[18]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[17], tailPoints[16]);
	B = createVec(tailPoints[17], tailPoints[21]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[17] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[18], tailPoints[13]);
	B = createVec(tailPoints[18], tailPoints[17]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[18], tailPoints[19]);
	B = createVec(tailPoints[18], tailPoints[13]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[18], tailPoints[21]);
	B = createVec(tailPoints[18], tailPoints[19]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[18], tailPoints[17]);
	B = createVec(tailPoints[18], tailPoints[21]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[18] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/
	A = createVec(tailPoints[19], tailPoints[14]);
	B = createVec(tailPoints[19], tailPoints[18]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[19], tailPoints[20]);
	B = createVec(tailPoints[19], tailPoints[14]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[19], tailPoints[21]);
	B = createVec(tailPoints[19], tailPoints[20]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[19], tailPoints[18]);
	B = createVec(tailPoints[19], tailPoints[21]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[19] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[20], tailPoints[15]);
	B = createVec(tailPoints[20], tailPoints[19]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[20], tailPoints[29]);
	B = createVec(tailPoints[20], tailPoints[15]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[20], tailPoints[22]);
	B = createVec(tailPoints[20], tailPoints[29]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[20], tailPoints[19]);
	B = createVec(tailPoints[20], tailPoints[21]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[20] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[21], tailPoints[18]);
	B = createVec(tailPoints[21], tailPoints[16]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[21], tailPoints[20]);
	B = createVec(tailPoints[21], tailPoints[18]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[21], tailPoints[22]);
	B = createVec(tailPoints[21], tailPoints[20]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[21], tailPoints[16]);
	B = createVec(tailPoints[21], tailPoints[22]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[21] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/	
	A = createVec(tailPoints[22], tailPoints[21]);
	B = createVec(tailPoints[22], tailPoints[16]);
	NWfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[22], tailPoints[20]);
	B = createVec(tailPoints[22], tailPoints[21]);
	NEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[22], tailPoints[31]);
	B = createVec(tailPoints[22], tailPoints[30]);
	SEfaceNorm = crossProd(A, B);

	A = createVec(tailPoints[22], tailPoints[32]);
	B = createVec(tailPoints[22], tailPoints[31]);
	SWfaceNorm = crossProd(A, B);
	vertNorms[22] = normAvg(NWfaceNorm, NEfaceNorm, SEfaceNorm, SWfaceNorm);
/*****************************************************************************/						
}


void Ghost::draw()
{   
	if(vertNormsCalced != true)
	{ 
		calcVertNorms();
		vertNormsCalced = true;
	}

	glPushMatrix(); // ghost body

	glScalef(scale, scale, scale);
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
	ghost.calcVertNorms();
	for(int i=0; i<22; i++)
	{
		printf("vertNorms[%i] = %f, %f, %f\n", i, ghost.vertNorms[i].x, ghost.vertNorms[i].y, ghost.vertNorms[i].z);
	}
	return(0);
}