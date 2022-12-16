#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 Text_Coor;

uniform mat4 model;

uniform mat4 projection;
uniform mat4 view;

//uniform mat4 scale;
out vec2 v_TexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
};



#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 v_TexCoord;


uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{

		FragColor = u_Color;

};