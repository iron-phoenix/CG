#version 150

uniform sampler2D texture_sampler;
varying vec2 v_texcoord;

float BSpline(float x, float a) {
    float f = abs(x);
    if(f >= 0.0 && f <= 1.0) {
        return (a + 2) * f * f * f - (a + 3) * f * f + 1;
    } else if(f > 1.0 && f <= 2.0) {
        return a * f * f * f - 5 * a * f * f + 8 * a * f - 4 * a;
    }
    return 0.0;
}

vec4 BiCubic(sampler2D texture_sampler, vec2 tex_coord) {
    float texel_width = 1.0 / 512;
    float texel_height = 1.0 / 512;
    vec4 sum = vec4(0.0);
    float a = fract(tex_coord.x * 512);
    float b = fract(tex_coord.y * 512);
    for(int m = -1; m <= 2; m++) {
        for(int n = -1; n <= 2; n++) {
            vec4 point = texture2D(texture_sampler, tex_coord + vec2(texel_width * float(m), texel_height * float(n)));
            float m1  = BSpline(float(m) - a, -0.5);
            float m2 = BSpline (-(float(n) - b), -0.5);
            sum = sum + point * vec4(m1) * vec4(m2);
        }
    }
    return sum;
}

void main(void) {
    gl_FragColor = BiCubic(texture_sampler, v_texcoord - vec2(1.0 / 1024, 1.0 / 1024));
}
