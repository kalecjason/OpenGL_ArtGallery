#include "Cube.h"


// Outside faces are culled
Cube::Cube(bool leftside, bool rightside, bool topside, bool bottomside, bool frontside, bool backside) {
	left = new Mesh();
	right = new Mesh();
	top = new Mesh();
	bottom = new Mesh();
	front = new Mesh();
	back = new Mesh();

	//manager compute called for nothing in these, the function doesnt do much at least, sorry ~raz :)
	setLeft(leftside);
	setRight(rightside);
	setTop(topside);
	setBottom(bottomside);
	setFront(frontside);
	setBack(backside);
	
	manager.addMesh(left);
	manager.addMesh(right);
	manager.addMesh(top);
	manager.addMesh(bottom);
	manager.addMesh(front);
	manager.addMesh(back);

	onChange();
}

Cube::~Cube() {
	//delete left, right, front, back, top, bottom;
}

void Cube::setSides(bool left, bool right, bool top, bool bottom, bool front, bool back) {
	setLeft(left);
	setRight(right);
	setTop(top);
	setBottom(bottom);
	setFront(front);
	setBack(back);
}


void Cube::onChange() {
	//recompute mesh on changes
	manager.computeMergedMesh();
	Mesh computedMesh = manager.finalMesh;
	vertices = computedMesh.getVertices();
	indices = computedMesh.getIndices();
}

Mesh* Cube::faceSwith(CubeFace face) {
	switch (face) {
		case CubeFace::left: return left;
		case CubeFace::right: return right;
		case CubeFace::top: return top;
		case CubeFace::bottom: return bottom;
		case CubeFace::front: return front;
		case CubeFace::back: return back;
		default: ;
	}
}

void Cube::setLeft(bool b) {
	left->reset();
	if (b) {

		Vertex v1 = Vertex(glm::vec3(0.5f, 0.5f, 0.5f)); // top far left
		Vertex v2 = Vertex(glm::vec3(0.5f, 0.5f, -0.5f)); // top near left
		Vertex v3 = Vertex(glm::vec3(0.5f, -0.5f, -0.5f)); // bottom near left;
		Vertex v4 = Vertex(glm::vec3(0.5f, -0.5f, 0.5f)); // bottom far left
		// Set textures
		v1.uv = glm::vec2(1, 1);
		v2.uv = glm::vec2(0, 1);
		v3.uv = glm::vec2(0, 0);
		v4.uv = glm::vec2(1, 0);

		left->addVertex(v1); // top far left
		left->addVertex(v2); // top near left
		left->addVertex(v3); // bottom near left
		left->addVertex(v4); // bottom far left
		left->addIndices(glm::vec3(1, 2, 0));
		left->addIndices(glm::vec3(0, 2, 3));
	}
	onChange();
}
void Cube::setRight(bool b) {
	right->reset();
	if (b) {


		Vertex v1 = Vertex(glm::vec3(-0.5f, 0.5f, 0.5f)); // top far right
		Vertex v2 = Vertex(glm::vec3(-0.5f, 0.5f, -0.5f)); // top near right
		Vertex v3 = Vertex(glm::vec3(-0.5f, -0.5f, -0.5f)); // bottom near right
		Vertex v4 = Vertex(glm::vec3(-0.5f, -0.5f, 0.5f)); // bottom far right
														  
		v1.uv = glm::vec2(1, 1);
		v2.uv = glm::vec2(0, 1);
		v3.uv = glm::vec2(0, 0);
		v4.uv = glm::vec2(1, 0);


		right->addVertex(v1);
		right->addVertex(v2);
		right->addVertex(v3);
		right->addVertex(v4);
		right->addIndices(glm::vec3(0, 2, 1));
		right->addIndices(glm::vec3(3, 2, 0));
	}
	onChange();
}
void Cube::setTop(bool b) {
	top->reset();
	if (b) {


		Vertex v1 = Vertex(glm::vec3(0.5f, 0.5f, 0.5f)); // top far right
		Vertex v2 = Vertex(glm::vec3(0.5f, 0.5f, -0.5f)); // top near right
		Vertex v3 = Vertex(glm::vec3(-0.5f, 0.5f, -0.5f)); // top near left
		Vertex v4 = Vertex(glm::vec3(-0.5f, 0.5f, 0.5f)); // top far left

		v1.uv = glm::vec2(1, 1);
		v2.uv = glm::vec2(0, 1);
		v3.uv = glm::vec2(0, 0);
		v4.uv = glm::vec2(1, 0);


		top->addVertex(v1);
		top->addVertex(v2);
		top->addVertex(v3);
		top->addVertex(v4);

		top->addIndices(glm::vec3(2, 1, 0));
		top->addIndices(glm::vec3(3, 2, 0));
	}
	onChange();
}
void Cube::setBottom(bool b) {
	bottom->reset();
	if (b) {
		
		Vertex v1 = Vertex(glm::vec3(0.5f, -0.5f, 0.5f));
		Vertex v2 = Vertex(glm::vec3(0.5f, -0.5f, -0.5f));
		Vertex v3 = Vertex(glm::vec3(-0.5f,-0.5f, -0.5f));
		Vertex v4 = Vertex(glm::vec3(-0.5f,-0.5f, 0.5f));
		// Set textures
		v1.uv = glm::vec2(1, 1);
		v2.uv = glm::vec2(0, 1);
		v3.uv = glm::vec2(0, 0);
		v4.uv = glm::vec2(1, 0);

		bottom->addVertex(v1);// bottom far right
		bottom->addVertex(v2); // bottom near right
		bottom->addVertex(v3); // bottom near left
		bottom->addVertex(v4); // bottom far left
		bottom->addIndices(glm::vec3(0, 1, 2));
		bottom->addIndices(glm::vec3(0, 2, 3));
	}
	onChange();
}
void Cube::setFront(bool b) {
	front->reset();
	if (b) {


		Vertex v1 = Vertex(glm::vec3(-0.5f, 0.5f, 0.5f)); // top far left
		Vertex v2 = Vertex(glm::vec3(0.5f, 0.5f, 0.5f)); // top far right
		Vertex v3 = Vertex(glm::vec3(-0.5f, -0.5f, 0.5f)); // bottom far left
		Vertex v4 = Vertex(glm::vec3(0.5f, -0.5f, 0.5f)); // bottom far right
		// Set textures
		v1.uv = glm::vec2(0, 1);
		v2.uv = glm::vec2(1, 1);
		v3.uv = glm::vec2(0, 0);
		v4.uv = glm::vec2(1, 0);


		front->addVertex(v1);
		front->addVertex(v2);
		front->addVertex(v3);
		front->addVertex(v4);
		front->addIndices(glm::vec3(1, 2, 0));
		front->addIndices(glm::vec3(3, 2, 1));
	}
	onChange();
}
void Cube::setBack(bool b) {
	back->reset();
	if (b) {


		Vertex v1 = Vertex(glm::vec3(-0.5f, 0.5f, -0.5f)); // top near left
		Vertex v2 = Vertex(glm::vec3(0.5f, 0.5f, -0.5f)); // top near right
		Vertex v3 = Vertex(glm::vec3(-0.5f, -0.5f, -0.5f)); // bottom near left
		Vertex v4 = Vertex(glm::vec3(0.5f, -0.5f, -0.5f)); // bottom near right
														  
		v1.uv = glm::vec2(0, 1);
		v2.uv = glm::vec2(1, 1);
		v3.uv = glm::vec2(0, 0);
		v4.uv = glm::vec2(1, 0);


		back->addVertex(v1);
		back->addVertex(v2);
		back->addVertex(v3);
		back->addVertex(v4);

		back->addIndices(glm::vec3(0, 2, 1));
		back->addIndices(glm::vec3(1, 2, 3));
	}
	onChange();
}

