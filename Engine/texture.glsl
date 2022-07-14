#shader VERTEX
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColor;
layout (location = 3) in float aTexID;

out vec2 fragPos;
out vec2 texCoord;
out vec4 fragColor;
out float texID;

void main(void)
{
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	fragPos = aPos;
	texCoord = aTexCoord;
	fragColor = aColor;
	texID = aTexID;
}

/* -------------------------------------------------------------------------- */
#shader FRAGMENT
#version 330 core

in vec2 fragPos;
in vec2 texCoord;
in vec4 fragColor;
in float texID;

out vec4 FinalColor;

uniform sampler2D uTexture[32];

void main(void)
{
	FinalColor = texture(uTexture[int(texID)], texCoord) * fragColor;
}

