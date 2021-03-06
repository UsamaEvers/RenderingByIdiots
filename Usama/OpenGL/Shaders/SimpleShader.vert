
	#version 330 core
	layout (location = 1) in vec3 aUV;
	layout (location = 0) in vec3 aPos;
	layout (location = 2) in vec2 aTC; 
	out vec3 uv;
	out vec2 TC;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	void main()
    {
		uv = aUV;
		gl_Position = projection * view * model * vec4(aPos, 1.0);
		TC = aTC;
	}