#version 330

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform vec4 globalColor;

uniform mat4 viewProjMat[6];

layout(triangles) in;
layout(triangle_strip, max_vertices= 18) out;

out vec4 positionVarying;

void main (void) {
    for(int i=0;i<6;i++){
        gl_Layer = i;
        for(int j=0;j<3;j++){
            positionVarying = gl_in[j].gl_Position;
            gl_Position = viewProjMat[i] * positionVarying;
            EmitVertex();
        }
        EndPrimitive();
    }
}