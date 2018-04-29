#version 330 core


layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 m_ambient;
layout (location = 3) in vec3 m_diffuse;
layout (location = 4) in vec3 m_specular;
layout (location = 5) in float m_shininess;


out vec4 vertexColor;
uniform mat4 transform;

void main()
{
    gl_Position = transform * position;
    vertexColor = vec4(m_ambient, 1.0);
} 