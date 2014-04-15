void main()
{
	gl_FrontColor = vec4(1,0,0,1); // red
	gl_BackColor = vec4(0,1,0,1); // green
	gl_Position = ftransform();
} 
