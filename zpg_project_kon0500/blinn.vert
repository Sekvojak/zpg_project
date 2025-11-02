#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
            
out vec3 worldPos;
out vec3 worldNorm;            

void main() {
    vec4 worldPosition = modelMatrix * vec4(position, 1.0);
    worldPos = worldPosition.xyz / worldPosition.w;

    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNorm = normalize(normalMatrix * normal);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}