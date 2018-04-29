#include "Room.h"
#include <iostream>

Room::Room(float length, float width, float height, float x, float y) : width(width), length(length), height(height), position(x, y) {
	center.setSides(false, false, true, true, false, false);
	setColors(center);
	center.localScaleMesh(glm::vec3(1.0f - sides_size, 1.0f, 1.0f - sides_size));
	manager.addMesh(&center);

	Cube* leftc = new Cube(true, false, true, true, false, false);
	setColors(*leftc);
	left = leftc;
	manager.addMesh(left);

	Cube* rightc = new Cube(false, true, true, true, false, false);
	setColors(*rightc);
	right = rightc;
	manager.addMesh(right);

	Cube* frontc = new Cube(false, false, true, true, true, false);
	setColors(*frontc);
	front = frontc;
	manager.addMesh(front);

	Cube* backc = new Cube(false, false, true, true, false, true);
	setColors(*backc);
	back = backc;
	manager.addMesh(back);

	onChangeLeft();
	onChangeRight();
	onChangeFront();
	onChangeBack();
	onChange();
}

Room::~Room() {
	//delete left, right, front, back;
}

void Room::onChange() {
	//recompute mesh on changes
	MeshManager m;

	manager.computeMergedMesh();
	Mesh roomMesh = manager.finalMesh;
	roomMesh.localScaleMesh(glm::vec3(width, height, length));
	roomMesh.translateMesh(glm::vec3(position.y, 0.0f, position.x));

	for (Mesh* art : objects) {
		art->translateMesh(glm::vec3(position.y, 0.0f, position.x));
	}
	objectManager.computeMergedMesh();
	Mesh objectsMesh = objectManager.finalMesh;

	m.addMesh(roomMesh);
	m.addMesh(objectsMesh);
	m.computeMergedMeshCopies();
	Mesh final = m.finalMesh;

	vertices = final.getVertices();
	indices = final.getIndices();
	maxXYZ = roomMesh.maxXYZ;
	minXYZ = roomMesh.minXYZ;
}

void Room::onChangeLeft() {
	left->localScaleMesh(glm::vec3(sides_size, 1.0f, 1.0f));
	left->translateMesh(glm::vec3(0.5f - (sides_size / 2.0f), 0.0f, 0.0f));
}
void Room::onChangeRight() {
	right->localScaleMesh(glm::vec3(sides_size, 1.0f, 1.0f));
	right->translateMesh(glm::vec3(-0.5f + (sides_size / 2.0f), 0.0f, 0.0f));
}
void Room::onChangeFront() {
	front->localScaleMesh(glm::vec3(1.0f, 1.0f, sides_size));
	front->translateMesh(glm::vec3(0.0f, 0.0f, 0.5f - (sides_size / 2.0f)));
}
void Room::onChangeBack() {
	back->localScaleMesh(glm::vec3(1.0f, 1.0f, sides_size));
	back->translateMesh(glm::vec3(0.0f, 0.0f, -0.5f + (sides_size / 2.0f)));
}

bool Room::intersects(Room room) {
	float aLeft = position.x - (length / 2.0f);
	float aRight = position.x + (length / 2.0f);
	float aTop = position.y + (width / 2.0f);
	float aBottom = position.y - (width / 2.0f);

	float bLeft = room.position.x - (room.length / 2.0f);
	float bRight = room.position.x + (room.length / 2.0f);
	float bTop = room.position.y + (room.width / 2.0f);
	float bBottom = room.position.y - (room.width / 2.0f);

	return (aLeft <= bRight && aRight >= bLeft && aTop >= bBottom && aBottom <= bTop);
}

