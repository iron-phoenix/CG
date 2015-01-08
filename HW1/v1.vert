#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
in vec3 vert;
out vec3 color;

void main(void) {
    gl_Position = projection * view * model * vec4(vert, 1.0);
    color = vec3(1.0, 1.0, 1.0);
}
