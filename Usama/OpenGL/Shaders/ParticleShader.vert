
	#version 330 core
	
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec2 aTC; 
	out vec2 TC;
	out vec4 ParticleColor;
	uniform vec4 color;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	void main()
    {
		vec3 cameraRightWS = vec3(view[0][0],view[1][0],view[2][0]);
		vec3 cameraUpWS= vec3(view[0][1],view[1][1],view[2][1]);
		vec3 particlePosition = vec3(model[0][3],model[1][3],model[2][3]);
		vec3 worldposition = particlePosition +  cameraRightWS * aPos.x +
		cameraUpWS * aPos.y;
		
		TC = aTC;
		ParticleColor = color;
		gl_Position = projection * view * model * vec4(worldposition, 1.0);
	
	}