Mesh Room::getXOpening(float from, float to, bool isLeft) {
	//limit from/to to object length
	from = from > length ? length : from;
	to = to > length ? length : to;

	//normalize to 0-1
	from = from / length;
	to = to / length;

	Cube hole(false, false, true, true, false, false);
	Cube c1(isLeft, !isLeft, true, true, false, false);
	Cube c2(isLeft, !isLeft, true, true, false, false);

	setColors(hole);
	setColors(c1);
	setColors(c2);

	float holeSize = to - from;
	float c1size = from;
	float c2size = 1.0f - to;

	hole.localScaleMesh(glm::vec3(1.0f, 1.0f, holeSize));
	c1.localScaleMesh(glm::vec3(1.0f, 1.0f, c1size));
	c2.localScaleMesh(glm::vec3(1.0f, 1.0f, c2size));

	hole.translateMesh(glm::vec3(0.0f, 0.0f, -0.5 + from + holeSize / 2.0f));
	c1.translateMesh(glm::vec3(0.0f, 0.0f, -0.5 + c1size / 2.0f));
	c2.translateMesh(glm::vec3(0.0f, 0.0f, -0.5 + to + c2size / 2.0f));

	MeshManager manager;
	manager.addMesh(hole);
	manager.addMesh(c1);
	manager.addMesh(c2);
	manager.computeMergedMeshCopies();
	return manager.finalMesh;
}

Mesh Room::getYOpening(float from, float to, bool isFront) {
	//limit from/to to object width
	from = from > width ? width : from;
	to = to > width ? width : to;

	//normalize to 0-1
	from = from / width;
	to = to / width;

	Cube hole(false, false, true, true, false, false);
	Cube c1(false, false, true, true, isFront, !isFront);
	Cube c2(false, false, true, true, isFront, !isFront);

	setColors(hole);
	setColors(c1);
	setColors(c2);

	float holeSize = to - from;
	float c1size = from;
	float c2size = 1.0f - to;

	hole.localScaleMesh(glm::vec3(holeSize, 1.0f, 1.0f));
	c1.localScaleMesh(glm::vec3(c1size, 1.0f, 1.0f));
	c2.localScaleMesh(glm::vec3(c2size, 1.0f, 1.0f));

	hole.translateMesh(glm::vec3(-0.5 + from + holeSize / 2.0f, 0.0f, 0.0f));
	c1.translateMesh(glm::vec3(-0.5 + c1size / 2.0f, 0.0f, 0.0f));
	c2.translateMesh(glm::vec3(-0.5 + to + c2size / 2.0f, 0.0f, 0.0f));

	MeshManager manager;
	manager.addMesh(hole);
	manager.addMesh(c1);
	manager.addMesh(c2);
	manager.computeMergedMeshCopies();
	return manager.finalMesh;
}

void Room::setLeftOpening(float from, float to) {
	//if from and to are the same, we have nothing to do
	if (from == to)
		return;

	Mesh mesh = getXOpening(from, to, true);
	hasLeftOpen = true;
	leftOpening = glm::vec2(from, to);

	left->reset();
	left->addVertices(mesh.getVertices());
	left->addIndices(mesh.getIndices());

	onChangeLeft();
	onChange();
}

void Room::setRightOpening(float from, float to) {
	//if from and to are the same, we have nothing to do
	if (from == to)
		return;

	Mesh mesh = getXOpening(from, to, false);
	hasRightOpen = true;
	rightOpening = glm::vec2(from, to);

	right->reset();
	right->addVertices(mesh.getVertices());
	right->addIndices(mesh.getIndices());

	onChangeRight();
	onChange();
}

void Room::setFrontOpening(float from, float to) {
	//if from and to are the same, we have nothing to do
	if (from == to)
		return;

	Mesh mesh = getYOpening(from, to, true);
	hasFrontOpen = true;
	frontOpening = glm::vec2(from, to);

	front->reset();
	front->addVertices(mesh.getVertices());
	front->addIndices(mesh.getIndices());

	onChangeFront();
	onChange();
}

void Room::setBackOpening(float from, float to) {
	//if from and to are the same, we have nothing to do
	if (from == to)
		return;

	Mesh mesh = getYOpening(from, to, false);
	hasBackOpen = true;
	backOpening = glm::vec2(from, to);

	back->reset();
	back->addVertices(mesh.getVertices());
	back->addIndices(mesh.getIndices());

	onChangeBack();
	onChange();
}

