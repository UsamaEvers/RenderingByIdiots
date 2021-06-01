#version 330 core

in vec2 vUv;
in vec3 vNormal;
in vec3 vPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vUv, 0., 1.);
} 