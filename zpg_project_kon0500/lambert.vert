#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
            
out vec3 worldPos;
out vec3 worldNorm;            

void main() {
    worldNorm = normal;
    worldPos = vec3(modelMatrix * vec4(position, 1.0)); 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}