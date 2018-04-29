#include "Hallway.h"


Hallway::Hallway(HallwayDirection direction, float length, float width, float height, bool front, bool left, bool right) : length(length), width(width), height(height), left(left), right(right), front(front), direction(direction){
	hallway = new Cube();
	edge = new Cube();

	if (direction == HallwayDirection::HORIZONTAL) {
		createHorizontalHallway();
	}
	else {
		createVerticalHallway();
	}

	onChange();
}

void Hallway::createHorizontalHallway() {
	if (length > width) {
		hallway->setFront(false);
		hallway->setBack(false);
		setColors(*hallway);
		hallway->localScaleMesh(glm::vec3(width, height, length - width));
		hallway->translateMesh(glm::vec3(0.0f, 0.0f, -(width / 2.0f)));

		manager.addMesh(hallway);
	}

	edge->setBack(false);
	edge->setFront(!front);
	if (left)
		edge->setLeft(!left);
	if (right)
		edge->setRight(!right);
	setColors(*edge);
	edge->localScaleMesh(glm::vec3(width, height, length > width ? width : length));
	if (length > width)
		edge->translateMesh(glm::vec3(0.0f, 0.0f, (length - width) / 2.0f));

	manager.addMesh(edge);
}

void Hallway::createVerticalHallway() {
	if (length > width) {
		hallway->setLeft(false);
		hallway->setRight(false);
		setColors(*hallway);
		hallway->localScaleMesh(glm::vec3(length - width, height, width));
		hallway->translateMesh(glm::vec3(-(width / 2.0f), 0.0f, 0.0f));

		manager.addMesh(hallway);
	}

	edge->setRight(false);
	edge->setLeft(!front);
	if (left)
		edge->setBack(!left);
	if (right)
		edge->setFront(!right);
	setColors(*edge);
	edge->localScaleMesh(glm::vec3(length > width ? width : length, height, width));
	if (length > width)
		edge->translateMesh(glm::vec3((length - width) / 2.0f, 0.0f, 0.0f));

	manager.addMesh(edge);
}

Hallway::~Hallway() {
	delete edge;
	delete hallway;
}

void Hallway::onChange() {
	manager.computeMergedMesh();
	Mesh computedMesh = manager.finalMesh;
	vertices = computedMesh.getVertices();
	indices = computedMesh.getIndices();
}

void Hallway::setColors(Cube& cube) {
	int mix = 50;
	float repeat = 3;
	Material m = MATERIAL_EMERALD;
	Material m2 = MATERIAL_RED_PLASTIC;

	cube.setFaceTexture(CubeFace::front, Texture::getTexture("wall"), repeat, repeat);
	cube.setFaceTexture(CubeFace::back, Texture::getTexture("wall"), repeat, repeat);
	cube.setFaceMix(CubeFace::left, m, Texture::getTexture("wall"), repeat, repeat, 50);
	cube.setFaceMix(CubeFace::right, m2, Texture::getTexture("wall"), repeat, repeat, 50);
	cube.setFaceTexture(CubeFace::bottom, Texture::getTexture("floor"), length / 3.0f, 1);
	cube.setFaceTexture(CubeFace::top, Texture::getTexture("wall"));
}

void Hallway::attach(Hallway* h) {
	if (direction == HallwayDirection::HORIZONTAL) {
		//assuming we are smart enough to only attach vertical to horizontal and vice verst
		//could change in future if necessary or if we want branching hallways (attach horizontal to horizontal, leave the left opening)
		if (left) {
			h->translateMesh(glm::vec3(width / 2.0f + h->length / 2.0f, 0.0f, length / 2.0f - width / 2.0f));
		}
		else {
			h->translateMesh(glm::vec3(-(width / 2.0f + h->length / 2.0f), 0.0f, length / 2.0f - width / 2.0f));
		}
	}
	else {
		if (left) {
			h->translateMesh(glm::vec3(length / 2.0f - width / 2.0f, 0.0f, -width / 2.0f - h->length / 2.0f));
		}
		else {
			h->translateMesh(glm::vec3(length / 2.0f - width / 2.0f, 0.0f, width / 2.0f + h->length / 2.0f));
		}
	}

	attachments.push_back(h);
	manager.addMesh(h);
	onChange();
}

std::vector<BoundingBox> Hallway::getBoundingBox() {
	std::vector<BoundingBox> boxes;

	if(length > width)
		for (BoundingBox box : hallway->getBoundingBox())
			boxes.push_back(box);

	for (BoundingBox box : edge->getBoundingBox())
		boxes.push_back(box);

	for (Hallway* h : attachments)
		for (BoundingBox box : h->getBoundingBox())
			boxes.push_back(box);

	return boxes;
}

void Hallway::translateMesh(glm::vec3 translate) {
	hallway->translateMesh(translate);
	edge->translateMesh(translate);
	for (Hallway* h : attachments) {
		h->translateMesh(translate);
	}
	onChange();
}