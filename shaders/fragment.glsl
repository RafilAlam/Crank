#version 450 core

#define M_MODEL 0
#define M_RECT  1
#define M_TRI   2
#define M_CIR   3

in vec4 gl_FragCoord;

out vec4 FragColor;

uniform vec2 u_modelposition;
uniform vec2 u_modelsize;
uniform float u_cornerradius;
uniform vec3 u_color;
uniform int u_meshtype;
uniform vec2 u_resolution;

float sdfRect(vec2 point, vec2 halfsize) 
{
  vec2 q = abs(point) - halfsize;
  return length(max(q, 0.0f)) + min(max(q.x, q.y), 0.0);
}

void main()
{
  float d = sdfRect(gl_FragCoord.xy - u_modelposition, u_modelsize*0.5 - u_cornerradius) - u_cornerradius;
  float alpha = smoothstep(1.0, -1.0, d);
  FragColor = vec4(u_color, alpha);
}
