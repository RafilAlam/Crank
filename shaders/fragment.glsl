#version 450 core

#define M_MODEL 0
#define M_RECT  1
#define M_TRI   2
#define M_CIR   3

in vec4 gl_FragCoord;

out vec4 FragColor;

uniform vec2 u_modelposition;
uniform vec3 u_color;
uniform int u_meshtype;
uniform vec2 u_resolution;
uniform float u_circleradius;

void main()
{
  switch(u_meshtype) {
    case M_CIR:
      float dist = distance(u_modelposition, gl_FragCoord.xy);
      if (dist > u_circleradius) {
        discard;
      }
      else {
        FragColor = vec4(u_color, 1.0f);
      }
      break;
    default:
      FragColor = vec4(u_color, 1.0f);
  }
}
