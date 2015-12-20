#ifndef __GHOST_H__
#define __GHOST_H__
#include <string>
#include "Vector3D"

class Ghost{
public:
	float pos[3];
	float rot[3];
	std::string dir;
	bool vertNormsCalced;
	Vector3D vertNorms[23];

	Ghost();
	Ghost(float x, float z);
	Ghost(float x, float z, std::string startDir);

	void move(std::string moveDir);
	Vector3D normAvg(Vector3D fNorm1, Vector3D fNorm2,
					 Vector3D fNorm3, Vector3D fNorm4 )
	void draw();
};
#endif