void Room::setColors(Cube& cube) {
	int mix = 50;
	float repeat = 2;

	if (rand() % 2 == 0) {
		Material m = randomMaterial();
		cube.setFaceMix(CubeFace::front, m, Texture::getTexture("wall"), repeat, repeat, mix);
	}
	else {
		cube.setFaceTexture(CubeFace::front, Texture::getTexture("wall"), repeat, repeat);
	}
	if (rand() % 2 == 0) {
		Material m = randomMaterial();
		cube.setFaceMix(CubeFace::back, m, Texture::getTexture("wall"), repeat, repeat, mix);
	}
	else {
		cube.setFaceTexture(CubeFace::back, Texture::getTexture("wall"), repeat, repeat);
	}
	if (rand() % 2 == 0) {
		Material m = randomMaterial();
		cube.setFaceMix(CubeFace::left, m, Texture::getTexture("wall"), repeat, repeat, mix);
	}
	else {
		cube.setFaceTexture(CubeFace::left, Texture::getTexture("wall"), repeat, repeat);
	}
	if (rand() % 2 == 0) {
		Material m = randomMaterial();
		cube.setFaceMix(CubeFace::right, m, Texture::getTexture("wall"), repeat, repeat, mix);
	}
	else {
		cube.setFaceTexture(CubeFace::right, Texture::getTexture("wall"), repeat, repeat);
	}

	cube.setFaceTexture(CubeFace::bottom, Texture::getTexture("floor"), 8, 16);
	cube.setFaceTexture(CubeFace::top, Texture::getTexture("wall"));
}

const glm::vec2 Room::getPosition() {
	return position;
}
const float Room::getLength() {
	return length;
}
const float Room::getWidth() {
	return width;
}
const float Room::getHeight() {
	return height;
}

glm::vec2 Room::getTopLeft() {
	return glm::vec2(getPosition().x - getLength() / 2.0f, getPosition().y + getWidth() / 2.0f);
}

glm::vec2 Room::getBottomRight() {
	return glm::vec2(getPosition().x + getLength() / 2.0f, getPosition().y - getWidth() / 2.0f);
}

std::vector<Light> Room::getLights() {
	std::vector<Light> lights;
	float lightheight = 0;
	glm::vec3 topLeft(position.y + width / 4.0f, lightheight, position.x - length / 4.0f);
	glm::vec3 topRight(position.y + width / 4.0f, lightheight, position.x + length / 4.0f);

	glm::vec3 bottomLeft(position.y - width / 4.0f, lightheight, position.x - length / 4.0f);
	glm::vec3 bottomRight(position.y - width / 4.0f, lightheight, position.x + length / 4.0f);

	glm::vec3 middleLeft(position.y, lightheight, position.x - length / 4.0f);
	glm::vec3 middleRight(position.y, lightheight, position.x + length / 4.0f);
	glm::vec3 middleTop(position.y + width / 4.0f, lightheight, position.x);
	glm::vec3 middleBottom(position.y - width / 4.0f, lightheight, position.x);
	
	Light low = LIGHT_DISTANCE_20;
	Light high = LIGHT_DISTANCE_32;

	Light light1 = width > 10.0f && length > 10.0f ? high : low;
	light1.position = middleTop;
	lights.push_back(light1);
	if (width > 10.0f || length > 10.0f) {
		Light light2 = high;
		light2.position = middleBottom;
		lights.push_back(light2);
	}

	return lights;
}

