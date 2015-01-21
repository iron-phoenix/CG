#version 330

in vec2 pos;
out vec3 color;

uniform float fscale;
uniform float xoffset;
uniform float yoffset;

void main() {
    vec2 c;
    vec2 z;
    c.x = (pos.x + xoffset) / fscale;
    c.y = (pos.y + yoffset) / fscale;
    z = c;
    int i;
    int iter = 1000;

    for(i = 0; i < iter; i++) {
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (z.y * z.x + z.x * z.y) + c.y;
        if((x * x + y * y) > 4.0) break;
        z.x = x;
        z.y = y;
    }

    color = vec3(float(i) / 300.0, float(i) / 300.0, float(i) / 50.0);
}
