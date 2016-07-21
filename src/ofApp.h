#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void renderScene();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofShader depth, render;
    GLuint depthCubemap, depthMapFBO;
    ofEasyCam cam;
    
    ofMatrix4x4 viewProjMat[6], lookAtMat[6];
    ofMatrix4x4 shadowProjMatrix;
    ofVec3f lightPos = ofVec3f(0.0, 0.0, 0.0);
    int shadowMapRes = 1024;
    float farPlane = 5000.0;
    
    ofVec3f boxPos[25], spherePos[50];
};
