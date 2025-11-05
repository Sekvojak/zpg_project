#version 330 core
in vec3 worldNorm;
in vec3 worldPos;    

out vec4 fragColor;

uniform vec3 viewPosition;
uniform vec3 objectColor; 


struct Light {
    vec3 position;
    vec3 color;
    vec3 direction; 
    float constant;
    float linear;
    float quadratic;

    float cutOff;
    int type;
    bool active;
};

struct Material {
    float ra;
    float rd;
    float rs;
    float h;
};

uniform Material material;


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

vec3 calcPointLight(Light light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 objColor) {
    vec3 lightDir = normalize(light.position - fragPos);
    
    // attenuation
    float distance = length(light.position - fragPos);
    float att = attenuation(distance, light.constant, light.linear, light.quadratic);

    // difuzna zlozka
    float diff = max(dot(normal, lightDir), 0.0);

    // spec zlozka
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.h);

    if (dot(normal, lightDir) < 0.0) {
        spec = 0.0;
    }

    vec3 diffuse = material.rd * diff * light.color * objColor;
    vec3 specular = material.rs * spec * light.color ;

    return (diffuse + specular) * att;
}

vec3 calcDirectionalLight(Light light, vec3 normal, vec3 viewDir, vec3 objColor) {
    vec3 lightDir = normalize(-light.direction); // smer k svetlu

    // difuzna zlozka
    float diff = max(dot(normal, lightDir), 0.0);

    // spec zlozka
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    if (dot(normal, lightDir) < 0.0) {
        spec = 0.0;
    }

    vec3 diffuse = material.rd * diff * light.color * objColor;
    vec3 specular = material.rs * spec * light.color * objColor; 

    return  (diffuse + specular);
}

vec3 calcSpotLight(Light light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 objColor) {
    vec3 lightToFrag = normalize(fragPos - light.position);    // smer ku fragmentu

    float LF = dot(lightToFrag, light.direction); // cos uhla medzi 

    // intenzita
    float intens = ( LF - light.cutOff )/( 1 - light.cutOff );
    intens = clamp(intens, 0.0, 1.0);

    // attenuation
    float distance = length(light.position - fragPos);

    float att = attenuation(distance, light.constant, light.linear, light.quadratic);

    // difuzna zlozka
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    // spec zlozka
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 diffuse = material.rd * diff * light.color * objColor;
    vec3 specular = material.rs * spec * light.color * objColor;

    return (diffuse + specular) * att * intens;

}

void main() {
    vec3 normal = normalize(worldNorm);
    vec3 viewDir = normalize(viewPosition - worldPos);

    vec3 result = vec3(0.0);


    for (int i = 0; i < lightCount; i++) {
        if (!lights[i].active) continue;

        if (lights[i].type == 0) {
            // POINT
            result += calcPointLight(lights[i], normal, viewDir, worldPos, objectColor);
        } else if (lights[i].type == 1) {
            // DIRECTIONAL
            result += calcDirectionalLight(lights[i], normal, viewDir, objectColor);
        } else if (lights[i].type == 2) {
            // SPOT
            result += calcSpotLight(lights[i], normal, viewDir, worldPos, objectColor);
        }
    }
    vec3 ambient = material.ra * objectColor;
    fragColor = vec4(result + ambient, 1.0);
}