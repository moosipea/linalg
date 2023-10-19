#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

out vec3 pos;

void main() {
    pos = aPos;
    gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}