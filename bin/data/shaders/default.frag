#version 330

in vec4 positionVarying;

uniform vec3 lightPos;
uniform float farPlane;

// based on http://learnopengl.com/#!Advanced-Lighting/Shadows/Point-Shadows
void main (void) {
    // get distance between fragment and light source
    float lightDistance = length(positionVarying.xyz - lightPos);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / farPlane;
    
    // Write this as modified depth
    gl_FragDepth = lightDistance;
}