#version 130

in vec3 position;

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

uniform mat4 transform;

void main()
{
    gl_Position = transform * model * vec4(position, 1.0f);
}