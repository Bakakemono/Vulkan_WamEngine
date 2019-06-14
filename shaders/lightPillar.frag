#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragLightColor;
layout(location = 3) in vec3 fragLightPos;
layout(location = 4) in float fragLightRange;
layout(location = 5) in vec3 fragPos;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 N = normalize(fragNormal);
	vec3 LDir = normalize(fragLightPos - fragPos);
	float LDist = pow(pow(LDir.x, 2) + pow(LDir.y, 2) + pow(LDir.z, 2), 1.0f / 3.0f);
	float R = dot(N, LDir);
	vec3 light;
	if(R > 0)
	{
		if(LDist < fragLightRange)
		{
			light = R *((fragLightRange / LDist) / fragLightRange) * fragLightColor;
		}
	}
	else
	{
		light = -R * vec3(0.0f, 0.0f, 0.0f);
	}
    outColor = vec4(light * texture(texSampler, fragTexCoord).rgb, 1.0);
}