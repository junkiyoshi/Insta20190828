#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	auto radius = 300;
	auto noise_step = 0.003;
	auto len = 30;
	ofColor color;
	for (auto deg = 0; deg < 360; deg += 10) {

		auto noise_seed_x = ofRandom(1000);
		auto noise_seed_y = ofRandom(1000);
		auto noise_seed_z = ofRandom(1000);
		color.setHsb(ofMap(deg, 0, 360, 0, 255), 180, 255);

		glm::vec3 pre_location;
		for (int i = 0; i < len; i++) {

			auto angle_x = ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + i) * noise_step), 0, 1, -PI * 2, PI * 2);
			auto angle_y = ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + i) * noise_step), 0, 1, -PI * 2, PI * 2);
			auto angle_z = ofMap(ofNoise(noise_seed_z, (ofGetFrameNum() + i) * noise_step), 0, 1, -PI * 2, PI * 2);

			auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
			auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));
			location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;

			if (i > 0) {

				ofSetColor(color, ofMap(i, 0, len, 0, 255));
				ofDrawLine(location, pre_location);
			}
			pre_location = location;
		}

	}
	
	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}