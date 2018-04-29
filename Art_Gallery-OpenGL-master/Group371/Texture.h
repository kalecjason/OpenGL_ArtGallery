#ifndef TEXTURE_H
#define TEXTURE_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <string>
#include <vector>

enum TexturMapType {
	diffuseMap,
	normalMap,
	specularMap,
	heightMap
};

static std::string textureToUniform(std::string textureBasename, TexturMapType mapType) {
	std::string output = textureBasename;
	switch (mapType) {
		case diffuseMap: output.append("_d"); break;
		case normalMap: output.append("_n"); break;
		case specularMap: output.append("_s"); break;
		case heightMap: output.append("_h"); break;
		default: ;
	}
	return output;
}

struct TextureMap {
	TexturMapType mapType;
	GLuint mapId;
	std::string mapFilename;
};

struct DiffuseMap : public TextureMap {
	DiffuseMap() {mapType = diffuseMap;}
};

struct NormalMap : public TextureMap {
	NormalMap() { mapType = normalMap; }
};

struct SpecularMap: public TextureMap {
	SpecularMap() { mapType = specularMap; }
};

struct HeightMap :  public TextureMap {
	HeightMap() { mapType = heightMap; };
};

class Texture {
public:
	Texture() {
	}
	Texture(std::string diffuse, std::string normal, std::string specular, std::string heightMap) {
		diffuseMap.mapFilename = diffuse;
		normalMap.mapFilename = normal;
		specularMap.mapFilename = specular;
	}

	Texture(std::string dir, std::string baseFile, std::string ext) {
		diffuseMap.mapFilename = dir + baseFile + "_d" + "." + ext;
		normalMap.mapFilename = dir + baseFile + "_n" + "." + ext;
		specularMap.mapFilename = dir + baseFile + "_s" + "." + ext;
		heightMap.mapFilename = dir + baseFile + "_h" + "." + ext;
	}

	DiffuseMap diffuseMap;
	NormalMap normalMap;
	SpecularMap specularMap;
	HeightMap heightMap;
	int width;
	int height;
	glm::ivec2 uvWrap;
	int minFilter;
	int maxFilter;
	static std::vector<std::pair<std::string, Texture>> textures;
	static Texture getTexture(std::string name) {
		for (std::pair<std::string, Texture> t : textures) {
			if (name == t.first)
				return t.second;
		}
		return Texture();
	}
};

#endif