void Room::addArtPieces() {
	//min-max sizes
	float minPaintingHeight = height / 6.0f;
	float maxPaintingHeight = height / 3.0f;
	float minPaintingLength = 1.0f;
	float maxPaintingLength = 4.25f;

	float pedestalHeight = 1.25f;
	float pedestalWidth = 0.25f;
	float pedestalLength = 0.25f;

	std::vector<float> addAtHeights = {height*2/3 - 0.25f*2 - maxPaintingHeight/2.0f, height - 0.25f - maxPaintingHeight/2.0f};

	//go through for each height  (so that paintings can be at different places throughout a wall)
	for (float atHeight : addAtHeights) {
		//fill each wall
		for (int i = 0; i < 4; i++) {
			WallSide side = (WallSide)i;

			//get the empty wall parts on this wall
			std::vector<glm::vec2> openings = getOpenings(side);
			for (glm::vec2 openarea : openings) {
				//as long as we can add another painting
				while (openarea.y - openarea.x >= minPaintingLength) {
					float openingLength = openarea.y - openarea.x;
					float maxLength = openingLength >= maxPaintingLength ? maxPaintingLength : openingLength;

					Painting* painting = getRandomPainting(minPaintingLength, maxLength, minPaintingHeight, maxPaintingHeight);
					addToWall(side, painting, openarea.x + painting->getLength() / 2.0f, painting->getWidth(), atHeight);

					openarea.x += painting->getLength() + 0.5f;
				}
			}
		}
	}

	//fill each wall once
	for (int i = 0; i < 4; i++) {
		WallSide side = (WallSide)i;

		//get the empty wall parts on this wall
		std::vector<glm::vec2> openings = getOpenings(side);

		for (glm::vec2 openarea : openings) {
			openarea.x += 0.75f;
			//as long as we can add another painting
			while (openarea.y - openarea.x >= pedestalLength + 0.75) {
				//if we can add another pedestal and have some space
				Pedestal* pedestal = getRandomPedestal(pedestalLength, pedestalWidth, pedestalHeight);
				addToWall(side, pedestal, (openarea.x + pedestalLength / 2.0f), pedestalWidth, pedestalHeight / 2.0f);

				float minHeight = pedestalHeight / 10.0f;
				float maxHeight = pedestalHeight / 2.0f;
				float shapeHeight = minHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxHeight - minHeight)));
				RandomShape* shape = getRandomShape(pedestalLength, pedestalWidth, shapeHeight);
				addToWall(side, shape, (openarea.x + pedestalLength / 2.0f), pedestalWidth, pedestalHeight + shapeHeight / 2.0f);

				openarea.x += pedestalLength + 1.75f;
			}
		}
	}

	//center
	Pedestal* ped = new Pedestal();
	float center_pedestal_width = width / 4.0f;
	float center_pedestal_height = height / 6.0f;
	float center_pedestal_length = length / 4.0f;
	ped->localScaleMesh(glm::vec3(center_pedestal_width, center_pedestal_height, center_pedestal_length));
	float center_pedestal_heightPosition = -height / 2.0f + height / 6.0f / 2.0f + 0.0001f;
	ped->translateMesh(glm::vec3(0.0f, center_pedestal_heightPosition, 0.0f));
	objectManager.addMesh(ped);
	objects.push_back(ped);

	//Bench
	float benchSpacing = 0.2f;
	Bench* bench1 = new Bench(center_pedestal_width - 0.5f, 0.3f, 0.3f);
	bench1->translateMesh(glm::vec3(0.0f, -height / 2.0f + bench1->getHeight(), (center_pedestal_length / 2) + benchSpacing));
	objectManager.addMesh(bench1);
	objects.push_back(bench1);
	Bench* bench2 = new Bench(center_pedestal_width - 0.5f, 0.3f, 0.3f);
	bench2->translateMesh(glm::vec3(0.0f, -height / 2.0f + bench2->getHeight(), -(center_pedestal_length / 2) - benchSpacing));
	objectManager.addMesh(bench2);
	objects.push_back(bench2);
	Bench* bench3 = new Bench(center_pedestal_length - 0.5f, 0.3f, 0.3f);
	bench3->rotateMesh(glm::radians(90.0f), glm::vec3(0, 1, 0));
	bench3->translateMesh(glm::vec3((center_pedestal_width / 2) + benchSpacing, -height / 2.0f + bench3->getHeight(), 0.0f));
	objectManager.addMesh(bench3);
	objects.push_back(bench3);
	Bench* bench4 = new Bench(center_pedestal_length - 0.5f, 0.3f, 0.3f);
	bench4->rotateMesh(glm::radians(90.0f), glm::vec3(0, 1, 0));
	bench4->translateMesh(glm::vec3(-(center_pedestal_width / 2) - benchSpacing, -height/2.0f + bench4->getHeight(), 0.0f));
	objectManager.addMesh(bench4);
	objects.push_back(bench4);

	float minHeight = height / 8.0f;
	float maxHeight = this->height - center_pedestal_height - 0.25f;
	float shapeHeight = minHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxHeight - minHeight)));
	RandomShape* shape = getRandomShape(center_pedestal_length, center_pedestal_width, shapeHeight);
	shape->translateMesh(glm::vec3(0.0f, center_pedestal_heightPosition + center_pedestal_height/2.0f + shapeHeight/2.0f, 0.0f));
	objectManager.addMesh(shape);
	objects.push_back(shape);


	onChange();
}

