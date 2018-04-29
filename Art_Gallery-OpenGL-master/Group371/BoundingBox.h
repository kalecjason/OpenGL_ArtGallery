#pragma once

// glm
#include <glm/glm.hpp>

struct BoundingBox
{
	glm::vec3 max;
	glm::vec3 min;

	bool operator==(const BoundingBox& o) const {
		return max == o.max && min == o.min;
	};

	bool operator!=(const BoundingBox& o) const {
		return !(*this == o);
	}
};

