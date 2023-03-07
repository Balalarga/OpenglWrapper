#version 330

in vec2 vertUv;
in vec4 vertColor;
out vec4 fragColor;

uniform vec4 uColor;
uniform vec3 uCameraPos;
uniform sampler2D uTexture;

void main()
{
    fragColor = texture(uTexture, vertUv);
}