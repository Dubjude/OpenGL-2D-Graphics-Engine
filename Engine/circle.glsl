#shader VERTEX
#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aRadius;
layout (location = 2) in vec3 aCenter;
layout (location = 3) in vec4 aColor;

out vec2 fragPos;
out vec2 center;
out vec4 fragColor;
out float radius;
out float radiusRatio;
out float innerRadius;
out float ratio;

void main(void)
{
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	fragPos = aPos;
	fragColor = aColor;
	center = aCenter.xy;
	radius = aRadius.x;
	radiusRatio = aRadius.z;
	innerRadius = aRadius.y;
	ratio = aCenter.z;
}

/* ------------------------------------------------------------------------- */
#shader FRAGMENT
#version 330 core

in vec2 fragPos;
in vec4 fragColor;
in vec2 center;
in float radius;
in float radiusRatio;
in float innerRadius;
in float ratio;

out vec4 CircleColor;

void main(void)
{
	float outFade = 0.005;
	float inFade = outFade / 3.0;
	vec2 pos = vec2(center.x - fragPos.x, center.y - fragPos.y);
	float dist = (radius * radius) - (pos.x*pos.x + (pos.y*pos.y * (ratio*ratio) / (radiusRatio*radiusRatio)));
	float alpha = smoothstep(0.0, outFade * radius, dist);
	alpha *= smoothstep(innerRadius + inFade, innerRadius, dist);
	CircleColor = vec4(fragColor.rgb, alpha * fragColor.a);
}