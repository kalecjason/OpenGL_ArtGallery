
#include "Plane.h"


Plane::Plane() {
	// Bottom face
	Vertex v1 = Vertex(glm::vec3(0.5f, 0, 0.5f));
	Vertex v2 = Vertex(glm::vec3(0.5f, 0, -0.5f));
	Vertex v3 = Vertex(glm::vec3(-0.5f, 0, -0.5f));
	Vertex v4 = Vertex(glm::vec3(-0.5f, 0, 0.5f));

	// Set textures
	v1.uv = glm::vec2(1,1);
	v2.uv = glm::vec2(1,0);
	v3.uv = glm::vec2(0,0);
	v4.uv = glm::vec2(0,1);

	addVertex(v1);// bottom far right
	addVertex(v2); // bottom near right
	addVertex(v3); // bottom near left
	addVertex(v4); // bottom far left
	addIndices(glm::vec3(0, 1, 2));
	addIndices(glm::vec3(0, 2, 3));
}


Plane::~Plane() {
}
