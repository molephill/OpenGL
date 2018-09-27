#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aUV;
layout (location = 3) in vec3 aColor;

out vec3 ourColor;
out vec2 TextCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 viewMatrix;
uniform mat4 viewExtentionMatrix;
uniform mat4 model;

void main()
{
	mat4 model1 = viewExtentionMatrix * model;

	FragPos = vec3(model1 * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model1))) * aNormal;  

	gl_Position = projection * viewMatrix * vec4(FragPos, 1.0);
	ourColor = aColor;
	TextCoords = vec2(aUV.x, aUV.y);
}