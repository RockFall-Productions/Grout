#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

uniform mat4 u_transform;

out vec3 v_color;

void main() {
	v_color = a_color.rgb;
	gl_Position = u_transform * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform

in float visibility;
in vec3 v_final_color;

void main() {
	if (visibility < -0.9) {
		color = vec4(v_final_color, 1.0f);
	} else {
		color = mix(vec4(0.0, 0.23, 0.58, 1.0), vec4(v_final_color, 1.0), visibility);
	}
	
}

#type geometry
#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 v_color[];
out vec3 v_final_color;

uniform float u_fog_density;
uniform float u_fog_gradient;
uniform vec3 u_camera_pos;
uniform float u_fog_on;

out float visibility;

uniform vec3 u_light_pos;
uniform vec3 u_light_dir;
uniform vec3 u_ambient_color;
uniform float u_ambient_strenght;

uniform bool u_block_light;

uniform mat4 u_view_projection;

vec3 calculateLighting(vec3 normal){
	//vec3 light_dir = normalize(u_light_pos - gl_in[0].gl_Position.xyz); // check if correct order
	vec3 light_dir = u_light_dir;
	float brightness = max(dot(light_dir, normal), 0.0);
	return (brightness) + (u_ambient_color * u_ambient_strenght);
}

vec3 calcTriangleNormal(){
	vec3 tangent1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 tangent2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 normal = cross(tangent1, tangent2);
	return normalize(normal);
}

void main(void){

	vec3 normal = calcTriangleNormal();
	vec3 lighting = calculateLighting(normal);
	
	for(int i=0;i<3;i++){
		// Fog
		if (u_fog_on == 1) {
			float distance = length(u_camera_pos - gl_in[i].gl_Position.xyz);
			visibility = exp(-pow(distance*u_fog_density, u_fog_gradient));
			visibility = clamp(visibility, 0.0, 1.0);
		} else {
			visibility = -1;
		}
		

		// Position
		gl_Position = u_view_projection * gl_in[i].gl_Position;

		// Color
		v_final_color = v_color[0] * lighting;

		EmitVertex();
	}
	
	EndPrimitive();

}