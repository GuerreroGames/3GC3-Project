#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

class Vector3D{
public:

	Vector3D();
	Vector3D(float inX, float inY, float inZ);

	float x;
	float y;
	float z;

};

class Point3D{
public:

	Point3D();
	Point3D(float inX, float inY, float inZ);

	float x;
	float y;
	float z;

};
#endif