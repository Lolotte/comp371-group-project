uniform sampler2D texture;

void main() {
    // Set the output color of our current pixel
    gl_FragColor = texture2D(texture,gl_TexCoord[0].st);
}