std::vector<BoundingBox> Room::getBoundingBox() {
	float extraSpace = 0.135f;
	std::vector<BoundingBox> boxes;

	if (hasLeftOpening()) {
		BoundingBox l1;
		l1.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->minXYZ.z + leftOpening.x + extraSpace);
		l1.min = glm::vec3(this->maxXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(l1);

		BoundingBox l2;
		l2.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		l2.min = glm::vec3(this->maxXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z + leftOpening.y - extraSpace);
		boxes.push_back(l2);
	}
	else {
		BoundingBox l;
		l.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		l.min = glm::vec3(this->maxXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(l);
	}

	if (hasRightOpening()) {
		BoundingBox l1;
		l1.max = glm::vec3(this->minXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->minXYZ.z + rightOpening.x + extraSpace);
		l1.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(l1);

		BoundingBox l2;
		l2.max = glm::vec3(this->minXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		l2.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z + rightOpening.y - extraSpace);
		boxes.push_back(l2);
	}
	else {
		BoundingBox r;
		r.max = glm::vec3(this->minXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		r.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(r);
	}

	if (hasFrontOpening()) {
		BoundingBox f1;
		f1.max = glm::vec3(this->minXYZ.x + frontOpening.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		f1.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->maxXYZ.z - extraSpace);
		boxes.push_back(f1);
		BoundingBox f2;
		f2.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		f2.min = glm::vec3(this->minXYZ.x + frontOpening.y - extraSpace, this->minXYZ.y - extraSpace, this->maxXYZ.z - extraSpace);
		boxes.push_back(f2);
	}
	else {
		BoundingBox f;
		f.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
		f.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->maxXYZ.z - extraSpace);
		boxes.push_back(f);
	}

	if (hasBackOpening()) {
		BoundingBox b1;
		b1.max = glm::vec3(this->minXYZ.x + backOpening.x + extraSpace, this->maxXYZ.y + extraSpace, this->minXYZ.z + extraSpace);
		b1.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(b1);
		BoundingBox b2;
		b2.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->minXYZ.z + extraSpace);
		b2.min = glm::vec3(this->minXYZ.x + backOpening.y - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(b2);
	}
	else {
		BoundingBox b;
		b.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->minXYZ.z + extraSpace);
		b.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
		boxes.push_back(b);
	}

	BoundingBox t;
	t.max = glm::vec3(this->maxXYZ.x + extraSpace, this->maxXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
	t.min = glm::vec3(this->minXYZ.x - extraSpace, this->maxXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
	boxes.push_back(t);

	BoundingBox bot;
	bot.max = glm::vec3(this->maxXYZ.x + extraSpace, this->minXYZ.y + extraSpace, this->maxXYZ.z + extraSpace);
	bot.min = glm::vec3(this->minXYZ.x - extraSpace, this->minXYZ.y - extraSpace, this->minXYZ.z - extraSpace);
	boxes.push_back(bot);

	for (Mesh* art : objects) {
		for (BoundingBox box : art->getBoundingBox()) {
			boxes.push_back(box);
		}
	}

	return boxes;
}

Painting* Room::getRandomPainting(float minLength, float maxLength, float minheight, float maxHeight) {
	float paintingWidth = Painting::FRAME_LENGTH / 2.0f;
	float paintingLength = minLength + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxLength - minLength)));
	float paintingHeight = minheight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxHeight - minheight)));

	return new Painting(paintingLength, paintingHeight, paintingWidth);
}

