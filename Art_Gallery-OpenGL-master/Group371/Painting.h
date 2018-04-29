#ifndef PAINTING_H
#define PAINTING_H

#include "Mesh.h"
#include "MeshManager.h"
#include "Cube.h"
#include "Plane.h"


class Painting : public Mesh {
public:
	Painting(float length, float height, float width);
	~Painting();

	void addFrame();		//back picture frame
	void addCanvas();	//blank canvas to be drawn on
	void addShapes();	//shape to be drawn on canvas
	void addRandomShape(float minusX, float x, float minusY, float y, float z);

	float getLength() { return length; };
	float getHeight() { return height; };
	float getWidth() { return width; };

	static const float FRAME_LENGTH;
private:
	void onChange();

	MeshManager manager;

	float height, length, width;

	Mesh* back;
	Mesh* canvas;
	Mesh* shape;

	std::vector<Mesh*> randomShapes;
};

#endif // !PAINTING_H