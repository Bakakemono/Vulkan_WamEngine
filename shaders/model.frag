#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragLightColor;
layout(location = 3) in vec3 fragLightPos;
layout(location = 4) in float fragLightRange;
layout(location = 5) in vec3 fragPos;
layout(location = 6) in vec3 fragViewPos;
layout(location = 7) in float fragSpecularStrength;
layout(location = 8) in float fragSpecularDisp;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 N = normalize(fragNormal);
	vec3 lightDir = normalize(fragLightPos - fragPos);
	
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * vec3(0.0, 0.0, 1.0);
	
	float diff = max(dot(N, lightDir), 0.0);
	vec3 diffuse = diff * fragLightColor;
	
	vec3 viewDir = normalize(fragViewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, N);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256 / fragSpecularDisp);
	vec3 specular = fragSpecularStrength * spec * fragLightColor;
	
	vec3 lightResult = ambient + diffuse + specular;
    outColor = vec4(lightResult * texture(texSampler, fragTexCoord).rgb, 1.0);
}