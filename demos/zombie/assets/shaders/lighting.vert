#version 130

in vec3 position;
in vec3 normal;
in vec2 texCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

uniform mat4 transform;
void main()
{
    //gl_Position = projection * view * model * vec4(position, 1.0f);
    gl_Position = transform * model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.0f));
    TexCoords = vec2(texCoords.x, 1.0 - texCoords.y);

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalMatrix * normal;
}
