#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;
layout(location = 2)in vec2 iVertUv;

uniform mat4 uModelMatrix = mat4(1);
uniform vec3 uCameraPos;

out vec4 vertColor;
out vec2 vertUv;

void main()
{
    gl_Position = uModelMatrix * vec4(iVert, 1.0);
    vertColor = iVertColor;
    vertUv = iVertUv;
}