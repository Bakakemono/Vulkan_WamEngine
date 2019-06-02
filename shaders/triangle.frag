#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragLightColor;
layout(location = 3) in vec3 fragNormal;
layout(location = 4) in vec3 fragLightDir;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 N = normalize(fragNormal);
	vec3 LDir = normalize(fragLightDir);
	vec3 light = max(dot(N, LDir), 0.0) * vec3(1.0);
    outColor = vec4(light * texture(texSampler, fragTexCoord).rgb, 1.0);
}