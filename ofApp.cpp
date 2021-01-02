#include "ofApp.h"
#include "Emitter.h"
//----------------------------------------------------------------------------------
//
// This example code demonstrates the use of an "Emitter" class to emit Sprites
// and set them in motion. The concept of an "Emitter" is taken from particle
// systems (which we will cover next week).
//
//  1) Creates a simple Emitter  that you can drag around (without images)
//  2) Creates an Sprite to Collide with
//
//  requires ofxGUI add-in for sliders for changing parameters
// 
//
//
//  Kevin M. Smith - CS 134 SJSU

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);

	emitter = new Emitter( new SpriteSystem() );
	emitter->setChildSize(10, 10);
	collider.setPosition(ofVec3f(600, 200));
	collider.width = 20;
	collider.height = 20;
	imageLoaded = false;

	if (defaultImage.loadImage("images/test.png")) {
		defaultImage.resize(90, 90);
		emitter->setImage(defaultImage);
		//emitter->setChildImage(defaultImage);
		imageLoaded = true;
	}
	if (missileImage.loadImage("images/missile.png")) {
		missileImage.resize(30, 30);
		emitter->setChildImage(missileImage);
		imageLoaded = true;
	}


	gui.setup();
	gui.add(rate.setup("rate", 5, 1, 10));
	gui.add(life.setup("life", 2, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(0, -700, 3000), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 10000)));

	bHide = false;

	emitter->setPosition(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 0));
	//emitter->start();

	
}

//--------------------------------------------------------------
void ofApp::update() {

	if(!gameStarted) return;

	
	if (rightKeyPressed && emitter->trans.x < ofGetWindowWidth()-40)
	{
		ofPoint moveRight = ofPoint(movementSpeed, 0);
		ofVec3f delta = moveRight;
		emitter->trans += delta;
	}
	if (leftKeyPressed && emitter->trans.x > 0 + 40)
	{
		ofPoint moveRight = ofPoint(-movementSpeed, 0);
		ofVec3f delta = moveRight;
		emitter->trans += delta;
	}
	if (upKeyPressed && emitter->trans.y > 0 + 40)
	{
		ofPoint moveRight = ofPoint(0, -movementSpeed);
		ofVec3f delta = moveRight;
		emitter->trans += delta;
	}
	if (downKeyPressed && emitter->trans.y < ofGetWindowHeight() - 40)
	{
		ofPoint moveRight = ofPoint(0, movementSpeed);
		ofVec3f delta = moveRight;
		emitter->trans += delta;
	}

	emitter->setRate(rate);
	emitter->setLifespan(life * 1000);    // convert to milliseconds 
	emitter->setVelocity(glm::vec3(velocity));
	emitter->update();

	checkCollisions();
}


//--------------------------------------------------------------
void ofApp::draw(){
	if (!gameStarted) {
		//cout << "Enter spacebar to start the game." << endl;
		ofDrawBitmapString("Press spacebar to start", ofGetWindowWidth()/2-100, ofGetWindowHeight()/2);
		return;
	}
	emitter->draw();
	collider.draw();

	if (!bHide) {
		gui.draw();
	}
}

void ofApp::checkCollisions() {

	// remove all sprites emitted within a radius equal to the max
	// distance sprite can travel in one frame.
	//
	float dist = emitter->maxDistPerFrame();
	collider.width = dist;
	collider.height = dist;
	emitter->sys->removeNear(collider.trans, emitter->maxDistPerFrame());
}


//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//	cout << "mouse( " << x << "," << y << ")" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofPoint mouse_cur = ofPoint(x, y);
	ofVec3f delta = mouse_cur - mouse_last;
	//emitter->trans += delta;
	
	//right, left, top, bottom boundary check
	if (!(emitter->trans.x >= ofGetWindowWidth() - 40 && delta.x > 0) &&
		!(emitter->trans.x <= 0 + 40 && delta.x < 0) && 
		!(emitter->trans.y <= 0 + 40 && delta.y < 0) && 
		!(emitter->trans.y >= ofGetWindowHeight() - 40 && delta.y > 0))
	{
		emitter->trans += delta;
	}

	mouse_last = mouse_cur;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouse_last = ofPoint(x, y);
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

void ofApp::keyPressed(int key) {
	switch (key) {
	case 'C':
	case 'c':
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'H':
	case 'h':
		bHide = !bHide;
		break;
	case 'r':
		break;
	case 's':
		break;
	case 'u':
		break;
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_DEL:
		break;
	case ' ': {
	
		if(!gameStarted)
		{
			gameStarted = true;
			break;
		}
		emitter->started = true;
		break;
	};
	case OF_KEY_RIGHT: {
		//cout << "right key preesed." << endl;
		rightKeyPressed = true;
		break;
	};
	case OF_KEY_LEFT: {
		//cout << "Left key preesed." << endl;
		leftKeyPressed = true;
		break;
	};
	case OF_KEY_UP: {
		//cout << "Up key preesed."<< endl;
		upKeyPressed = true;
		break;
	};
	case OF_KEY_DOWN: {
		//cout << "Down key preesed." << endl;
		downKeyPressed = true;
		break;
	};
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_RIGHT: {
		//cout << "right key Released." << endl;
		rightKeyPressed = false;
		break;
	};
	case OF_KEY_LEFT: {
		//cout << "Left key Released." << endl;
		leftKeyPressed = false;
		break;
	};
	case OF_KEY_UP: {
		//cout << "Up key Released." << endl;
		upKeyPressed = false;
		break;
	};
	case OF_KEY_DOWN: {
		//cout << "Down key Released." << endl;
		downKeyPressed = false;
		break;
	};
	case ' ': {
		
		emitter->stop();
		break;
	};
	}

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

