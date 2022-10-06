#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
out vec2 pos;
uniform mat4 u_MVP;

void main() 
{
	pos = position;
	gl_Position = u_MVP * vec4(pos, -1.0f, 1.0f);
};

#shader fragment
#version 330 core

in vec2 pos;
out vec4 fragColor;
uniform vec4 u_Color;

void main() 
{
	fragColor = vec4(pos.x / 1080.0f, pos.y / 1080.0f, 1.0f - ((pos.x + pos.y) / (2 * 1080.0f)),1.0f);
};