Pedestal* Room::getRandomPedestal(float length, float width, float height) {
	Pedestal* ped = new Pedestal();
	ped->localScaleMesh(glm::vec3(width, height, length));
	return ped;
}

RandomShape* Room::getRandomShape(float length, float width, float height) {
	RandomShape* shape = new RandomShape();
	shape->localScaleMesh(glm::vec3(width, height, length));
	return shape;
}

void Room::addToWall(WallSide side, Mesh* mesh, float at, float width, float atHeight) {
	switch (side) {
	case LEFT:
		mesh->localRotateMesh(glm::radians(-90.0f), glm::vec3(0, 1, 0));
		mesh->translateMesh(glm::vec3(
			this->width / 2.0f - width / 2.0f - 0.001f,
			-this->height / 2.0f + atHeight + 0.001f,
			-this->length / 2.0f + at));
		break;
	case RIGHT:
		mesh->localRotateMesh(glm::radians(90.0f), glm::vec3(0, 1, 0));
		mesh->translateMesh(glm::vec3(
			-this->width / 2.0f + width / 2.0f + 0.001f,
			-this->height / 2.0f + atHeight + 0.001f,
			-this->length / 2.0f + at));
		break;
	case FRONT:
		mesh->localRotateMesh(glm::radians(180.0f), glm::vec3(0, 1, 0));
		mesh->translateMesh(glm::vec3(
			-this->width / 2.0f + at,
			-this->height / 2.0f + atHeight + 0.001f,
			this->length / 2.0f - width / 2.0f - 0.001f));
		break;
	case BACK:
		mesh->translateMesh(glm::vec3(
			-this->width / 2.0f + at,
			-this->height / 2.0f + atHeight + 0.001f,
			-this->length / 2.0f + width / 2.0f + 0.001f));
		break;
	}

	objects.push_back(mesh);
	objectManager.addMesh(mesh);
}

std::vector<glm::vec2> Room::getOpenings(WallSide side, float padding) {
	std::vector<glm::vec2> openings; //empty space on wall
	switch (side) {
	case LEFT:
		if (hasLeftOpening()) {
			openings.push_back(glm::vec2(padding, leftOpening.x - padding));
			openings.push_back(glm::vec2(leftOpening.y + padding, length - padding));
		}
		else {
			openings.push_back(glm::vec2(padding, length - padding));
		}
		break;
	case RIGHT:
		if (hasRightOpening()) {
			openings.push_back(glm::vec2(padding, rightOpening.x - padding));
			openings.push_back(glm::vec2(rightOpening.y + padding, length - padding));
		}
		else {
			openings.push_back(glm::vec2(padding, length - padding));
		}
		break;
	case FRONT:
		if (hasFrontOpening()) {
			openings.push_back(glm::vec2(padding, frontOpening.x - padding));
			openings.push_back(glm::vec2(frontOpening.y + padding, width - padding));
		}
		else {
			openings.push_back(glm::vec2(padding, width - padding));
		}
		break;
	case BACK:
		if (hasBackOpening()) {
			openings.push_back(glm::vec2(padding, backOpening.x - padding));
			openings.push_back(glm::vec2(backOpening.y + padding, width - padding));
		}
		else {
			openings.push_back(glm::vec2(padding, width - padding));
		}
		break;
	}

	return openings;
}