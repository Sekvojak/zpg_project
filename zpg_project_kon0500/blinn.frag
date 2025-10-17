#version 330 core
in vec3 worldNorm;
in vec3 worldPos;    
            
out vec4 fragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform vec3 objectColor; 

void main() {
    vec3 normal = normalize(worldNorm);
    vec3 lightDir = normalize(lightPosition - worldPos);
    vec3 viewDir = normalize(viewPosition - worldPos);
    vec3 halfwayDir = normalize ( lightDir + viewDir );


    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(normal, halfwayDir), 0.0 ), 32);

    vec3 ambient = 0.1 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 specular = spec * lightColor;

                
    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0);
}