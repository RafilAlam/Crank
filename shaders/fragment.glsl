#version 450 core

#define M_MODEL 0
#define M_RECT  1
#define M_TRI   2
#define M_CIR   3

in vec4 gl_FragCoord;

out vec4 FragColor;

uniform vec2 u_modelposition;
uniform int u_meshtype;
uniform vec2 u_resolution;
uniform float u_circleradius;

void main()
{
  switch(u_meshtype) {
    case M_CIR:
      vec2 ndc = (gl_FragCoord.xy / u_resolution) * 2.0 - 1.0;
      float dist = distance(u_modelposition, ndc);
      if (u_circleradius <= dist) {
        discard;
      }
      else {
        FragColor = vec4(0.2f, 0.5f, 0.2f, 1.0f);
      }
      break;
    default:
      FragColor = vec4(0.2f, 0.5f, 0.2f, 1.0f);
  }
}
