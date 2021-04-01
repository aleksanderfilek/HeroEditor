#shader vertex
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec2 coord;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);
    coord = uv;
}

#shader fragment
#version 330 core

in vec2 coord;

uniform sampler2D ourTexture;

void main()
{
    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
} 