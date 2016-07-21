#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform vec4 globalColor;
uniform mat4 viewMatrix;

in vec4 position;
in vec3 normal;

out vec4 positionVarying;
out vec3 normalVarying;

out mat4 normalMatrix;

void main(){
    normalMatrix = inverse(transpose((modelViewMatrix)));
    normalVarying = normal;
    positionVarying = (inverse(viewMatrix) * modelViewMatrix) * position;
    gl_Position = modelViewProjectionMatrix * position;
}