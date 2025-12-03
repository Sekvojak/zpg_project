#version 330 core
in vec3 worldNorm;
in vec3 worldPos;    

in vec2 uv;  

out vec4 fragColor;

uniform vec3 viewPosition;
uniform vec3 objectColor; 
uniform bool hasTexture;
uniform sampler2D texture1;

uniform int isSelected;

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

    float intensity;
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

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.h);

    if (dot(normal, lightDir) < 0.0) {
        spec = 0.0;
    }

    vec3 diffuse = material.rd * diff * light.color * objColor * light.intensity;
    vec3 specular = material.rs * spec * light.color * light.intensity;

    return (diffuse + specular) * att;
}

vec3 calcDirectionalLight(Light light, vec3 normal, vec3 viewDir, vec3 objColor) {
    vec3 lightDir = normalize(-light.direction); // vector from fragment to light

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    if (dot(normal, lightDir) < 0.0) {
        spec = 0.0;
    }

    vec3 diffuse = material.rd * diff * light.color * objColor * light.intensity;
    vec3 specular = material.rs * spec * light.color * light.intensity; 

    return  (diffuse + specular);
}

vec3 calcSpotLight(Light light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 objColor) {
    vec3 lightToFrag = normalize(fragPos - light.position);    

    float LF = dot(lightToFrag, light.direction); 

    float intens = ( LF - light.cutOff )/( 1 - light.cutOff );
    intens = clamp(intens, 0.0, 1.0);

    float distance = length(light.position - fragPos);

    float att = attenuation(distance, light.constant, light.linear, light.quadratic);

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 diffuse = material.rd * diff * light.color * objColor * light.intensity;
    vec3 specular = material.rs * spec * light.color * light.intensity;

    return (diffuse + specular) * att * intens;

}

void main() {
    vec3 normal = normalize(worldNorm);
    vec3 viewDir = normalize(viewPosition - worldPos);

    vec3 result = vec3(0.0);

    vec3 baseColor = hasTexture ? texture(texture1, uv).rgb : objectColor;

    for (int i = 0; i < lightCount; i++) {
        if (!lights[i].active) continue;

        if (lights[i].type == 0) {
            // POINT
            result += calcPointLight(lights[i], normal, viewDir, worldPos, baseColor);
        } else if (lights[i].type == 1) {
            // DIRECTIONAL
            result += calcDirectionalLight(lights[i], normal, viewDir, baseColor);
        } else if (lights[i].type == 2) {
            // SPOT
            result += calcSpotLight(lights[i], normal, viewDir, worldPos, baseColor);
        }
    }
    vec3 ambient = material.ra * baseColor;
    
    vec3 finalColor = result + ambient;
    if (isSelected == 1) {
        finalColor = mix(finalColor, vec3(1.0, 0.2, 0.2), 0.25);
        finalColor *= 1.2;
    }
    
    fragColor = vec4(finalColor, 1.0);
}