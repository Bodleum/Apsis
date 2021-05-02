ShaderType::Vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
void main()
{
	gl_Position = vec4(a_Position, 1.0f);
}

ShaderType::Pixel
#version 450 core
layout(location = 0) out vec4 a_Color;
uniform vec4 u_Color;
void main()
{
	a_Color = u_Color;
}