#ifndef __GHOST_H__
#define __GHOST_H__
#include <string>

class Ghost{
public:
	bool status;
	float pos[3];
	float rot[3];
	std::string dir;

	Ghost();
	Ghost(float x, float z);
	Ghost(float x, float z, std::string startDir);

	void move(std::string moveDir);
	void draw();
};
#endif