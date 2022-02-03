#type vertex
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex_coord;

out vec3 v_frag_pos;
out vec3 v_normals;
out vec2 v_tex_coord;

uniform mat4 u_transform;
uniform mat4 u_view_projection;

void main()
{
    v_frag_pos = vec3(u_transform * vec4(a_position, 1.0));
    v_normals = mat3(transpose(inverse(u_transform))) * a_normal;
    v_tex_coord = a_tex_coord;  
    
    // gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
    gl_Position = u_view_projection * vec4(v_frag_pos, 1.0);
}

#type fragment
#version 330 core

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 v_frag_pos;
in vec3 v_normals;
in vec2 v_tex_coord;

uniform vec3 u_view_pos;
uniform Material u_material;
uniform Light u_light;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, v_tex_coord);
}