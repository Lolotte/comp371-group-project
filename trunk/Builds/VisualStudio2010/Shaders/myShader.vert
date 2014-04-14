varying vec3 normal, lightDir;
varying vec4 forFragColor;

void main()
{	
	float intensity;
	vec4 color;

	vec4 vertPos4 = gl_ModelViewMatrix * gl_Vertex;
	vec3 vertPos = vec3(vertPos4);
	
	vec3 lightPos = vec3(0,0,0);
	
	lightDir = normalize(lightPos - vertPos);

	normal = normalize(gl_NormalMatrix * gl_Normal);

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	intensity = dot(lightDir, normal);
	
	if (intensity > 0.95)
		color = vec4(1.0,0.5,0.5,1.0);
	else if (intensity > 0.5)
		color = vec4(0.6,0.3,0.3,1.0);
	else if (intensity > 0.25)
		color = vec4(0.4,0.2,0.2,1.0);
	else
		color = vec4(0.2,0.1,0.1,1.0);

	forFragColor = color;
}
