#version 330

in vec2 in_pos;

out vec2 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    pos = in_pos;
    gl_Position = projection * view * model * vec4(in_pos, 0, 1);
}
