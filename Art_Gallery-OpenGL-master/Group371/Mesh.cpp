#include "Mesh.h"
#include "Texture.h"


Mesh::Mesh() {
	updateVerticesFromTransform();
}

Mesh::~Mesh() {
}

Mesh Mesh::copy() {
	Mesh copiedMesh;
	copiedMesh.vertices = vertices;
	copiedMesh.indices = indices;
	copiedMesh.indiceGroups = indiceGroups;
	copiedMesh.transform = transform;
	return copiedMesh;
}

void Mesh::addVertex(Vertex v) {
	vertices.push_back(v);	
	maxXYZ.x = glm::max(maxXYZ.x, v.position.x);
	maxXYZ.y = glm::max(maxXYZ.y, v.position.y);
	maxXYZ.z = glm::max(maxXYZ.z, v.position.z);

	minXYZ.x = glm::min(minXYZ.x, v.position.x);
	minXYZ.y = glm::min(minXYZ.y, v.position.y);
	minXYZ.z = glm::min(minXYZ.z, v.position.z);
	recalculateCenter();
}

void Mesh::addIndices(glm::ivec3 tri) {
	indices.push_back(tri.x);
	indices.push_back(tri.y);
	indices.push_back(tri.z);
	addIndiceGroup(tri);
}

void Mesh::addVertices(const std::vector<Vertex> vertices) {
	for (Vertex v : vertices) {
		addVertex(v);
	}
}

void Mesh::addIndices(const std::vector<int> indices) {
	for (int i = 0; i < indices.size(); i += 3) {
		addIndices(glm::vec3(indices.at(i), indices.at(i + 1), indices.at(i + 2)));
	}
}

void Mesh::setVertices(const std::vector<Vertex> vertices) {
	this->vertices.clear();
	addVertices(vertices);
}

void Mesh::setIndices(const std::vector<int> indices) {
	this->indices = indices;
	indiceGroups.clear();
	for (int i = 0; i < indices.size(); i += 3) {
		addIndiceGroup(glm::ivec3(indices.at(i), indices.at(i+1), indices.at(i+2)));
	}
}

void Mesh::setColor(glm::vec4 color) {
	// TODO: do we really need to make new vertices just to set the colors
	std::vector<Vertex> newVertices;
	for (std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		it->color = color;
		newVertices.push_back(*it);
	}
	vertices = newVertices;
}

void Mesh::setMaterial(const Material& material) {
	// TODO: do we really need to make new vertices just to set the materials
	std::vector<Vertex> newVertices;
	for (std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		it->material = material;
		it->textureMeta = { 0, 0 };
		it->textureMaps = { -1, -1, -1, -1 };
		newVertices.push_back(*it);
	}
	vertices = newVertices;

}

void Mesh::setTexture(Texture texture, float repeatX, float repeatY) {
	this->texture = texture;
	for (std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		// Enable textures for this vertex
		it->textureMeta = { 1, 0 };
		it->textureMaps = { texture.diffuseMap.mapId, texture.normalMap.mapId, texture.specularMap.mapId, texture.heightMap.mapId };
		it->uv.x *= repeatX;
		it->uv.y *= repeatX;
	}
}

void Mesh::mix(Material material, Texture texture, float repeatX, float repeatY, int mix) {
	this->texture = texture;
	for (std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		// Enable textures for this vertex
		it->textureMeta = { 2, mix };
		it->material = material;
		it->textureMaps = { texture.diffuseMap.mapId, texture.normalMap.mapId, texture.specularMap.mapId, texture.heightMap.mapId };
		it->uv.x *= repeatX;
		it->uv.y *= repeatX;
	}
}


int Mesh::vertexBufferSize() {
	return vertices.size() * sizeof(Vertex);
}

int Mesh::indexBufferSize() {
	return indices.size() * sizeof(int);
}

void Mesh::reset() {
	vertices.clear();
	indices.clear();
}

