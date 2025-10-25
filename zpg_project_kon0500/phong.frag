#version 330 core
in vec3 worldNorm;
in vec3 worldPos;    

out vec4 fragColor;

uniform vec3 viewPosition;
uniform vec3 objectColor; 


struct Light {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

uniform int lightCount;
uniform Light lights[20];

float attenuation ( float d , float c , float l , float q )
{
    // d = distance from the light to the fragment
    // c = constant attenuation factor
    // l = linear attenuation factor
    // q = quadratic attenuation factor
    float att = 1.0 / ( c + l * d + q * d * d );
    return clamp ( att , 0.0 , 1.0);
}


void main() {
    vec3 normal = normalize(worldNorm);
    vec3 viewDir = normalize(viewPosition - worldPos);

    vec3 result = vec3(0.0);

    vec3 ambient = vec3(0.1, 0.1, 0.1) * objectColor;

    for (int i = 0; i < lightCount; i++) {
        vec3 lightDir = normalize(lights[i].position - worldPos);

        // attenuation
        float distance = length(lights[i].position - worldPos);
        float att = attenuation(distance, lights[i].constant, lights[i].linear, lights[i].quadratic);


        // difuzna zlozka
        float diff = max(dot(normal, lightDir), 0.0);
        
        // spec zlozka
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0 ), 32);

        if (dot(normal, lightDir) < 0.0) {
            spec = 0.0;
        }
       
        vec3 diffuse = diff * lights[i].color * objectColor * att;
        vec3 specular = spec * lights[i].color * objectColor * att;

        result += (diffuse + specular);
    }

    fragColor = vec4(result + ambient, 1.0);
}