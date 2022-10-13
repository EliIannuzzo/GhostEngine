#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(0.1, 0.1, 0.8, 1.0);
    //FragColor = vec4(0.1, 0.1, 0.8, 1.0);
}