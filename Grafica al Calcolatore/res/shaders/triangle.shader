#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 vertexColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
	vertexColor = aColor;
}

#shader fragment
#version 330 core

in vec2 TexCoord;
in vec3 vertexColor;


out vec4 FragColor;

void main()
{
	FragColor = vec4(vertexColor, 1.0);
}