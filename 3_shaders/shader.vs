#version 330 core

layout (location = 0) in vec3 position;

out vec4 vertexColor;

uniform float offsetX;

void main()
{
	gl_Position = vec4(position.x + offsetX, -position.y, position.z, 1.0);

	vertexColor = vec4(position.x + offsetX, position.y, position.z, 1.0f);
}