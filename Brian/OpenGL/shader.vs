
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 vUv;
out vec3 vNormal;
out vec3 vPos;

void main()
{
	vUv = aUv;
    vNormal = (model * vec4(aNormal, 0.)).xyz;
    vPos = (model * vec4(aPos, 1.0)).xyz;
    mat4 mvpMatrix =  projection * view * model;
    gl_Position = mvpMatrix * vec4(aPos, 1.0);
}