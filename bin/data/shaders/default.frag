#version 330

in vec4 positionVarying;

uniform vec3 lightPos;
uniform float far_plane;

void main (void) {
    // get distance between fragment and light source
    float lightDistance = length(positionVarying.xyz - lightPos);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;
    
    // Write this as modified depth
    gl_FragDepth = lightDistance;
}