#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat shininess;
};

#endif
