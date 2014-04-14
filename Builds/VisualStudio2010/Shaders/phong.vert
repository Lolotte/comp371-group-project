uniform mat4 projection, modelview, normalMat;
uniform int mode;

varying vec4 forFragColor;
const vec3 diffuseColor = vec3(0.5, 0.0, 0.0);
const vec3 specularColor = vec3(1, 1, 1);
const float shininess = 200;

void main(){
 gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
 vec3 lightPos = vec3(0,0,0);

  // all following gemetric computations are performed in the
  // camera coordinate system (aka eye coordinates)
  vec3 normal = vec3(gl_NormalMatrix * gl_Normal);
  vec4 vertPos4 = gl_ModelViewMatrix * gl_Vertex;
  vec3 vertPos = vec3(vertPos4);
  vec3 lightDir = normalize(lightPos - vertPos);

  float lambertian = max(dot(lightDir,normal), 0.0);
  vec3 L = lightDir;
  vec3 E = normalize(-vertPos);
  vec3 R = normalize(reflect(-L, normalize(normal)));	
  vec3 Ispec =  specularColor * pow(max(dot(R, E), 0.0), 0.3 * shininess);
  Ispec = clamp(Ispec, 0.0, 1.0);
// forFragColor = vec4(lambertian*diffuseColor , 1.0);
 forFragColor = vec4(lambertian*diffuseColor + Ispec, 1.0);
}
