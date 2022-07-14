#shader VERTEX
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

out vec2 fragPos;
out vec4 fragColor;

void main(void)
{
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	fragPos = aPos;
	fragColor = aColor;
}

/* -------------------------------------------------------------------------- */
#shader FRAGMENT
#version 330 core

in vec2 fragPos;
in vec4 fragColor;

out vec4 FinalColor;

void main(void)
{
	FinalColor = fragColor;
}
	
