#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
      
out vec2 uv;      
out vec3 worldPos;
out vec3 worldNorm;            

void main() {
    vec4 worldPosition = modelMatrix * vec4(position * 200, 200.0);
    worldPos = worldPosition.xyz / worldPosition.w;
    
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNorm = normalize(normalMatrix * normal);

    uv = texCoord;
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}