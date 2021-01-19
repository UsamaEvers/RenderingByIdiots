        #version 330 core
		in vec2 TC;
		in vec4 ParticleColor;
		out vec4 FragColor;

		uniform sampler2D texture1;
		uniform sampler2D texture2;
		uniform sampler2D texture3;

		void main()
		{

			FragColor = mix(texture(texture3, TC),	 mix(texture(texture1, TC), texture(texture2, TC), 0.5),0.5 )*ParticleColor;
		}
