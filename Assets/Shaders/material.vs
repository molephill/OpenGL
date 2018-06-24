#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 invest;

void main()
{

	vec4 vmp = view * model * vec4(aPos, 1.0);

	FragPos = vec3(vmp);
    Normal = mat3(transpose(invest)) * aNormal;  

    gl_Position = projection * vmp;
	TexCoords = vec2(aTexCoord.x, aTexCoord.y);
}
