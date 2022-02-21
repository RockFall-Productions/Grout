#type vertex
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex_coord;

out vec3 v_frag_pos;
out vec3 v_normal;
out vec2 v_tex_coord;

uniform mat4 u_transform;
uniform mat4 u_view_projection;

void main()
{
    v_frag_pos = vec3(u_transform * vec4(a_position, 1.0));
    v_normal = mat3(transpose(inverse(u_transform))) * a_normal;
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
in vec3 v_normal;
in vec2 v_tex_coord;

uniform vec3 u_view_pos;
uniform Material u_material;
uniform Light u_light;

uniform vec3 u_t_light_pos;
uniform vec3 u_t_light_dir;
uniform vec3 u_t_ambient;
uniform float u_t_ambient_strength;
uniform vec3 u_t_light_diffuse;
uniform vec3 u_t_light_specular;
uniform bool u_block_light;

uniform sampler2D texture_diffuse1;

void main()
{   
    if (u_block_light){
        FragColor = texture2D(texture_diffuse1, v_tex_coord);
    }
    else {
        float material_shininess = 1.0;

        // ambient
        vec3 ambient = (u_t_ambient * u_t_ambient_strength) * texture(texture_diffuse1, v_tex_coord).rgb;

        // diffuse
        vec3 norm = normalize(v_normal);
        //vec3 light_dir = normalize(u_t_light_pos - v_frag_pos);
        vec3 light_dir = u_t_light_dir;
        float diff = max(dot(norm, -light_dir), 0.0);
        vec3 diffuse = u_t_light_diffuse * diff * texture(texture_diffuse1, v_tex_coord).rgb;

        // specular
        vec3 view_dir = normalize(u_view_pos - v_frag_pos);
        vec3 reflect_dir = reflect(-light_dir, norm);
        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material_shininess);
            //vec3 specular = u_t_light_specular * spec * texture(texture_specular1, v_tex_coord).rgb;
        vec3 specular = u_t_light_specular * spec;

        vec3 result = ambient + diffuse;
        FragColor = vec4(result, 1.0);
    }
}