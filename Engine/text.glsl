#shader VERTEX
#version 330 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main(void)
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
} 

/* -------------------------------------------------------------------------- */
#shader FRAGMENT
#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main(void)
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = textColor * sampled;
} 