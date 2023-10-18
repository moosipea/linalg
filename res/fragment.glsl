#version 330 core
out vec4 FragColor;

in vec3 pos;

void main() {
    vec3 color = pos;
    FragColor = vec4(pos, 1.0f);
}