#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 m_ambient;
layout (location = 3) in vec3 m_diffuse;
layout (location = 4) in vec3 m_specular;
layout (location = 5) in float m_shininess;
layout (location = 6) in vec2 uv;
layout (location = 7) in ivec2 textureMeta;
layout (location = 8) in ivec4 textureID;
layout (location = 9) in vec3 tangent;
layout (location = 10) in vec3 bitangent;

// Position, normals, textures
out vec4 frag_position;
out vec3 frag_normal;
out vec2 frag_textureUV;

// Texture ids for this vertex
flat out ivec2 frag_textureMeta;
flat out ivec4 frag_textureID;

// Material outs 
out vec3  frag_ambient;
out vec3  frag_diffuse;
out vec3  frag_specular;
out float frag_shininess;

// tangent space matrix
out mat3 TBN;

 
uniform mat4 transform;
uniform mat4 model;



void main(){
	gl_Position = transform * position;
	frag_position = model * position;
	frag_normal = normal;
	//frag_textureCoord = vec2(uv.x, 1.0 - uv.y);
	frag_textureUV = uv;
	frag_textureMeta = textureMeta;
	frag_textureID = textureID;

	frag_ambient = m_ambient;
	frag_diffuse = m_diffuse;
	frag_specular = m_specular;
	frag_shininess = m_shininess;

	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);    

	TBN = transpose(mat3(T, B, N));  
    
}
