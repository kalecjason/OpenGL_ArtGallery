#ifndef VERTEX_H
#define VERTEX_H

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Material.h"

// A simple structure to hold our vertex
struct Vertex {

	glm::vec4 position;
	glm::vec3 normal;
	Material material;
	glm::vec2 uv;
	glm::ivec2 textureMeta;
	glm::ivec4 textureMaps;
	// Normal maps
	glm::vec3 tangent;
	glm::vec3 bitangent;
	// TODO depracate color to material
	glm::vec4 color;
	



	// TODO: refactor this, so that we dont have to call everything
	// Work in 4 dimensions for easier matrix multiplication
	// Default since we provided other ctors
	Vertex() {
		this->position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		this->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		this->normal = glm::vec3(0, 0, 0);
		this->uv = glm::vec2(0, 0);
		this->textureMaps = glm::ivec4(0, -1, -1, -1);
	}; 


	Vertex(glm::vec4 position) {
		this->position = position;
		this->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		this->normal = glm::vec3(0, 0, 0);
		this->uv = glm::vec2(0, 0);
		this->textureMaps = glm::ivec4(0, -1, -1, -1);
		
	};

	Vertex(glm::vec3 position) {
		this->position = glm::vec4(position, 1.0f);
		this->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		this->normal = glm::vec3(0, 0, 0);
		this->uv = glm::vec2(0, 0);
		this->textureMaps = glm::ivec4(0, -1, -1, -1);
	};

	Vertex(glm::vec4 position, glm::vec4 color) {
		this->position = position;
		this->color = color;
		this->normal = glm::vec3(0, 0, 0);
		this->uv = glm::vec2(0, 0);
		this->textureMaps = glm::ivec4(0, -1, -1, -1);
		
	};

	Vertex(glm::vec3 position, glm::vec3 color) {
		this->position = glm::vec4(position, 1.0);
		this->color = glm::vec4(color, 1.0f);
		this->normal = glm::vec3(0, 0, 0);
		this->uv = glm::vec2(0, 0);
		this->textureMaps = glm::ivec4(0, -1, -1, -1);
		
	};

	Vertex(glm::vec3 position, const Material& material) {
		this->position = glm::vec4(position, 1.0);
		this->material = material;
		this->normal = glm::vec3(0, 0, 0);
		this->uv = glm::vec2(0, 0);
		this->textureMaps = glm::ivec4(0, -1, -1, -1);
	};

	bool operator==(const Vertex& other) const {
		return position == other.position && color == other.color && normal == other.normal;
	}
	bool operator!=(const Vertex& other) const {
		return !(*this == other);
	}

};

#endif // !VERTEX_H