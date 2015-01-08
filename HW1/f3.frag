#version 150

out vec4 color;
in vec2 pos;

void main(void) {
      vec2 position = pos / 0.07;
      if((fract(position.x) < 0.5 && fract(position.y) < 0.5) ||
         (fract(position.x) > 0.5 && fract(position.y) > 0.5)){
        color = vec4(0,0,0,1.0);
      } else{
        color = vec4(1,1,1,1.0);
      }
}
