#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

#shader fragment
#version 330 core

uniform vec4 myColor;
out vec4 FragColor;

void main()
{
	FragColor = myColor;
}