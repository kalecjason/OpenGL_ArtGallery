
#ifndef CUBE_H
#define CUBE_H

#include "Mesh.h"
#include "MeshManager.h"

enum CubeFace {
	left,
	right,
	top,
	bottom,
	front,
	back
};



class Cube : public Mesh {
public:
	Cube(bool leftside = true, bool rightside = true, bool topside = true, bool bottomside = true, bool frontside = true, bool backside = true);
	~Cube();

	void setSides(bool left, bool right, bool top, bool bottom, bool front, bool back);
	void setLeft(bool);
	void setRight(bool);
	void setTop(bool);
	void setBottom(bool);
	void setFront(bool);
	void setBack(bool);

	// TODO: deprecated
	void setLeftColor(glm::vec4);
	void setRightColor(glm::vec4);
	void setTopColor(glm::vec4);
	void setBottomColor(glm::vec4);
	void setFrontColor(glm::vec4);
	void setBackColor(glm::vec4);

	// Sets material for all faces
	void setMaterial(const Material& material);
	void setFaceMaterial(CubeFace face, const Material material);
	void setFaceTexture(CubeFace face, Texture texture, float repeatX = 1.0, float repeatY = 1.0);
	void setFaceMix(CubeFace face, Material material, Texture texture, float repeatX = 1.0, float repeatY = 1.0, int mix = 50);

	virtual std::vector<BoundingBox> getBoundingBox();
private:
	void onChange();
	Mesh* faceSwith(CubeFace face);
	MeshManager manager;

	Mesh* left;
	Mesh* right;

	Mesh* front;
	Mesh* back;

	Mesh* top;
	Mesh* bottom;
};

#endif // !CUBE_H