#version 410 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float greenChange;

void main()
{
//    FragColor = vec4(ourColor.x, greenChange, ourColor.z, 1.0f);
    //FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, 1.0f);
//    FragColor= texture(texture1, TexCoord) * vec4(ourColor.x, greenChange, ourColor.z, 1.0f);
//    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * vec4(ourColor.x, greenChange, ourColor.z, 1.0f);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), greenChange);
}