// TODO remove
void Cube::setLeftColor(glm::vec4 color) {
	left->setColor(color);
	onChange();
}
void Cube::setRightColor(glm::vec4 color) {
	right->setColor(color);
	onChange();
}
void Cube::setTopColor(glm::vec4 color) {
	top->setColor(color);
	onChange();
}
void Cube::setBottomColor(glm::vec4 color) {
	bottom->setColor(color);
	onChange();
}
void Cube::setFrontColor(glm::vec4 color) {
	front->setColor(color);
	onChange();
}
void Cube::setBackColor(glm::vec4 color) {
	back->setColor(color);
	onChange();
}

void Cube::setMaterial(const Material& material) {
	left->setMaterial(material);
	right->setMaterial(material);
	top->setMaterial(material);
	bottom->setMaterial(material);
	front->setMaterial(material);
	back->setMaterial(material);
	onChange();
}

void Cube::setFaceMaterial(CubeFace face, const Material material) {
	Mesh* meshFace = faceSwith(face);
	meshFace->setMaterial(material);
	onChange();
}

void Cube::setFaceTexture(CubeFace face, Texture texture, float repeatX, float repeatY) {
	Mesh* meshFace = faceSwith(face);
	meshFace->setTexture(texture, repeatX, repeatY);
	onChange();
}

void Cube::setFaceMix(CubeFace face, Material material, Texture texture, float repeatX, float repeatY, int mix) {
	Mesh* meshFace = faceSwith(face);
	meshFace->mix(material, texture, repeatX, repeatY, mix);
	onChange();
}

std::vector<BoundingBox> Cube::getBoundingBox() {
	float extraSpace = 0.135f;
	std::vector<BoundingBox> boxes;

	if (!left->getVertices().empty()) {
		BoundingBox l;
		l.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		l.min = glm::vec3(this->maxXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(l);
	}

	if (!right->getVertices().empty()) {
		BoundingBox r;
		r.max = glm::vec3(this->minXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		r.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(r);
	}

	if (!front->getVertices().empty()) {
		BoundingBox f;
		f.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		f.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->maxXYZ.z - extraSpace);
		boxes.push_back(f);
	}

	if (!back->getVertices().empty()) {
		BoundingBox b;
		b.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->minXYZ.z + extraSpace);
		b.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(b);
	}

	if (!top->getVertices().empty()) {
		BoundingBox t;
		t.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		t.min = glm::vec3(this->minXYZ.x - extraSpace, this->maxXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(t);
	}

	if (!bottom->getVertices().empty()) {
		BoundingBox bot;
		bot.max = glm::vec3(this->maxXYZ.x + extraSpace, this->minXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		bot.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(bot);
	}

	return boxes;
};
