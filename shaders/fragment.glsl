#version 450 core

#define M_MODEL 0
#define M_RECT  1
#define M_TRI   2
#define M_CIR   3

in vec4 gl_FragCoord;

out vec4 FragColor;

uniform vec2 u_modelposition;
uniform vec2 u_modelsize;
uniform float u_roundness;
uniform vec4 u_bgcolor;
uniform vec3 u_bordercolor;
uniform float u_borderwidth;
uniform int u_meshtype;
uniform vec2 u_resolution;

float sdfRect(vec2 point, vec2 halfsize) 
{
  vec2 q = abs(point) - halfsize;
  return length(max(q, 0.0f)) + min(max(q.x, q.y), 0.0);
}

void main()
{
  switch(u_meshtype) {
    case M_RECT:
      vec2 halfsize = u_modelsize*0.5;
      float cornerradius = u_roundness * min(halfsize.x, halfsize.y);
      float d = sdfRect(gl_FragCoord.xy - u_modelposition, halfsize - cornerradius) - cornerradius;

      float fill = smoothstep(1.0, -1.0, d + u_borderwidth);
      float border = smoothstep(1.0, -1.0, d) - fill;

      float alpha = smoothstep(1.0, -1.0, d) * u_bgcolor.a;
      FragColor = vec4(mix(u_bgcolor.rgb, u_bordercolor, border), alpha);
      break;
    default:
      FragColor = u_bgcolor;
  }
}
