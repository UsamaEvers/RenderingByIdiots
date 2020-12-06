
	#version 330 core
	layout (location = 1) in vec3 aUV;
	layout (location = 0) in vec3 aPos;
	layout (location = 2) in vec2 aTC; 
	out vec3 uv;
	out vec2 TC;
	
	void main()
    {
		uv = aUV;
	   gl_Position = vec4(aPos, 1.0);
		TC = aTC;
	}