#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
in vec3 vert;
out vec2 pos;

void main(void)
{
     pos = (vert).xy;
     gl_Position = projection * view * model * vec4(vert, 1.0);
}
