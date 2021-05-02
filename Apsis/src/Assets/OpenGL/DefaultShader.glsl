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
void main()
{
	a_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}