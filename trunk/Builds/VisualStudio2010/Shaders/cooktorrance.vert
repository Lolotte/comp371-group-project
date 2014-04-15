
uniform mat4 projection, modelview, normalMat;
uniform int mode;
varying vec4 forFragColor;

//const vec3 diffuseColor = vec3(0.5,0.0,0.0);

void main(){
	float specular = 0.0f;
	// set important material values
	vec3 lightColor = vec3(0.9,0.1,0.1);
    float roughnessValue = 0.3; // 0 : smooth, 1: rough
    float F0 = 0.8; // fresnel reflectance at normal incidence
    float k = 0.2; // fraction of diffuse reflection (specular reflection = 1 - k)
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	vec3 lightPos = vec3(0,0,0);

	// all following gemetric computations are performed in the
	// camera coordinate system (aka eye coordinates)
	vec3 N = vec3(gl_NormalMatrix * gl_Normal);
	vec4 vertPos4 = gl_ModelViewMatrix * gl_Vertex;
	vec3 vertPos = vec3(vertPos4);
	vec3 L = normalize(lightPos - vertPos);
	vec3 V = normalize(-vertPos);
	float mSquared = roughnessValue * roughnessValue;
	// half-vector
	vec3 H = normalize(N+V);
float NdotL = max(dot(N,L), 0.0);

if(NdotL > 0.0)
{
	float NdotH = max(dot(N,H), 0.0);
	float NdotV = max(dot(N,V), 0.0);
	
	float VdotH = max(dot(V,H), 0.0);
		
	// Geometric
	float g1 = 2.0 * NdotH;
	float g2 = (g1 * NdotV) / NdotH;
	float g3 = (g1 * NdotL) / NdotH;
	float G = min(1.0, min(g2,g3));
	
	
	// Roughness
	float r1 =  = 1.0 / (4.0 * mSquared * pow(NdotH, 4.0));
	float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
	float R = r1 * exp(r2);
	
	// Fresnel
    float F = pow(1.0 - VdotH, 5.0);
    F *= (1.0 - F0);
    F += F0;

	specular = (F * G * R) / (NdotV * NdotL);
	//  float lambertian = max(dot(lightDir,normal), 0.0);
	// diffuse = vec4(lambertian*diffuseColor , 1.0);
}
	vec3 value = lightColor * NdotL * (k + specular * (1.0 - k));
	forFragColor = vec4(value, 1.0); 
}


