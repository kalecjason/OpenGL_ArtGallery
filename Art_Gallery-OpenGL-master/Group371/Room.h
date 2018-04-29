#pragma once
#include "Mesh.h"
#include "Cube.h"
#include "Texture.h"
#include "Painting.h"
#include "Pedestal.h"
#include "RandomShape.h"
#include "Bench.h"
#include "Light.h"

class Room : public Mesh {
public:
	Room(float length, float width, float height = 3.0f, float x = 0, float y = 0);
	~Room();

	bool intersects(Room);
	
	void setLeftOpening(float from, float to);
	void setRightOpening(float from, float to);
	void setFrontOpening(float from, float to);
	void setBackOpening(float from, float to);

	const glm::vec2 getPosition();
	const float getLength();
	const float getWidth();
	const float getHeight();
	glm::vec2 getTopLeft();
	glm::vec2 getBottomRight();
	std::vector<Light> getLights();

	bool hasLeftOpening() { return hasLeftOpen; };
	bool hasRightOpening() { return hasRightOpen; };
	bool hasFrontOpening() { return hasFrontOpen; };
	bool hasBackOpening() { return hasBackOpen; };

	void addArtPieces();
	virtual std::vector<BoundingBox> getBoundingBox();
private:
	enum WallSide { LEFT, RIGHT, FRONT, BACK };
	Mesh getXOpening(float from, float to, bool isLeft);
	Mesh getYOpening(float from, float to, bool isFront);

	Painting* getRandomPainting(float minLength, float maxLength, float minheight, float maxHeight);
	Pedestal* getRandomPedestal(float length, float width, float height);
	RandomShape* getRandomShape(float length, float width, float height);
	void addToWall(WallSide, Mesh*, float at, float width, float atHeight);
	std::vector<glm::vec2> getOpenings(WallSide, float padding = 0.3f);

	void onChange();
	void onChangeLeft();
	void onChangeRight();
	void onChangeFront();
	void onChangeBack();

	//walls & center
	MeshManager manager;
	Mesh* left;
	Mesh* right;
	Mesh* front;
	Mesh* back;
	Cube center;
	bool hasLeftOpen, hasRightOpen, hasFrontOpen, hasBackOpen;
	glm::vec2 leftOpening, rightOpening, frontOpening, backOpening;

	float length, width, height;
	glm::vec2 position;

	MeshManager objectManager;
	std::vector<Mesh*> objects;

	Mesh roomMesh;
	void setColors(Cube&);

	float sides_size = 0.0000001f;
};

