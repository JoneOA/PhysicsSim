#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
uniform vec3 u_Pos;

void main() 
{
	gl_Position = vec4(position + u_Pos, 1.0f);
};

#shader fragment
#version 330 core

uniform vec4 u_Color;
out vec4 color;

void main() 
{
	color = u_Color;
};