void Mesh::scaleMesh(glm::vec3 scale) {
	transform = glm::scale(transform, scale);
	updateVerticesFromTransform();
}

void Mesh::localScaleMesh(glm::vec3 scale) {
	glm::mat4 scaleMatrix;
	// Rotates around center of bounding box
	glm::vec4 vecToOrigin = center - glm::vec4(0, 0, 0, 0);
	scaleMatrix = glm::translate(scaleMatrix, glm::vec3(vecToOrigin));
	scaleMatrix = glm::scale(scaleMatrix, scale);
	scaleMatrix = glm::translate(scaleMatrix, -glm::vec3(vecToOrigin));
	transform = scaleMatrix * transform;
	updateVerticesFromTransform();
	
}

void Mesh::rotateMesh(float radians, glm::vec3 rotate) {
	transform = glm::rotate(transform, radians, rotate);
	updateVerticesFromTransform();
}

void Mesh::localRotateMesh(float radians, glm::vec3 rotate) {
	glm::mat4 rotationMatrix;
	// Rotates around center of bounding box
	glm::vec4 vecToOrigin = center - glm::vec4(0, 0, 0, 0);
	rotationMatrix = glm::translate(rotationMatrix, glm::vec3(vecToOrigin));
	rotationMatrix = glm::rotate(rotationMatrix, radians, rotate);
	rotationMatrix = glm::translate(rotationMatrix, -glm::vec3(vecToOrigin));
	transform = rotationMatrix * transform;
	updateVerticesFromTransform();
}

void Mesh::translateMesh(glm::vec3 translate) {
	transform = glm::translate(transform, translate);
	updateVerticesFromTransform();
}

void Mesh::updateVerticesFromTransform() {
	maxXYZ = glm::vec4(-FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX);
	minXYZ = glm::vec4(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);

	for (Vertex& v : vertices) {
		v.position = transform * v.position;
		maxXYZ.x = glm::max(maxXYZ.x, v.position.x);
		maxXYZ.y = glm::max(maxXYZ.y, v.position.y);
		maxXYZ.z = glm::max(maxXYZ.z, v.position.z);

		minXYZ.x = glm::min(minXYZ.x, v.position.x);
		minXYZ.y = glm::min(minXYZ.y, v.position.y);
		minXYZ.z = glm::min(minXYZ.z, v.position.z);
	}
	recalculateCenter();
	recalculateNormals();
	transform = glm::mat4();
}

void Mesh::recalculateCenter() {
	// Gets center of bounding box
	center = glm::vec4((maxXYZ.x + minXYZ.x) / 2.0,
		(maxXYZ.y + minXYZ.y) / 2.0,
		(maxXYZ.z + minXYZ.z) / 2.0
		, 0
	);
}

void Mesh::recalculateNormals() {
	for (int i = 0; i < indiceGroups.size(); i++) {
		glm::ivec3 tri = indiceGroups.at(i);
		// TODO: make this inline for performance
		calculateTangentsAndBitTangents(tri);
		Vertex& v1 = vertices.at(tri.x);
		Vertex& v2 = vertices.at(tri.y);
		Vertex& v3 = vertices.at(tri.z);

		glm::vec3 d1 = v1.position - v2.position;
		glm::vec3 d2 = v1.position - v3.position;
		glm::vec3 normal = glm::normalize(glm::vec3(glm::vec4(glm::cross(d1, d2), 1.0)));
		v1.normal = normal;
		v2.normal = normal;
		v3.normal = normal;
	}
}

bool Mesh::operator==(const Mesh& other) const {
	return vertices == other.vertices && indices == other.indices;
}

bool Mesh::operator!=(const Mesh& other) const {
	return !(*this == other);
}

