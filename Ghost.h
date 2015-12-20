#ifndef __GHOST_H__
#define __GHOST_H__
#include <string>
#include "Vector3D.h"

class Ghost{
public:
	float pos[3];
	float rot[3];
	std::string dir;
	float scale;

	Point3D tailPoints[37];
	bool vertNormsCalced;
	Vector3D vertNorms[23];

	Ghost();
	Ghost(float x, float z, float scaleSize);
	Ghost(float x, float z, float scaleSize,std::string startDir);

	void move(std::string moveDir);
	Vector3D normAvg(Vector3D fNorm1, Vector3D fNorm2,
					 Vector3D fNorm3, Vector3D fNorm4 );
	Vector3D crossProd(Vector3D A, Vector3D B);
	Vector3D createVec(Point3D A, Point3D B);
	void calcVertNorms();
	void draw();
};
#endif