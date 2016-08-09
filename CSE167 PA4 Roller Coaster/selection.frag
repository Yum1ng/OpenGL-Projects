#version 330 core

// This is a sample fragment shader.
uniform uint id;
uniform uint id2;
out vec4 color;

void main()
{

    color = vec4(id/255.0f, 0.0f, id2, 0.0f);
}

