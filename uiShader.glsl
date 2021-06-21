#shader vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
uniform mat4 model;
uniform mat4 view;
out vec2 coord;
void main()
{
    gl_Position = view * model * vec4(position, 0.0, 1.0);
    coord = uv;
}

#shader fragment
#version 330 core
in vec2 coord;
uniform sampler2D ourTexture;
void main()
{
    vec4 texColor = texture(ourTexture, coord);
    gl_FragColor = texColor;
}
