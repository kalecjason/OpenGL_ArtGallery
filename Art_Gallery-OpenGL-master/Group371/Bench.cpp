#include "Bench.h"
#include "Color.h"
#include <iostream>

Bench::Bench() 
	: length(1.0f), height(0.3f), width(0.3f) {
}

Bench::Bench(float length, float height, float width)
	: length(length), height(height), width(width) {
	this->textureMap = textureMap;
	addBench();
	onChange();
}



Bench::~Bench(){}

void Bench::addBench()
{
	glm::vec3 amb = glm::vec3(0.6f, 0.6f, 0.6f);
	Material m{
		amb, amb,
		glm::vec3(1.0f, 1.0f, 1.0f),
		128 };

	int repeat = 1;
	Mesh bench = Cube();
	bench.localScaleMesh(glm::vec3(length, height / 3, width));
	bench.translateMesh(glm::vec3(0.0f, 0.0f, 0.0f));
	bench.setTexture(Texture::getTexture("pedestal"), repeat, repeat);
	manager.addMesh(bench);

	Mesh leftLeg = Cube();
	leftLeg.localScaleMesh(glm::vec3(length / 10, (height / 3) * 2, width));
	leftLeg.translateMesh(glm::vec3(-length / 4, -(height / 2), 0.0f));
	leftLeg.setTexture(Texture::getTexture("pedestal"), repeat, repeat);
	manager.addMesh(leftLeg);

	Mesh rightLeg = Cube();
	rightLeg.localScaleMesh(glm::vec3(length / 10, (height / 3) * 2, width));
	rightLeg.translateMesh(glm::vec3(length / 4, -(height / 2), 0.0f));
	rightLeg.setTexture(Texture::getTexture("pedestal"), repeat, repeat);
	manager.addMesh(rightLeg);
}

std::vector<BoundingBox> Bench::getBoundingBox()
{
	float extraSpace = 0.135f;
	std::vector<BoundingBox> boxes;
	glm::vec3 max_XYZ = this->manager.finalMesh.maxXYZ;
	glm::vec3 min_XYZ = this->manager.finalMesh.minXYZ;

	BoundingBox box;
	box.max = glm::vec3(maxXYZ.x + extraSpace, maxXYZ.y + extraSpace, maxXYZ.z + extraSpace);
	box.min = glm::vec3(minXYZ.x + extraSpace, minXYZ.y + extraSpace, minXYZ.z + extraSpace);
	boxes.push_back(box);

	return boxes;
}

void Bench::onChange()
{
	//recompute mesh on changes
	manager.computeMergedMeshCopies();
	Mesh computedMesh = manager.finalMesh;
	vertices = computedMesh.getVertices();
	indices = computedMesh.getIndices();
}

