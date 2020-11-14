
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;
out vec3 normal;

void main()
{
    normal = aNormal;
	uv = aUv;
    mat4 mvpMatrix =  projection * view * model;
    gl_Position = mvpMatrix * vec4(aPos, 1.0);
}