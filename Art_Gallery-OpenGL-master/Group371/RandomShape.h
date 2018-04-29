#ifndef RANDOMSHAPE_H
#define RANDOMSHAPE_H

#include "Mesh.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Cube.h"
#include "Plane.h"
#include "Circle.h"
#include "Cylinder.h"
#include "Cone.h"
#include "MeshManager.h"
#include <algorithm>


class RandomShape : public Mesh {
public:
	RandomShape();
	~RandomShape() {};
private:
	Mesh Superform();
	float superformula(float a, float b, float m1, float m2, float n1, float n2, float n3, float angle);
	float map(float value, float istart, float istop, float ostart, float ostop);
};

#endif // !RANDOMSHAPE_H