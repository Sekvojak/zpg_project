#version 330 core

in vec2 uv;
out vec4 fragColor;

uniform vec3 objectColor;
uniform bool hasTexture;
uniform sampler2D texture1;
uniform int isSelected;

void main() {
    vec3 baseColor = hasTexture ? texture(texture1, uv).rgb : objectColor;

    if (isSelected == 1) {
        baseColor = mix(baseColor, vec3(1.0, 0.2, 0.2), 0.25);
        baseColor *= 1.2;
    }
    fragColor = vec4(baseColor, 1.0);
}
