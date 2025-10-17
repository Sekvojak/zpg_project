#version 330 core
in vec3 worldNorm;
in vec3 worldPos;    
            
out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 objectColor; 

void main() {
    vec3 N = normalize(worldNorm);
    vec3 L = normalize(lightPosition - worldPos);

    float diff = max(dot(N, L), 0.0);

    vec3 ambient = 0.1 * lightColor;
                
    vec3 result = (ambient + diff * lightColor) * objectColor;
    fragColor = vec4(result, 1.0);
}