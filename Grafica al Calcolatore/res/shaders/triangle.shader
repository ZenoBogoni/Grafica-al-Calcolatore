#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}

#shader fragment
#version 330 core

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 myColor;

out vec4 FragColor;

void main()
{
	FragColor = texture(ourTexture, TexCoord);
}