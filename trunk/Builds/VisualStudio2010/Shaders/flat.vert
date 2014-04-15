void main(void)
{
	vec4 vertex = vec4(gl_Vertex);
	vertex.z = 0.0;		// Flatten the object on the Z-axis
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
} 