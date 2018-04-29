
#include "Circle.h"

const int Circle::DEFAULT_SIDES = 15;


Circle::Circle() : Circle(DEFAULT_SIDES) {}
Circle::Circle(int sides) {
	if (sides < 3) {
		sides = 3;
	}
	Vertex origin(glm::vec3(0,0,0));
	origin.uv = glm::vec2(0.5, 0.5);
	Vertex rotationPoint(glm::vec3(0.5f, 0, 0));
	float rotationAngle = glm::radians(360.0f) / sides ;
	
	int size = 0;
	for (int i = 0; i < sides; i++) {
		Vertex nextRotationPoint;
		float uvRotation = i * rotationAngle;
		float nextUvRotation = (i + 1) * rotationAngle;
		nextRotationPoint.position = glm::rotateY(rotationPoint.position, rotationAngle);	

		rotationPoint.uv = glm::vec2(glm::cos(uvRotation) * 0.5 + 0.5, glm::sin(uvRotation) * 0.5 + 0.5);;
		nextRotationPoint.uv = glm::vec2(glm::cos(nextUvRotation) * 0.5 + 0.5, glm::sin(nextUvRotation) * 0.5 + 0.5);
		addVertex(origin);
		addVertex(rotationPoint);
		addVertex(nextRotationPoint);
		glm::ivec3 indice = glm::ivec3(size, size + 1, size + 2);
		addIndices(indice);
		size += 3;
		rotationPoint = nextRotationPoint;
	}

}


Circle::~Circle() {
}

