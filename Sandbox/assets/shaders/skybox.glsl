#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_view_projection;

out vec3 v_tex_coords;

void main() {
	vec4 pos = u_view_projection * vec4(a_position, 1.0);
	gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
	v_tex_coords = vec3(a_position.x, a_position.y, -a_position.z);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 fragment_color;

in vec3 v_tex_coords;

uniform samplerCube u_skybox;

void main() {
	fragment_color = texture(u_skybox, v_tex_coords);
}