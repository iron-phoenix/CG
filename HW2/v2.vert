#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 color;

in vec3 vertex;
in vec3 norm;

out vec4 pass_pos;
out vec4 pass_norm;
out vec4 pass_color;

void main(void) {
     gl_Position = projection * view * model * vec4(vertex, 1.0);
     pass_norm = projection * view * model * vec4(norm, 1.0);
     pass_color = vec4(color, 1.0);
     pass_pos = gl_Position;
}
