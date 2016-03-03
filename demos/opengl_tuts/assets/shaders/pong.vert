#version 130

in vec3 position;
in vec2 text_coord;

out vec2 tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    tex_coord = vec2(text_coord.x, 1.0f - text_coord.y);
}