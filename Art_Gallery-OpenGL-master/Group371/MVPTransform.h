#ifndef MVP_TRANSFORM_H
#define MVP_TRANSFORM_H


#include <glm/glm.hpp>

// Simple container to hold our model,view,projection matrices
struct MVPTransform {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 getTransform() {
		return projection * view * model;
	};
};
#endif // !MVP_TRANSFORM_H