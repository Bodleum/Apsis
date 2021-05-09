ShaderType::Vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0f);
	v_TexCoord = a_TexCoord;
}

ShaderType::Pixel
#version 450 core
layout(location = 0) out vec4 o_Color;
in vec2 v_TexCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	o_Color = texColor * u_Color;
}