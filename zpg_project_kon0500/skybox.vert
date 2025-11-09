#version 330 core
layout(location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentLocalPosition;

void main() {
    mat4 viewNoTranslate = mat4(mat3(viewMatrix));
    gl_Position = projectionMatrix * viewNoTranslate * vec4(vp, 1.0);
    fragmentLocalPosition = vp;
}
