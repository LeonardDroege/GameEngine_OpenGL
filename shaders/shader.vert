#version 460

// Input vertex attributes
layout (location = 0) in vec3 position;  // Vertex position in local space (model space)
layout (location = 1) in vec3 normal;     // Vertex normal

// Output to fragment shader
out vec4 vertexColor; // Color passed to fragment shader for output

uniform vec4 u_color;

// Uniforms for transformation matrices
uniform mat4 u_model;       // Model matrix: transforms from local space to world space
uniform mat4 u_view;        // View matrix: transforms from world space to camera space (view space)
uniform mat4 u_projection;  // Projection matrix: transforms from camera space to clip space

void main()
{
    // Apply the transformations to the vertex position
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0);

    // Pass the vertex color to the fragment shader for coloring the pixel
    vertexColor = u_color;
}