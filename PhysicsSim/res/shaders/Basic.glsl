#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
uniform vec3 u_Pos;

uniform mat4 u_MVP;

void main() 
{
	gl_Position = vec4(position, 1.0f) * u_MVP;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;
uniform vec4 u_Color;

void main() 
{
	fragColor = u_Color;
};
