#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
uniform vec4 color;

out VS_OUT
{
	vec4 color;
} vs_out;


void main()
{
	vs_out.color = color;
	gl_Position = vec4(position, 0, 1);
};







#shader geometry
#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 5) out;

out vec4 color;

in VS_OUT{
	vec4 color;
} gs_in[];

void main() {

	color = gs_in[0].color;
	gl_Position = gl_in[2].gl_Position + vec4(0.5, 0.1, 0, 0);
	EmitVertex();
	gl_Position = gl_in[2].gl_Position + vec4(1.3, 0.1, 0, 0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.5,-0.8,0,0);
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + vec4(0.3, -0.8, 0, 0);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.9, -0.1, 0, 0);
	color = vec4(1, 1, 1, 1);
	EmitVertex();




	EndPrimitive();
}


#shader fragment
#version 330 core

out vec4 FragColor;
in vec4 color;

void main()
{

	FragColor = color;

};