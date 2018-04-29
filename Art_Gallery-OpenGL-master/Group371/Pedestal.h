#ifndef PEDESTAL_H
#define PEDESTAL_H

#include "Mesh.h"
#include "Cube.h"
#include "Texture.h"

class Pedestal : public Cube {
public:
	Pedestal();
	~Pedestal();
private:
	MeshManager manager;
};

#endif