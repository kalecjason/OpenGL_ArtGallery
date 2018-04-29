#ifndef BENCH_H
#define BENCH_H

#include "Mesh.h"
#include "MeshManager.h"
#include "Cube.h"
#include "Plane.h"
#include <unordered_map>


class Bench : public Mesh {
public:
	Bench();
	Bench(float length, float height, float width);
	
	~Bench();

	void addBench();		

	float getLength() { return length; };
	float getHeight() { return height; };
	float getWidth() { return width; };

	virtual std::vector<BoundingBox> getBoundingBox();

	static const float BENCH_LENGTH;
private:
	void onChange();

	MeshManager manager;

	float height, length, width;

	Mesh* bench;

	std::unordered_map<std::string, Texture>* textureMap;
};

#endif // !BENCH_H