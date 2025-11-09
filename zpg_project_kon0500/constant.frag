#version 330 core

in vec2 uv;
out vec4 fragColor;

uniform vec3 objectColor;
uniform bool hasTexture;
uniform sampler2D texture1;

void main() {
    vec3 baseColor = hasTexture ? texture(texture1, uv).rgb : objectColor;
    fragColor = vec4(baseColor, 1.0);
}
