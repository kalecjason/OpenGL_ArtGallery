#ifndef CYLINDER_H
#define CYLINDER_H

#include "Mesh.h"


class Cylinder : public Mesh {
public:
	static const int DEFAULT_SIDES;
	Cylinder();
	Cylinder(int sides);
	~Cylinder();
};

#endif // !CYLINDER_H