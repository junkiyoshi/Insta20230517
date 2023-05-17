#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->frame.clear();

	float scale = 18;
	ofColor color;

	for (int i = 0; i < 1; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		for (int deg = 0; deg < 360; deg += 1) {

			auto location = glm::vec3(this->make_point(deg * DEG_TO_RAD) * scale, 0);
			location.x += ofMap(ofNoise(noise_seed.x, location.x * 0.5, ofGetFrameNum() * 0.0085), 0, 1, -30, 30);
			location.y += ofMap(ofNoise(noise_seed.y, location.y * 0.5, ofGetFrameNum() * 0.0085), 0, 1, -30, 30);

			this->frame.addVertex(location);

			color.setHsb(ofRandom(255), 255, 255);
			this->frame.addColor(color);
		}
	}

	for (int i = 0; i < this->frame.getNumVertices(); i++) {

		for (int k = i + 1; k < this->frame.getNumVertices(); k++) {

			auto distance = glm::distance(this->frame.getVertex(i), this->frame.getVertex(k));
			if (distance < 15) {

				this->frame.addIndex(i); this->frame.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5 + glm::vec2(0, -30));

	this->frame.drawVertices();

	for (int i = 0; i < this->frame.getNumVertices(); i++) {

		ofPushMatrix();
		ofTranslate(this->frame.getVertex(i));
		ofRotate(ofRandom(360));

		auto scale = ofRandom(0.5, 1.5);

		ofFill();
		ofSetColor(this->frame.getColor(i), 92);
		ofBeginShape();
		for (int deg = 0; deg < 360; deg += 2) {

			ofVertex(this->make_point(deg * DEG_TO_RAD) * scale);
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(this->frame.getColor(i));
		ofBeginShape();
		for (int deg = 0; deg < 360; deg += 2) {

			ofVertex(this->make_point(deg * DEG_TO_RAD) * scale);
		}
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
// Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}