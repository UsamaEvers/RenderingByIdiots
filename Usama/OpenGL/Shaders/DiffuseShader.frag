        #version 330 core
		in vec3 FragPos;  
		in vec3 Normal;
		out vec4 FragColor;
		//uniform sampler2D texture1;
		//uniform sampler2D texture2;
		uniform vec3 viewPos; 
		uniform vec3 color;
		uniform vec3 lightPos;

		void main()
		{
			float ambientStrength = 0.1;
   			vec3 ambient = ambientStrength * color;
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(lightPos - FragPos);  
			float diff = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = diff * color;
			float specularStrength = 0.5;
    		vec3 viewDir = normalize(viewPos - FragPos);
    		vec3 reflectDir = reflect(-lightDir, norm);  
   	 		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 	64);
   	 		vec3 specular = specularStrength * spec * color;  
			vec3 result = (ambient + diffuse + specular)* vec3(1.0,0,0);//* mix(texture(texture1, TC),texture(texture2, TC),0.5);
			FragColor = vec4(result, 1.0);//* vec4(uv, 1.0); 
		}