void Mesh::addIndiceGroup(glm::ivec3 tri) {
	indiceGroups.push_back(tri);

	Vertex& v1 = vertices.at(tri.x);
	Vertex& v2 = vertices.at(tri.y);
	Vertex& v3 = vertices.at(tri.z);

	glm::vec3 d1 = v1.position - v2.position;
	glm::vec3 d2 = v1.position - v3.position;
	glm::vec3 normal = glm::normalize(glm::cross(d1, d2));
	v1.normal = normal;
	v2.normal = normal;
	v3.normal = normal;

	calculateTangentsAndBitTangents(tri);
}

void Mesh::calculateTangentsAndBitTangents(glm::ivec3 tri) {
	Vertex& v1 = vertices.at(tri.x);
	Vertex& v2 = vertices.at(tri.y);
	Vertex& v3 = vertices.at(tri.z);

	glm::vec3 e1 = v2.position - v1.position;
	glm::vec3 e2 = v3.position - v1.position;
	glm::vec2 deltaUV1 = v2.uv - v1.uv;
	glm::vec2 deltaUV2 = v3.uv - v1.uv;

	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	glm::vec3 tangent;
	glm::vec3 bitangent;

	tangent.x = f * (deltaUV2.y * e1.x - deltaUV1.y * e2.x);
	tangent.y = f * (deltaUV2.y * e1.y - deltaUV1.y * e2.y);
	tangent.z = f * (deltaUV2.y * e1.z - deltaUV1.y * e2.z);
	tangent = glm::normalize(tangent);

	bitangent.x = f * (-deltaUV2.x * e1.x + deltaUV1.x * e2.x);
	bitangent.y = f * (-deltaUV2.x * e1.y + deltaUV1.x * e2.y);
	bitangent.z = f * (-deltaUV2.x * e1.z + deltaUV1.x * e2.z);
	bitangent = glm::normalize(bitangent);

	v1.tangent = tangent;
	v2.tangent = tangent;
	v3.tangent = tangent;

	v1.bitangent = bitangent;
	v2.bitangent = bitangent;
	v3.bitangent = bitangent;
	
	
}



GridMesh::GridMesh() {
	// Size should be a power of 2
	int size = 512;
	// TODO: figure out if size should be a power of 2 for faster generation
	float divSize = 1;

	// Generate vertices
	for (int i = -(size / 2); i <= (size / 2); i++) {
		for (int j = -(size / 2); j <= (size / 2); j++) {
			
			Vertex v(glm::vec3(i * divSize, 0, j * divSize));
			v.material.ambient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			vertices.push_back(v);
		}
	}

	for (int i = 0; i < vertices.size(); i++) {
		
			if (i == 0 || i % (size + 1) != size) {
				indices.push_back(i);
				indices.push_back(i + 1);
			}

			if (i < (size * size) + size) {
				indices.push_back(i);
				indices.push_back(i + size + 1);
			}
	}



}

GridMesh::~GridMesh() {}

XYZAxis::XYZAxis() {

	

	// x is red
	Vertex xOrigin(glm::vec3(0, 0, 0));
	Vertex xAxis(glm::vec3(10, 0, 0));
	xOrigin.material.ambient = xAxis.material.ambient = RED;
	

	// y is green
	Vertex yOrigin(glm::vec3(0, 0, 0));
	Vertex yAxis(glm::vec3(0, 10, 0));
	yOrigin.material.ambient = yAxis.material.ambient = GREEN;

	// z is blue
	Vertex zOrigin(glm::vec3(0, 0, 0));
	Vertex zAxis(glm::vec3(0, 0, 10));
	zOrigin.material.ambient = zAxis.material.ambient = BLUE;

	int top = 0;
	vertices.push_back(xOrigin);
	vertices.push_back(xAxis);
	indices.push_back(top++);
	indices.push_back(top++);

	vertices.push_back(yOrigin);
	vertices.push_back(yAxis);
	indices.push_back(top++);
	indices.push_back(top++);

	vertices.push_back(zOrigin);
	vertices.push_back(zAxis);
	indices.push_back(top++);
	indices.push_back(top++);
}


XYZAxis::~XYZAxis() {
}