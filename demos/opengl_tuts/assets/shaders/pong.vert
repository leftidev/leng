#version 130

in vec3 position;
in vec3 color;
in vec2 text_coord;

out vec3 my_color;
out vec2 tex_coord;

//uniform mat4 world;
//uniform mat4 view;
//uniform mat4 proj;

uniform mat4 transform;

void main()
{
    //gl_Position = proj * view * world * vec4(position, 1.0f);
    gl_Position = transform * vec4(position, 1.0f);
    my_color = color;
    tex_coord = vec2(text_coord.x, 1.0f - text_coord.y);
}