#shader vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;

void main()
{
    gl_Position = view * model * vec4(position, 1.0);
}

#shader fragment
#version 330 core

uniform vec4 color;

uniform sampler2D ourTexture;

void main()
{
    gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
} 