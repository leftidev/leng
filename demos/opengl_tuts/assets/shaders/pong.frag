#version 130

in vec3 my_color;
in vec2 tex_coord;

out vec4 color;

uniform sampler2D my_texture;

void main()
{
    color = texture(my_texture, tex_coord) * vec4(my_color, 1.0f);
}