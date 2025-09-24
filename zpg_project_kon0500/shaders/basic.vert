#version 330
layout(location=0) in vec4 vp;
layout(location=1) in vec4 vc;
out vec4 vColor;

uniform float aspect;

void main() {
    gl_Position = vec4(vp.x / aspect, vp.y, vp.z, vp.w);
    vColor = vc;
}
