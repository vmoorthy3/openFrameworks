#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,0,255);
	ofSetVerticalSync(true);
	frameByframe = false;

	// Uncomment this to show movies with alpha channels
	fingerMovie.setPixelFormat(OF_PIXELS_RGBA);

	//fingerMovie.loadMovie("movies/test_png.mov");
	fingerMovie.loadMovie("movies/test_animation.mov");
	//fingerMovie.loadMovie("movies/fingers.mov");
	fingerMovie.play();
}

//--------------------------------------------------------------
void testApp::update(){
    fingerMovie.update();
}

//--------------------------------------------------------------
void testApp::draw(){

	//ofBackground(255,255,0);
	ofSetHexColor(0xFFFFFF);
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);		// Movie has premultiplied alpha.

	fingerMovie.draw(20, 20, 320, 240);
	
	glDisable(GL_BLEND);

	ofSetHexColor(0x000000);
    unsigned char * pixels = fingerMovie.getPixels();
    
    int nChannels = fingerMovie.getPixelsRef().getNumChannels();
    
    // let's move through the "RGB(A)" char array
    // using the red pixel to control the size of a circle.
	for (int i = 4; i < fingerMovie.width; i+=8){
        for (int j = 4; j < fingerMovie.height; j+=8){
            unsigned char a = pixels[(j * fingerMovie.width + i)*nChannels + 3];
            float val = 1 - ((float)a / 255.0f);
            ofCircle(400 + i,20+j,10*val);
        }
    }


    ofSetHexColor(0x000000);
	ofDrawBitmapString("press f to change",20,320);
    if(frameByframe) ofSetHexColor(0xCCCCCC);
    ofDrawBitmapString("mouse speed position",20,340);
    if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);
    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
    ofSetHexColor(0x000000);

    ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),20,380);
    ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),20,400);
    ofDrawBitmapString("speed: " + ofToString(fingerMovie.getSpeed(),2),20,420);

    if(fingerMovie.getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch(key){
        case 'f':
            frameByframe=!frameByframe;
            fingerMovie.setPaused(frameByframe);
        break;
        case OF_KEY_LEFT:
            fingerMovie.previousFrame();
        break;
        case OF_KEY_RIGHT:
            fingerMovie.nextFrame();
        break;
        case '0':
            fingerMovie.firstFrame();
        break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        fingerMovie.setSpeed(speed);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        fingerMovie.setPosition(pct);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!frameByframe){
        fingerMovie.setPaused(true);
	}
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(!frameByframe){
        fingerMovie.setPaused(false);
	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
