#version 330 core
in vec3 vColor;
in vec2 vTexCoords;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
  FragColor = texture(tex0, vTexCoords);
}
