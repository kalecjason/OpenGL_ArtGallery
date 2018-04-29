#ifndef HALLWAY_H
#define HALLWAY_H

#include "Cube.h"
#include "MeshManager.h"
#include "Texture.h"

class Hallway : public Mesh {
public:
	enum HallwayDirection { HORIZONTAL, VERTICAL };

	Hallway(HallwayDirection direction, float length, float width, float height, bool front, bool left = true, bool right = true);
	~Hallway();

	void attach(Hallway*);
	std::vector<BoundingBox> getBoundingBox();
	void translateMesh(glm::vec3 translate);
private:
	void createHorizontalHallway();
	void createVerticalHallway();

	MeshManager manager;
	void onChange();

	void setColors(Cube&);
	float length;
	float width;
	float height;
	bool left;
	bool right;
	bool front;
	HallwayDirection direction;

	Cube* hallway;
	Cube* edge;
	std::vector<Hallway*> attachments;
};

#endif // !HALLWAY_H