        #version 330 core
		in vec3 uv;
		in vec2 TC;
		out vec4 FragColor;
		uniform sampler2D texture1;
		uniform sampler2D texture2;
		void main()
		{
			FragColor = mix(texture(texture1, TC),texture(texture2, TC),0.5);//* vec4(uv, 1.0); 
		}