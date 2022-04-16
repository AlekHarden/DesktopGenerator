#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

uniform mat4 u_MVP;


void main(){
	color = v_Color;
};
