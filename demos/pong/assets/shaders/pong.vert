#version 130

in vec3 position;
in vec4 color;
in vec2 text_coord;

out vec4 my_color;
out vec2 tex_coord;

uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * world * vec4(position, 1.0f);
    my_color = color;
    tex_coord = vec2(text_coord.x, 1.0f - text_coord.y);
}