#version 330 core

uniform vec3 objectColor; 


out vec4 fragColor;
in vec4 pos;
void main() {
    fragColor = vec4(objectColor, 1.0);
}