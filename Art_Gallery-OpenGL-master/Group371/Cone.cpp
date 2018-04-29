#include "Cone.h"

const int Cone::DEFAULT_SIDES = 15;

Cone::Cone() : Cone(DEFAULT_SIDES) {

}

Cone::Cone(int sides) {
	if (sides < 3) {
		sides = 3;
	}
	float rotationAngle = glm::radians(360.0f) / sides;

	

	Vertex originTop(glm::vec3(0,0.5,0));
	Vertex originBottom(glm::vec3(0, -0.5, 0));

	originTop.uv = glm::vec2(0.5, 0.5);
	originBottom.uv = glm::vec2(0.5, 0.5);

	Vertex rotationPoint(glm::vec3(0.5, -0.5, 0));

	int size = 0;
	for (int i = 0; i < sides; i++) {
		Vertex nextRotationPoint;
		nextRotationPoint.position = glm::rotateY(rotationPoint.position, rotationAngle);

		float uvRotation = i * rotationAngle;
		float nextUvRotation = (i + 1) * rotationAngle;

		rotationPoint.uv = glm::vec2(glm::cos(uvRotation) * 0.5 + 0.5, glm::sin(uvRotation) * 0.5 + 0.5);
		nextRotationPoint.uv = glm::vec2(glm::cos(nextUvRotation) * 0.5 + 0.5, glm::sin(nextUvRotation) * 0.5 + 0.5);


		addVertex(originBottom);
		addVertex(rotationPoint);
		addVertex(nextRotationPoint);
		addIndices(glm::ivec3(size, size + 1, size + 2));
		size += 3;
		addVertex(rotationPoint);
		addVertex(nextRotationPoint);
		addVertex(originTop);
		addIndices(glm::ivec3(size, size + 1, size + 2));
		size += 3;
		rotationPoint = nextRotationPoint;
	}



}


Cone::~Cone() {
}
