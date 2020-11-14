
#version 330 core

in vec2 uv;
in vec3 normal;

out vec4 FragColor;

void main()
{
    vec3 color = vec3(dot(normal, vec3(0., 1., 0.)));
    FragColor = vec4(color, 1.0f);
} 