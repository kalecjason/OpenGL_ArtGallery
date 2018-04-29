#include "Cylinder.h"



const int Cylinder::DEFAULT_SIDES = 15;


Cylinder::Cylinder() : Cylinder(DEFAULT_SIDES) {
}

Cylinder::Cylinder(int sides) {
	if (sides < 3) {
		sides = 3;
	}
	float rotationAngle = glm::radians(360.0f) / sides;

	Vertex originTop(glm::vec3(0, 0.5f, 0));
	originTop.uv = glm::vec2(0.5, 0.5);
	Vertex originBottom(glm::vec3(0, -0.5f, 0));
	originBottom.uv = glm::vec2(0.5, 0.5);

	Vertex rotationPointTop(glm::vec3(0.5f, 0.5f, 0));
	Vertex rotationPointBottom(glm::vec3(0.5f, -0.5f, 0));
	Vertex rotationPointTopDup(glm::vec3(0.5f, 0.5f, 0));
	Vertex rotationPointBottomDup(glm::vec3(0.5f, -0.5f, 0));

	
	

	int size = 0;
	for (int i = 0; i < sides; i++) {
		
		Vertex nextRotationPointTop;
		Vertex nextRotationPointBottom;
		Vertex nextRotationPointTopDup;
		Vertex nextRotationPointBottomDup;

		nextRotationPointTop.position = glm::rotateY(rotationPointTop.position, rotationAngle);
		nextRotationPointBottom.position = glm::rotateY(rotationPointBottom.position, rotationAngle);

		nextRotationPointTopDup.position = nextRotationPointTop.position;
		nextRotationPointBottomDup.position = nextRotationPointBottom.position;



		// Uv solve
		float uvRotation = i * rotationAngle;
		float nextUvRotation = (i + 1) * rotationAngle;

		rotationPointTop.uv = glm::vec2(glm::cos(uvRotation) * 0.5 + 0.5, glm::sin(uvRotation) * 0.5 + 0.5);;
		nextRotationPointTop.uv = glm::vec2(glm::cos(nextUvRotation) * 0.5 + 0.5, glm::sin(nextUvRotation) * 0.5 + 0.5);


		rotationPointBottom.uv = rotationPointTop.uv;
		nextRotationPointBottom.uv = nextRotationPointTop.uv;
		nextRotationPointBottomDup.uv = nextRotationPointBottom.uv;


		rotationPointTopDup.uv = glm::vec2((1.0 * i) / sides, 1);
		rotationPointBottomDup.uv = glm::vec2((1.0 * i) / sides, 0);
		nextRotationPointTopDup.uv = glm::vec2((1.0 * (i + 1))/ sides, 1);
		nextRotationPointBottomDup.uv = glm::vec2((1.0 * (i + 1)) / sides, 0);
		



		// Top face
		addVertex(originTop);
		addVertex(rotationPointTop);
		addVertex(nextRotationPointTop);
		addIndices(glm::ivec3(size, size + 1, size + 2));
		size += 3;
		
		// Bottom face
		addVertex(originBottom);
		addVertex(rotationPointBottom);
		addVertex(nextRotationPointBottom);
		addIndices(glm::ivec3(size + 2, size + 1, size));
		size += 3;

		// Side edges
		addVertex(rotationPointTopDup);
		addVertex(rotationPointBottomDup);
		addVertex(nextRotationPointBottomDup);
		addIndices(glm::ivec3(size, size + 1, size + 2));
		size += 3;

		addVertex(rotationPointTopDup);
		addVertex(nextRotationPointBottomDup);
		addVertex(nextRotationPointTopDup);
		addIndices(glm::ivec3(size, size + 1, size + 2));
		size += 3;
		
		rotationPointTop = nextRotationPointTop;
		rotationPointBottom = nextRotationPointBottom;
		rotationPointTopDup = nextRotationPointTopDup;
		rotationPointBottomDup = nextRotationPointBottomDup;

		
	}
}


Cylinder::~Cylinder() {
}
