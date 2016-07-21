#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    
    // load shaders
    depth.setGeometryInputType(GL_TRIANGLES);
    depth.setGeometryOutputType(GL_TRIANGLE_STRIP);
    depth.setGeometryOutputCount(18);
    depth.load("shaders/default.vert", "shaders/default.frag", "shaders/default.geom");
    depth.begin();
    depth.setUniform1f("farPlane", farPlane);
    depth.end();
    
    render.load("shaders/render");
    render.begin();
    render.setUniform1f("farPlane", farPlane);
    render.setUniform1i("depthMap", 1);
    render.end();
    
    // generate cubemap fbo
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (GLuint i = 0; i < 6; ++i){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32F, shadowMapRes, shadowMapRes, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // make projection matrix
    shadowProjMatrix.makePerspectiveMatrix(90.0, 1.0, 1.0, farPlane);
        
    // set objects position
    int size = sizeof(boxPos)/sizeof(ofVec3f);
    for(int i=0;i<size;i++){
        boxPos[i].set(1000 * sin(TWO_PI * float(i) / float(size)), 250, 1000 * cos(TWO_PI * float(i) / float(size)));
    }
    for(auto &p: spherePos){
        p.set(ofRandom(-1000, 1000), 50, ofRandom(-1000, 1000));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    lightPos = ofVec3f(500 * sin(ofGetElapsedTimef()), 250 + 200 * sin(2.0 * ofGetElapsedTimef()), 500 * cos(ofGetElapsedTimef()));
    
    // make view matricies
    lookAtMat[0].makeLookAtViewMatrix(lightPos, lightPos + ofVec3f(1,0,0), ofVec3f(0,-1,0));
    lookAtMat[1].makeLookAtViewMatrix(lightPos, lightPos + ofVec3f(-1,0,0), ofVec3f(0,-1,0));
    lookAtMat[2].makeLookAtViewMatrix(lightPos, lightPos + ofVec3f(0,1,0), ofVec3f(0,0,1));
    lookAtMat[3].makeLookAtViewMatrix(lightPos, lightPos + ofVec3f(0,-1,0), ofVec3f(0,0,-1));
    lookAtMat[4].makeLookAtViewMatrix(lightPos, lightPos + ofVec3f(0,0,1), ofVec3f(0,-1,0));
    lookAtMat[5].makeLookAtViewMatrix(lightPos, lightPos + ofVec3f(0,0,-1), ofVec3f(0,-1,0));
    
    // make view projection matricies
    for(int i=0;i<6;i++){
        viewProjMat[i] = lookAtMat[i] * shadowProjMatrix;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    
    // make depth cube map pass
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glViewport(0, 0, shadowMapRes, shadowMapRes);
    ofClear(0);
    depth.begin();
    depth.setUniform3f("lightPos", lightPos);
    glUniformMatrix4fv(glGetUniformLocation(depth.getProgram(), "viewProjMat"), 6, GL_FALSE, viewProjMat[0].getPtr());
    renderScene();
    depth.end();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    // bind cubemap
    glActiveTexture( GL_TEXTURE0 + 1 );
    glEnable( GL_TEXTURE_CUBE_MAP );
    glBindTexture( GL_TEXTURE_CUBE_MAP, depthCubemap );
    
    // render pass
    cam.begin();
    render.begin();
    render.setUniform3f("lightPos", lightPos);
    renderScene();
    render.end();
    cam.end();
    
    // unbind cubemap
    glActiveTexture( GL_TEXTURE0 + 1 );
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0 );
    glDisable( GL_TEXTURE_CUBE_MAP );
    glActiveTexture( GL_TEXTURE0 );
}

//--------------------------------------------------------------
void ofApp::renderScene(){
    for(auto p: boxPos){
        ofDrawBox(p, 100, 500, 100);
    }
    for(auto p: spherePos){
        ofDrawSphere(p, 50);
    }
    ofDrawBox(0, 0, 0, 10000, 1, 10000);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
